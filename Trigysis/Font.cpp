#include "Font.h"
#include <stdarg.h>

FontManager::FontManager(D3DAPP* d3dApp, Basic2DDraw* draw2d, char* fntFile)
{

	this->D3dApp = d3dApp;

	if (!this->CompileFile(fntFile))
	{
		D3DDelete(this->CTFManager);
		//MessageBox(this->D3dApp->GetWindow(), "Can't Compile *.fnt file", std::string(fntFile).c_str(), MB_ICONERROR);
		this->Error = true;
		return;
	}

	this->InitConstTexts();

	this->Draw2d = draw2d;

	this->BState = this->D3dApp->GetBlendState((UINT)DX_BS_TRANSPARENCY);
	PrepareShader(this->FontMaterial, this->Draw2d->GetShaderManager());

}

FontManager::~FontManager()
{

	D3DDelete(this->CTFManager);

	for (int i = 0; i < this->Decoder.size(); i++)
		D3DDelete(this->Decoder.at(i).GUISym);

}

bool FontManager::CompileFile(char* fntFile)
{

	FileManager* FNTManager = new FileManager(this->D3dApp->GetCatalogName() + "\\Textures\\Fonts\\"+std::string(fntFile));
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

				Words = StringHelp::DivideString(Line, "-");

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
			Words = StringHelp::DivideString(Line, "-");

			if (Words.size() == 6)
			{

				GUIChar* NChar = new GUIChar;
				NChar->Sizes = Vector2d(StringHelp::ASCIIToINT(Words.at(4)), StringHelp::ASCIIToINT(Words.at(5)));
				NChar->TexCoords = XMFLOAT2(StringHelp::ASCIIToINT(Words.at(2)), StringHelp::ASCIIToINT(Words.at(3)));

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
	if (Reading)
	{
		MessageBox(this->D3dApp->GetWindow(), "Load font: ParamFile error", this->CTextFName.c_str(), MB_ICONWARNING);
		return false;
	}
	
	return true;

}

void FontManager::Draw(Vector2d& pos, XMFLOAT3& color, float scale, char* buffer)
{

	FontManager::Render(pos, color, scale, buffer);

}

void FontManager::DrawA(Vector2d& pos, XMFLOAT3& color, float scale, char* text, ...)
{

	va_list List;
	va_start(List, text);

	static char Buffer[512];

	vsprintf(Buffer, text, List);

	va_end(List);

	FontManager::Render(pos, color, scale, Buffer);

}

void FontManager::Render(Vector2d& pos, XMFLOAT3& color, float scale, char* buffer)
{

	if (this->Error)
		return;

	this->D3dApp->SetBlendState(this->BState);

	static Vector2d PrevSizes;
	PrevSizes = Vector2d(0, 0);
	static float TScale;

	TScale = this->FontMaterial->Scale.x;

	this->FontMaterial->Scale.x = TScale * scale;


	for (char* ptrText = buffer; *ptrText != '\0'; ptrText++)
	{

		for (int i = 0; i < this->Decoder.size(); i++)
		{
			if (this->Decoder.at(i).Sym == *ptrText)
			{

				this->FontMaterial->TextureOffset.x = this->Decoder.at(i).GUISym->TexCoords.x * (this->Size);
				this->FontMaterial->TextureOffset.y = this->Decoder.at(i).GUISym->TexCoords.y * (this->Size);

				this->Draw2d->DrawRectangle(pos + PrevSizes, this->Decoder.at(i).GUISym->Sizes * scale, this->Draw2d->GetShaderManager()->GetIndexOfVP(),
					XMFLOAT4(0, 0, 0, 0), XMFLOAT4(color.x, color.y, color.z, 0), this->FontMaterial);
				PrevSizes = PrevSizes + Vector2d(this->Decoder.at(i).GUISym->Sizes.X * scale, 0);

			}

		}

	}

	this->FontMaterial->Scale.x = TScale;

}

bool FontManager::InitConstTexts()
{

	//TODO: Some code...
	return true;

}
