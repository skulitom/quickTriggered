#include "Font.h"
#include <stdarg.h>

FontManager::FontManager(D3DAPP* d3dApp, Basic2DDraw* draw2d, char* fntFile, char* loc)
{

	this->D3dApp = d3dApp;

	this->Locale = loc;

	if (!this->CompileFile(fntFile) || !this->InitConstTexts())
	{
		//MessageBox(this->D3dApp->GetWindow(), "Can't Compile *.fnt file", std::string(fntFile).c_str(), MB_ICONERROR);
		this->Error = true;
		return;
	}

	this->Draw2d = draw2d;

	this->BState = this->D3dApp->GetBlendState((UINT)DX_BS_TRANSPARENCY);
	PrepareShader(this->FontMaterial, this->Draw2d->GetShaderManager());

}

FontManager::~FontManager()
{

	for (int i = 0; i < this->Decoder.size(); i++)
		D3DDelete(this->Decoder.at(i).GUISym);

}

bool FontManager::CompileFile(char* fntFile)
{

	FileManager* FNTManager = new FileManager(this->D3dApp->GetCatalogName() + "\\Resources\\Fonts\\"+std::string(fntFile));
	FNTManager->Open();
	 
	if (FNTManager->GetFILE().fail())
	{
		D3DDelete(FNTManager);
		MessageBox(this->D3dApp->GetWindow(), "Can't Load *.fnt file", std::string(fntFile).c_str(), MB_ICONERROR);
		return false;
	}
	
	bool Reading = false;
	std::string Line;
	std::vector<std::string> Words;
	SDecoder NSDec;
	while (!FNTManager->GetFILE().eof())
	{

		Line.clear();
		Line.shrink_to_fit();
		Line = FNTManager->GetStringFromFile();

		if (!Line.compare("$StartDec"))
			Reading = true;

		if (Reading == true && !Line.compare("$StopDec"))
			Reading = false;

		if (Reading)
		{

			//////////////////////////////////////////
			//**Reading Name
			//////////////////////////////////////////
			if (Line.size() && Line.at(0) == '$')
			{

				Words = StringHelp::DivideString(Line, "|");

				if (Words.size() >= 2)
					if (!Words.at(0).compare("$Size"))
					{
						this->Size = 1.f / StringHelp::ASCIIToINT(Words.at(1));
					}
					else if (!Words.at(0).compare("$Name"))
					{
						this->FontMaterial = this->D3dApp->GetMaterial(Words.at(1));
					}
				continue;
			}
	
			//////////////////////////////////////////
			//**Reading Settings
			//////////////////////////////////////////
			Words = StringHelp::DivideString(Line, "|");

			if (Words.size() == 8)
			{

				GUIChar* NChar = new GUIChar;
				NChar->Sizes = Vector2d(StringHelp::ASCIIToINT(Words.at(4)), StringHelp::ASCIIToINT(Words.at(5)));
				NChar->TexCoords = XMFLOAT2(StringHelp::ASCIIToINT(Words.at(2)), StringHelp::ASCIIToINT(Words.at(3)));
				NChar->XOffSet = StringHelp::ASCIIToINT(Words.at(6));
				NChar->YOffSet = StringHelp::ASCIIToINT(Words.at(7));

				NSDec.GUISym = NChar;
				NSDec.Sym = *Words.at(0).c_str();

				this->Decoder.push_back(NSDec);

			}

		}

	}

	D3DDelete(FNTManager);

	if (!this->FontMaterial)
	{
		MessageBox(this->D3dApp->GetWindow(), "Load font: No Font Name or Invalid Font Name", this->CTextFName.c_str(), MB_ICONWARNING);
		return false;
	}
	if (this->Size <= 0)
	{
		MessageBox(this->D3dApp->GetWindow(), "Load font: Invalid texutre size", this->CTextFName.c_str(), MB_ICONWARNING);
		return false;
	}
	
	return true;

}

void FontManager::Draw(Vector2d& pos, XMFLOAT3& color, float scale, const char* buffer)
{

	FontManager::Render(pos, color, scale, buffer);

}

void FontManager::DrawA(Vector2d& pos, XMFLOAT3& color, float scale, const char* text, ...)
{

	va_list List;
	va_start(List, text);

	static char Buffer[512];

	vsprintf(Buffer, text, List);

	va_end(List);

	FontManager::Render(pos, color, scale, Buffer);

}

const char* FontManager::GetLocText(const char* key)
{

	auto& It = this->LocMap.find(std::string(key));
	if (It != std::end(this->LocMap))
	{
		return It->second.c_str();
	}

	return nullptr;

}

void FontManager::Render(Vector2d& pos, XMFLOAT3& color, float scale, const char* buffer)
{

	if (this->Error)
		return;

	if (*buffer == '@')
	{

		buffer = this->GetLocText(buffer);
		if (!buffer)
			return;

	}

	this->D3dApp->SetBlendState(this->BState);

	static Vector2d PrevSizes;
	PrevSizes = Vector2d(0, 0);
	static float TScale;
	static UINT FirstHeight;
	FirstHeight = 0;

	TScale = this->FontMaterial->Scale.x;

	this->FontMaterial->Scale.x = TScale * scale;


	for (const char* ptrText = buffer; *ptrText != '\0'; ptrText++)
	{

		for (int i = 0; i < this->Decoder.size(); i++)
		{
			if (this->Decoder.at(i).Sym == *ptrText)
			{


				if (!FirstHeight)
					FirstHeight = this->Decoder.at(i).GUISym->Sizes.Y;

				this->FontMaterial->TextureOffset.x = this->Decoder.at(i).GUISym->TexCoords.x * (this->Size);
				this->FontMaterial->TextureOffset.y = this->Decoder.at(i).GUISym->TexCoords.y * (this->Size);

				this->Draw2d->DrawRectangle(pos + Vector2d( this->Decoder.at(i).GUISym->Sizes.X*0.5f, this->Decoder.at(i).GUISym->Sizes.Y - FirstHeight - this->Decoder.at(i).GUISym->YOffSet)*0.5f*scale + PrevSizes, this->Decoder.at(i).GUISym->Sizes * scale, this->Draw2d->GetShaderManager()->GetIndexOfVP(),
					XMFLOAT4(0, 0, 0, 0), XMFLOAT4(color.x, color.y, color.z, 0), this->FontMaterial);
				PrevSizes = PrevSizes + Vector2d((this->Decoder.at(i).GUISym->Sizes.X*0.5f + 7) * scale, 0);
				//+Vector2d(this->Decoder.at(i).GUISym->XOffSet, 0)
			}

		}

	}

	this->FontMaterial->Scale.x = TScale;

}

bool FontManager::InitConstTexts()
{

	std::string Line;
	std::vector<std::string> Words;

	bool Reading = false;

	FileManager* CTMFile = new FileManager(this->D3dApp->GetCatalogName() + "\\Resources\\Loc\\" + this->Locale + ".txt");
	CTMFile->Open();
	if (CTMFile->GetFILE().fail())
	{
		MessageBox(this->D3dApp->GetWindow(), "Can't Open Constant Text file", std::string(this->Locale).c_str(), MB_ICONERROR);
		D3DDelete(CTMFile);
		return false;
	}
	Line = CTMFile->GetStringFromFile();
	if (Line.compare("$Loc"))
	{
		MessageBox(this->D3dApp->GetWindow(), "Can't Recognize Constant Text file", std::string(this->Locale).c_str(), MB_ICONERROR);
		D3DDelete(CTMFile);
		return false;
	}

	while (!CTMFile->GetFILE().eof())
	{

		Line = CTMFile->GetStringFromFile();

		if (!Line.compare("$StartDec"))
		{
			Reading = true;
			continue;
		}

		if (!Line.compare("$StopDec"))
		{
			Reading = false;
			continue;
		}
		
		if (Reading)
		{

			Words = StringHelp::DivideString(Line, "|");
			if (Words.size() == 2)
			{

				this->LocMap.insert(std::pair<std::string, std::string>(Words.at(0), Words.at(1)));
				//Words.at(0) = Words.at(0);
			}

		}

	}

	D3DDelete(CTMFile);

	return true;

}
