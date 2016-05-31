#include "Element.h"
//////////////////////////////////////////////////
//*ElementsMLand
//////////////////////////////////////////////////
ElementsMLand::ElementsMLand(D3DAPP* d3dApp, D3DAPPINPUT* input, std::string& saveBufferName)
{
	this->D3dApp = d3dApp;
	this->Input = input;
	this->Draw2D = new Basic2DDraw(this->D3dApp);
	this->FManager = new FileManager(saveBufferName);
}

ElementsMLand::~ElementsMLand()
{
	for (size_t i = 0; i < this->Elements.size(); i++)
	{
		D3DDelete(this->Elements.at(i));
	}
	D3DDelete(this->Draw2D);
	D3DDelete(this->FManager);
	D3DRelease(this->VertexBuffer);
	D3DRelease(this->IndexBuffer);
	D3DRelease(this->InputLayout);
}

void ElementsMLand::AddNewElement(ElementInterface* pNewElement)
{
	if (pNewElement)
	{
		pNewElement->SetInput(this->Input);
		this->Elements.push_back(pNewElement);
	}
}
void ElementsMLand::DeleteElement(ElementInterface* pElementToDelete)
{
	if (!pElementToDelete)
		return;
	for (size_t i = 0; i < this->Elements.size(); i++)
	{
		if (this->Elements.at(i) == pElementToDelete)
		{
			D3DDelete(this->Elements.at(i));
			this->Elements.erase(this->Elements.begin() + i);
			return;
		}
	}
}

void ElementsMLand::UpdateAndDraw(FLOAT deltaTime)
{
	int Index = 0;
	while (Index < this->Elements.size())
	{
		if ((!this->Elements.at(Index)->GetIsFired()))
		{
			if (this->Elements.at(Index)->GetIsSpawned())
			{
				if (!this->IsLoadMode)
					this->Elements.at(Index)->Update(deltaTime);
				if (this->Elements.at(Index)->GetIsNeedRender())
				{
					this->Draw2D->DrawRectangle(this->Elements.at(Index)->GetPosition(), this->Elements.at(Index)->GetSizes(),
						this->Elements.at(Index)->GetIndexOfViewPort(),
						this->Elements.at(Index)->GetColors(), this->Elements.at(Index)->GetTextureViewPtr());
				}
			}
			Index++;
		}
		else
			this->DeleteElement(this->Elements.at(Index));
	}
}

void ElementsMLand::SetIsLoadMode(bool isLoadMode)
{

	this->IsLoadMode = isLoadMode;

	//if (this->IsLoadMode)
	//{
	//	
	//	this->SBuffer.open(this->SaveBufferName);
	//}
	//else
	//{
	//	this->SBuffer.close();
	//}

}

void ElementsMLand::LoadElements()
{

	//this->SBuffer.open(this->SaveBufferName);
	//std::string Command;
	//while (!this->SBuffer.eof())
	//{
	//	FileHelp::GetStringFromFile(this->SBuffer, Command);
	//	if (Command == "NewEl")
	//	{
	//		FileHelp::GetStringFromFile(this->SBuffer, Command);
	//		SaveLoadElementsTable(this, Command);
	//	}
	//}

	//this->IsLoadMode = 0;

}

///////////////////////////////////////////////////
//**ElementInterface
///////////////////////////////////////////////////
ElementInterface::ElementInterface(ElementsMLand* ptrToMotherLand)
{

	this->IsNeedRender = 1;

	if (ptrToMotherLand->GetIsLoadMode() && ptrToMotherLand->GetFManager()->GetCString() != "ELCMP")
	{
		//if (!ptrToMotherLand->GetSaveOBuffer())
			//return;

		UINT Counter = 1;
		__int32* Pointer = reinterpret_cast<__int32*>(this);
		std::string SFromFile;

		do
		{
			
			INT In = ptrToMotherLand->GetFManager()->GetINTFromFile();

			if (ptrToMotherLand->GetFManager()->GetCString() != "ELCMP")
				*(Pointer + Counter) = In;

			Counter++;

		} while (ptrToMotherLand->GetFManager()->GetCString() != "ELCMP");

	}

	ProtectPtr(PMLand);
	ProtectPtr(Input);
	ProtectPtr(D3dApp);
	DeclareElementName(ElementInterface, this->EName);
	this->PMLand = ptrToMotherLand;
	this->D3dApp = this->PMLand->GetD3DApp();
}


ElementInterface::ElementInterface(D3DAPP* d3dApp, Vector2d& position, Vector2d& sizes, short indexOfVPort,
	ElementsMLand* ptrToMotherLand, bool isNeedRender)
{
	this->D3dApp = d3dApp;
	this->PMLand = ptrToMotherLand;
	this->Position = position;
	if (abs(sizes.X) <= 1)
	{
		if(sizes.X > 0)
			this->Sizes.X = sizes.X * d3dApp->GetViewPort(indexOfVPort).Width;
		else
			this->Sizes.X = abs(sizes.X) * d3dApp->GetViewPort(indexOfVPort).Height;
	}
	else
		this->Sizes.X = sizes.X;
	if (abs(sizes.Y) <= 1)
	{
		if (sizes.Y > 0)
			this->Sizes.Y = sizes.Y * d3dApp->GetViewPort(indexOfVPort).Height;
		else 
			this->Sizes.Y = abs(sizes.Y) * d3dApp->GetViewPort(indexOfVPort).Width;
	}
	else
		this->Sizes.Y = sizes.Y;
	this->IsNeedRender = isNeedRender;
	this->IndexOfViewPort = indexOfVPort;
	this->Color = XMFLOAT4(0, 0, 0, 0);
}

bool ElementInterface::SetTexture(std::string& textureName)
{
	this->TextureView = this->D3dApp->GetTextureViewPtr(textureName);
	return 1;
}

void ElementInterface::SetSizesRelative(Vector2d& sizes, short indexOfVPort)
{

	//if (sizes.X == 0 && sizes.Y == 0)
	//	return;

	if (indexOfVPort == -1)
		indexOfVPort = this->IndexOfViewPort;

	if (abs(sizes.X) <= 1)
	{
		if (sizes.X > 0)
			this->Sizes.X = sizes.X * this->D3dApp->GetViewPort(indexOfVPort).Width;
		else
			this->Sizes.X = abs(sizes.X) * this->D3dApp->GetViewPort(indexOfVPort).Height;
	}
	else
		this->Sizes.X = sizes.X;
	if (abs(sizes.Y) <= 1)
	{
		if (sizes.Y > 0)
			this->Sizes.Y = sizes.Y * this->D3dApp->GetViewPort(indexOfVPort).Height;
		else
			this->Sizes.Y = abs(sizes.Y) * this->D3dApp->GetViewPort(indexOfVPort).Width;
	}
	else
		this->Sizes.Y = sizes.Y;

}

void ElementInterface::Spawn(Vector2d& position, short indexOfVPort)
{

	this->Position = position;
	this->IsSpawned = 1;
	this->IndexOfViewPort = indexOfVPort;

	//if (sizes.X == 0 && sizes.Y == 0)
	//	return;

	//if (abs(sizes.X) <= 1)
	//{
	//	if (sizes.X > 0)
	//		this->Sizes.X = sizes.X * this->D3dApp->GetViewPort(indexOfVPort).Width;
	//	else
	//		this->Sizes.X = abs(sizes.X) * this->D3dApp->GetViewPort(indexOfVPort).Height;
	//}
	//else
	//	this->Sizes.X = sizes.X;
	//if (abs(sizes.Y) <= 1)
	//{
	//	if (sizes.Y > 0)
	//		this->Sizes.Y = sizes.Y * this->D3dApp->GetViewPort(indexOfVPort).Height;
	//	else
	//		this->Sizes.Y = abs(sizes.Y) * this->D3dApp->GetViewPort(indexOfVPort).Width;
	//}
	//else
	//	this->Sizes.Y = sizes.Y;

}

//////////////////////////////////////////////////////////
//**Element
//////////////////////////////////////////////////////////
Element::Element(ElementsMLand* ptrToMotherLand)
	: ElementInterface(ptrToMotherLand)
{
	DeclareElementName(Element, this->EName);
	this->PMLand->AddNewElement(this);
}

