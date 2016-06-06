#include "GUIFigures.h"

//////////////////////////////////////////////////////
//**CCButton
//////////////////////////////////////////////////////
FButton::FButton(BasicInterface* super)
	:ButtonInterface(super)
{
	DeclareElementName(FButton, this->EName);
	this->PFigureClass = dynamic_cast<Figure*>(this->D3dApp);
	ButtonSettings BS;
	BS.IdleColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.f);
	BS.InActiveColor = XMFLOAT4(1, 1, 1, 0.f);
	BS.ReadyColor = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.f);
	BS.SuppressColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.f);
	BS.IsActive = true;
	BS.IsLongTerm = true;
	BS.IsVisible = true;
	
	this->SetSettings(BS);

	this->Sizes = Vector2d(GUIF_SIZE, GUIF_SIZE);

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
		this->Feature |= DX_BUTTON_FEATURE_ONSTOPINQUISITION;
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

	this->Sizes = Vector2d(GUIF_SIZE, GUIF_SIZE);
	this->Color = XMFLOAT4(1, 1, 1, 1);

	this->FrontButton = new FButton(super);
	Figure::SetFigureSuperType(0);

}

Figure::~Figure()
{



}

void Figure::Spawn(Vector2d& position, short indexOfVPort)
{
	Element::Spawn(position, indexOfVPort);
	
	this->FrontButton->Spawn(position, indexOfVPort);

}

void Figure::SetFigureSuperType(UINT sType)
{

	this->SType = sType;
	
	if (this->FrontButton)
	{
		std::string TName;
		switch (this->SType)
		{

			case 0:
			{

				TName = "DTBF.dds";
				break;

			}
			default:
			{
				TName = "DTHD.dds";
			}

		}

		this->FrontButton->SetTexture(TName);

	}

}

void Figure::SetFigureType(UINT type)
{

	this->Type = type;

	switch (this->Type)
	{

		case 0:
		{
			this->Color = XMFLOAT4(1, 0, 0, 1);
			break;
		}
		default :
		{
			this->Color = XMFLOAT4(1, 1, 1, 1);
			break;
		}

	}

}

void Figure::Move(int dPosX, int dPosY, float deltaTime)
{



}

bool Figure::Update(float deltaTime)
{

	if (!Element::Update(deltaTime))
		return false;

	this->FrontButton->SetPosition(this->Position);

}