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

	//this->ReleaseFromCache(this->Elements.at(indexOfVP).at(indexOfElement));

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
					if (!this->IsLoadMode && this->Elements.at(i).at(Index)->GetIsNeedUpdate())
					{
						this->Elements.at(i).at(Index)->Update();
						if (this->Elements.at(i).at(Index)->GetIsFired())
							this->ReleaseFromCache(this->Elements.at(i).at(Index));
					}
						
					this->Elements.at(i).at(Index)->Render();

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

void ElementsMLand::EPrecache(ElementInterface* element)
{

	if (!element)
		return;

	if (element->GetEName() == "")
		return;

	auto& It = this->Cache.find(std::string(element->GetEName()));
	if (It != std::end(this->Cache))
	{
		It->second.push_back(element);
		element->SetIndexInCache(It->second.size() - 1);
	}
	else
	{
		std::vector<ElementInterface*> NewBranch = { element };
		this->Cache.insert(std::pair<std::string, std::vector<ElementInterface*>>(element->GetEName(), NewBranch));
		element->SetIndexInCache(0);
	}


}

void ElementsMLand::ReleaseFromCache(ElementInterface* element)
{

	if (!element)
		return;
	if (!element->GetEName().compare(""))
		return;

	auto& It = this->Cache.find(std::string(element->GetEName()));
	if (It != std::end(this->Cache))
	{
		//It->second.erase(It->second.begin() + element->GetIndexInCache());
		It->second.at(element->GetIndexInCache()) = nullptr;
	}

}

std::vector<ElementInterface*>& ElementsMLand::Find(std::string& eName)
{

	if (!eName.compare(""))
		return std::vector<ElementInterface*>();

	auto& It = this->Cache.find(std::string(eName));
	if (It != std::end(this->Cache))
	{
		return It->second;
	}

	return std::vector<ElementInterface*>();

}

void ElementsMLand::ReleaseCache(/*char* key*/)
{

	//if (key)
	//{

	//	auto& It = this->Cache.find(std::string(key));
	//	if (It != std::end(this->Cache))
	//	{
	//		for (int i = 0; i < It->second.size(); i++)
	//			It->second.at(i) = nullptr;

	//		It->second.clear();
	//		It->second.shrink_to_fit();

	//	}

	//	return;

	//}
	//else
		this->Cache.clear();

}

///////////////////////////////////////////////////
//**ElementInterface
///////////////////////////////////////////////////
ElementInterface::ElementInterface(ElementsMLand* ptrToMotherLand)
{

	this->IsNeedRender = 1;
	this->IsNeedUpdate = 1;

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

void ElementInterface::Render()
{

	if (this->IsNeedRender)
	{

		if (!this->BState)
			this->BState = this->PMLand->GetD3DApp()->GetBlendState((UINT)DX_BS_BASIC);

		this->PMLand->GetD3DApp()->SetBlendState(this->BState);

		if (this->ShapeType == EL_SHAPE_TYPE_RECTANGLE)
		{
			this->PMLand->GetDraw2D()->DrawRectangle(this->Position, this->Rotation, this->Sizes, this->IndexOfViewPort, this->CustomVars, this->Color,
				this->MaterialPtr, this->Color);
		}
		else if (this->ShapeType == EL_SHAPE_TYPE_HEXAGON)
		{
			this->PMLand->GetDraw2D()->DrawHexagon(this->Position, this->Sizes, this->IndexOfViewPort, this->CustomVars, this->Color,
				this->MaterialPtr, this->Color);
		}

	}

}

bool ElementInterface::SetMaterial(std::string& materialName)
{
	this->MaterialPtr = this->D3dApp->GetMaterial(materialName);
	if (this->MaterialPtr)
	{
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

//void ElementInterface::SetEName(std::string& eName)
//{
//
//	this->EName = eName;
//
//}

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


