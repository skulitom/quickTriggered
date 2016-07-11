#include "Element.h"
//////////////////////////////////////////////////
//*ElementsMLand
//////////////////////////////////////////////////
ElementsMLand::ElementsMLand(D3DAPP* d3dApp, D3DAPPINPUT* input, Basic2DDraw* draw2D, std::string& saveBufferName)
{
	this->D3dApp = d3dApp;
	this->Input = input;
	this->Draw2D = draw2D;
	this->FManager = new FileManager(saveBufferName);
	this->Elements.resize(8);
}

ElementsMLand::~ElementsMLand()
{
	for (int i = 0; i < this->Elements.size(); i++)
		for (size_t j = 0; j < this->Elements.at(i).size(); j++)
		{
			D3DDelete(this->Elements.at(i).at(j));
		}
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
		this->Elements.at(pNewElement->GetIndexOfViewPort()).push_back(pNewElement);
		
	}

}
void ElementsMLand::DeleteElement(const UINT indexOfVP, const UINT indexOfElement)
{

	if (indexOfVP > this->D3dApp->GetNumOfVPorts() || indexOfVP < 0)
		return;

	D3DDelete(this->Elements.at(indexOfVP).at(indexOfElement));
	this->Elements.at(indexOfVP).erase(this->Elements.at(indexOfVP).begin() + indexOfElement);

}

void ElementsMLand::UpdateAndDraw(FLOAT deltaTime)
{
	int Index;
	for (int i = 0; i < this->Elements.size(); i++)
	{

		this->D3dApp->SetRenderTarget(this->D3dApp->GetVPRenderTV(i));
		Index = 0;
		//this->D3dApp->ClearScreen(XMFLOAT4(0, 1, 0, 1), this->D3dApp->GetVPRenderTV(i), this->D3dApp->MainDepth);
		while (Index < this->Elements.at(i).size())
		{
			if ((!this->Elements.at(i).at(Index)->GetIsFired()))
			{
				if (this->Elements.at(i).at(Index)->GetIsSpawned())
				{
					if (!this->IsLoadMode)
						this->Elements.at(i).at(Index)->Update(deltaTime);
					if (this->Elements.at(i).at(Index)->GetIsNeedRender())
					{
						if (this->Elements.at(i).at(Index)->GetShapeType() == EL_SHAPE_TYPE_RECTANGLE)
							this->Draw2D->DrawRectangle(this->Elements.at(i).at(Index)->GetPosition(), 
							this->Elements.at(i).at(Index)->GetSizes(), this->Elements.at(i).at(Index)->GetIndexOfViewPort(),
							this->Elements.at(i).at(Index)->GetCustomVars(),
							this->Elements.at(i).at(Index)->GetColors(), this->Elements.at(i).at(Index)->GetMaterial());
						else if (this->Elements.at(i).at(Index)->GetShapeType() == EL_SHAPE_TYPE_HEXAGON)
							this->Draw2D->DrawHexagon(this->Elements.at(i).at(Index)->GetPosition(),
							this->Elements.at(i).at(Index)->GetSizes(), this->Elements.at(i).at(Index)->GetIndexOfViewPort(),
							this->Elements.at(i).at(Index)->GetCustomVars(),
							this->Elements.at(i).at(Index)->GetColors(), this->Elements.at(i).at(Index)->GetMaterial());
					}
				}
				Index++;
			}
			else
				this->DeleteElement(i, Index);
		}

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

void ElementsMLand::LoadShaders()
{

	std::vector<std::string> Files = FileHelp::FindFiles(std::string("*.fx"));

	for (size_t i = 0; i < Files.size(); i++)
	{

		//if ()

	}

}

///////////////////////////////////////////////////
//**ElementInterface
///////////////////////////////////////////////////
ElementInterface::ElementInterface(ElementsMLand* ptrToMotherLand)
{

	this->IsNeedRender = 1;

	this->ShapeType = EL_SHAPE_TYPE_RECTANGLE;

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

bool ElementInterface::SetMaterial(std::string& materialName)
{
	this->MaterialPtr = this->D3dApp->GetMaterial(materialName);
	if (this->MaterialPtr)
	{
		PrepareShader(this->MaterialPtr, this->PMLand->GetDraw2D()->GetShaderManager());
		return true;
	}
	else
		return false;
}

bool ElementInterface::SetMaterial(Material* pMaterial)
{

	if (pMaterial)
	{

		this->MaterialPtr = pMaterial;
		return true;

	}

	return false;

}

//////////////////////////////////////////////////////////////////////
//**
//**@If indexOfVPort == -1 -> Default IndexOfVPort would
//**be applyed
//**@If 'X(Y)' < 1 -> ElementSize = VPortSize.X(Y) * 'X(Y)' formula
//**would be used
//**@If 'X(Y)' < 0 -> ElementSize = VPortSize.Y(X) * '|X(Y)|' formula
//**would be used
//**
//////////////////////////////////////////////////////////////////////
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

}

