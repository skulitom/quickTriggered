#include "FastTriggered.h"

//////////////////////////////////////////////////////
//**CCButton
//////////////////////////////////////////////////////
CCButton::CCButton(ElementsMLand* ptrToMotherLand, ButtonSettings& bs)
:ButtonInterface(ptrToMotherLand, bs)
{
	DeclareElementName(CCButton, this->EName);
	this->PTrigClass = dynamic_cast<FastTriggered*>(this->D3dApp);
}

void CCButton::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, TFunc tf)
{
	switch (DX_BUTTON_FUNC_TYPE_)
	{
		case DX_BUTTON_FUNC_TYPE_ONSELECT:
		{
			this->TFOnSelect = tf;
			this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONPRESS:
		{
			this->TFOnPress = tf;
			this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONCLICK:
		{
			this->TFOnClick = tf;
			this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
		{
			this->TFOnStopInquisition = tf;
			this->Feature |= DX_BUTTON_FEATUDE_ONSTOPINQUISITION;
			return;
		}
	}
}
//////////////////////////////////////////////////////
//**FastTriggered
//////////////////////////////////////////////////////
bool FastTriggered::InitApp()
{
	if (this->dxDevice)
	{
		/////////////////////////////////////
		//**Create Views
		/////////////////////////////////////

		this->SetStandartRenderSettings(D3D11_FILL_SOLID, D3D11_CULL_NONE);

		this->Draw2d = new Basic2DDraw(this);

		this->Input->SetWinSizes(this->WinSizes);

		this->ElementsBase = new ElementsMLand(this, this->Input, std::string("TestSave.txt"));

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

void FastTriggered::Update(FLOAT deltaTime, FLOAT totalTime)
{

	//New Line

}

void FastTriggered::ReleaseDefault()
{
	D3DDelete(this->Draw2d);
	D3DDelete(this->ElementsBase);
	D3DAPP::ReleaseDefault();
}