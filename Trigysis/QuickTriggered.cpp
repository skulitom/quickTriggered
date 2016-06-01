#include "QuickTriggered.h"

//////////////////////////////////////////////////////
//**QTButton
//////////////////////////////////////////////////////
QTButton::QTButton(ElementsMLand* ptrToMotherLand, ButtonSettings& bs)
:ButtonInterface(ptrToMotherLand, bs)
{
	DeclareElementName(CCButton, this->EName);
	this->Sizes = Vector2d(50, 30);
	this->PQTClass = dynamic_cast<QuickTriggered*>(this->D3dApp);
}

void QTButton::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, QTFunc qtf)
{
	switch (DX_BUTTON_FUNC_TYPE_)
	{
		case DX_BUTTON_FUNC_TYPE_ONSELECT:
		{
			this->QTFOnSelect = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONPRESS:
		{
			this->QTFOnPress = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONCLICK:
		{
			this->QTFOnClick = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
		{
			this->QTFOnStopInquisition = qtf;
			this->Feature |= DX_BUTTON_FEATUDE_ONSTOPINQUISITION;
			return;
		}
	}
}
//////////////////////////////////////////////////////
//**QuickTriggered
//////////////////////////////////////////////////////
bool QuickTriggered::InitApp()
{
	if (this->dxDevice)
	{
		/////////////////////////////////////
		//**Create Views
		/////////////////////////////////////

		this->SetStandartRenderSettings(D3D11_FILL_SOLID, D3D11_CULL_NONE);

		this->Input->SetWinSizes(this->WinSizes);

		this->ElementsBase = new ElementsMLand(this, this->Input);

		this->Draw2d = this->ElementsBase->GetDraw2D();

		/////////////////////////////////////
		//**Load Textures
		/////////////////////////////////////
		this->SLoadAllTextures();
		/////////////////////////////////////
		//**Create BackGrounds
		/////////////////////////////////////


		return true;

	}

	return false;
}

void QuickTriggered::Update(FLOAT deltaTime, FLOAT totalTime)
{
	

	////////////////////////////////////////////////
	//**Render Update
	////////////////////////////////////////////////
	QuickTriggered::ClearScreen(0, 0, 1, 1,true);

	this->ElementsBase->UpdateAndDraw(deltaTime);

	QuickTriggered::Draw();

}

void QuickTriggered::ReleaseDefault()
{
	D3DDelete(this->ElementsBase);
	D3DAPP::ReleaseDefault();
}