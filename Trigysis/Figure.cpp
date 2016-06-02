#include "Figures.h"

//////////////////////////////////////////////////////
//**CCButton
//////////////////////////////////////////////////////
FButton::FButton(BasicInterface* super)
	:ButtonInterface(super)
{
	DeclareElementName(FButton, this->EName);
	this->PFigureClass = dynamic_cast<Figure*>(this->D3dApp);
	ButtonSettings BS;
	BS.IdleColor = XMFLOAT4(0.5f, 0.5f, 0.5f, 1);
	BS.InActiveColor = XMFLOAT4(1, 1, 1, 1);
	BS.ReadyColor = XMFLOAT4(0.4f, 0.4f, 0.4f, 1);
	BS.SuppressColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1);
	BS.IsActive = true;
	BS.IsLongTerm = true;
	BS.IsVisible = true;
	
	this->SetSettings(BS);

}

void FButton::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, FFunc ff)
{
	switch (DX_BUTTON_FUNC_TYPE_)
	{
	case DX_BUTTON_FUNC_TYPE_ONSELECT:
	{
		this->FFOnSelect = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONPRESS:
	{
		this->FFOnPress = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONCLICK:
	{
		this->FFOnClick = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
	{
		this->FFOnStopInquisition = ff;
		this->Feature |= DX_BUTTON_FEATUDE_ONSTOPINQUISITION;
		return;
	}
	}
}

//////////////////////////////////////////////////////
//**Figure
//////////////////////////////////////////////////////

Figure::Figure(BasicInterface* super)
	:Element(super)
{



}

Figure::~Figure()
{



}

void Figure::Spawn(Vector2d& position, short indexOfVPort)
{

	

}