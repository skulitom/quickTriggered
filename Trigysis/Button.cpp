#include "Button.h"

ButtonInterface::ButtonInterface(BasicInterface* super, ButtonSettings& bs)
	:Element(super)
{
	DeclareElementName(ButtonInterface, this->EName);
	this->SetSettings(bs);
	this->TIsConstant = true;
}

void ButtonInterface::Disable(bool visibleOnEneble)
{
	this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE, !this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE));
	this->SetIsNeedRender(this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE) * visibleOnEneble);
}

void ButtonInterface::ReleaseIndNames()
{

	IndName* INToDelete = this->IName;
	IndName* T = nullptr;
	while (true)
	{

		if (INToDelete)
			if (INToDelete->PtrNext)
				T = INToDelete->PtrNext;
		D3DDelete(INToDelete);
		if (T)
		{
			INToDelete = T;
			T = nullptr;
		}
		else
			break;

	}

}

void ButtonInterface::SetIndName(UINT prevLevel, char* name)
{

	//IName->NPtr->NPtr->NPtr;
	//NPtr = new 

	IndName* CIName = this->IName;
	if (!prevLevel)
	{
		CIName = new IndName();
		this->IName = CIName;
	}
	else
	{
		IndName* T;
		for (int i = 0; i < prevLevel; i++)
		{
			T = new IndName();
			CIName->PtrNext = T;
			CIName = CIName->PtrNext;
		}
	}

	CIName->Name = name;

}

char* ButtonInterface::GetIndName(UINT prev)
{

	IndName* CIName = this->IName;
	if (!CIName)
		return "";
	for (int i = 0; i < prev; i++)
	{
		if (!CIName)
			return "";
		CIName = CIName->PtrNext;

	}

	return CIName->Name;

}

void ButtonInterface::SetSettings(ButtonSettings& bSettings)
{
	this->Settings = bSettings;
	this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE, bSettings.IsActive);
	if (this->Settings.MaterialName != "")
		this->SetMaterial(this->Settings.MaterialName);
	this->SetIsNeedRender(this->Settings.IsVisible);
}

bool ButtonInterface::CheckIsSelected()
{
	if (this->Settings.IsActive)
	{

		if (this->Input->GetStatus(DX_MOUSE_DOWN_LEFT | DX_MOUSE_DOWN_RIGHT) && !this->GetStatus(DX_BUTTON_STATUS_IS_SELECT))
			return false;

		Vector2d HalfSizes = this->GetSizes() * 0.5f;
		Vector2d MousePos;
		this->Input->GetMousePosCenterVPort(this->D3dApp->GetVPStruct(this->GetIndexOfViewPort()),&MousePos);
		FLOAT BRadius = HalfSizes.GetLength() * 0.707f;
		HalfSizes = this->GetPosition() - MousePos;
		FLOAT Radius = HalfSizes.GetLength();

		if (this->IsCircle)
		{

			BRadius = BRadius * 0.866f;
			if (Radius - BRadius <= 0)
				return true;
			return false;
		}

		if (Radius - BRadius * 2.f <= 0)
		{

			if (MousePos.X < this->GetPosition().X - this->GetSizes().X * 0.5f || MousePos.X > this->GetPosition().X + this->GetSizes().X * 0.5f)
				return false;
			if (MousePos.Y < this->GetPosition().Y - this->GetSizes().Y * 0.5f || MousePos.Y > this->GetPosition().Y + this->GetSizes().Y * 0.5f)
				return false;
			return true;
		}
		return false;
	}
	return false;
}

bool ButtonInterface::CheckIsPress(FLOAT deltaTime)
{
	this->SetStatus(DX_BUTTON_STATUS_WAS_PRESSED,this->GetStatus(DX_BUTTON_STATUS_IS_PRESSING));

	if ((this->Input->GetStatus() && this->GetStatus(DX_BUTTON_STATUS_IS_SELECT) && 
		this->Input->CheckNewGUIButton(this, this->GetStatus(DX_BUTTON_STATUS_IS_PRESSING))) || 
		(this->Input->GetStatus() && this->GetStatus(DX_BUTTON_STATUS_IS_PRESSING) && 
		this->Input->CheckNewGUIButton(this, this->GetStatus(DX_BUTTON_STATUS_IS_PRESSING))))
	{
			
		this->MButtonUsed = 0;
		if (!(this->GetStatus(DX_BUTTON_STATUS_WAS_PRESSED)))
			this->PressTime = 1;
		this->PressTime += deltaTime;
		this->SetStatus(DX_BUTTON_STATUS_IS_PRESSING);
		return true;
	}
	this->SetStatus(DX_BUTTON_STATUS_IS_PRESSING, false);
	if (this->Input->GetGUIButtonPtr() == this)
		this->Input->ClearGUIButton();
	return false;
}

bool ButtonInterface::CheckIsClick()
{
	if (this->PressTime >= 1 && this->PressTime <= 1.5f && this->GetStatus(DX_BUTTON_STATUS_WAS_PRESSED))
	{
		this->PressTime = 0;
		this->SetStatus(DX_BUTTON_STATUS_CLICKED);
		if (this->GetSettings().IsLongTerm)
		{
			if (!this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
			{
				this->SetStatus(DX_BUTTON_STATUS_IS_EXECUTING);
				this->SetStatus(DX_BUTTON_STATUS_WAS_EXECUTE, false);
			}
			else
			{
				this->SetStatus(DX_BUTTON_STATUS_IS_EXECUTING, false);
				this->SetStatus(DX_BUTTON_STATUS_WAS_EXECUTE);
			}

		}
		return true;
	}
	this->SetStatus(DX_BUTTON_STATUS_CLICKED, false);
	return false;
}

void ButtonInterface::ToggleVisible(bool weakLink)
{
	if (this->Settings.IsVisible)
	{
		this->Settings.IsVisible = false;
		{
			this->Settings.IsActive = false;
			this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE, false);
		}
	}
	else
	{
		this->Settings.IsVisible = true;
		if (weakLink)
			this->Settings.IsActive = this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE);
		else
		{
			this->Settings.IsActive = true;
			this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE);
		}
	}
	ElementInterface::SetIsNeedRender(this->Settings.IsVisible);
}

void ButtonInterface::SetIsNeedRender(bool isNeedRender)
{
	ElementInterface::SetIsNeedRender(isNeedRender);
	this->Settings.IsVisible = isNeedRender;
}

void ButtonInterface::SetDone() 
{ 
	if (this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
		this->SetStatus(DX_BUTTON_STATUS_WAS_EXECUTE); 
}

void ButtonInterface::SetColor(unsigned __int8 DX_BUTTON_COLOR_STYLE_, XMFLOAT4 color)
{
	if (DX_BUTTON_COLOR_STYLE_ & DX_BUTTON_COLOR_STYLE_IDLE)
		this->Settings.IdleColor = color;
	if (DX_BUTTON_COLOR_STYLE_ & DX_BUTTON_COLOR_STYLE_INACTIVE)
		this->Settings.InActiveColor = color;
	if (DX_BUTTON_COLOR_STYLE_ & DX_BUTTON_COLOR_STYLE_READY)
		this->Settings.ReadyColor = color;
	if (DX_BUTTON_COLOR_STYLE_ & DX_BUTTON_COLOR_STYLE_SUPPRESS)
		this->Settings.SuppressColor = color;
}

bool ButtonInterface::Update()
{
	if (!ElementInterface::Update())
		return false;
	if (!this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE))
	{
		this->SetColors(this->Settings.InActiveColor);
		return true;
	}
	this->SetStatus(DX_BUTTON_STATUS_WAS_SELECT, this->GetStatus(DX_BUTTON_STATUS_IS_SELECT));
	this->SetStatus(DX_BUTTON_STATUS_IS_SELECT | DX_BUTTON_STATUS_WORKING, this->CheckIsSelected());
	
	if (this->GetStatus(DX_BUTTON_STATUS_IS_SELECT) && !( this->GetStatus(DX_BUTTON_STATUS_WAS_SELECT)))
		this->Super->GetSound()->Play(std::string("ButtonSelect.wav"), 65);

	if (this->GetStatus(DX_BUTTON_STATUS_IS_SELECT) && this->GetStatus(DX_BUTTON_STATUS_WAS_SELECT))

	if (this->CheckIsPress(this->D3dApp->GetTimer()->GetDeltaTime()))
	{
		this->SetColors(this->Settings.SuppressColor);
		if (this->Feature & DX_BUTTON_FEATURE_ONPRESS)
			this->EventOnPress();
	}
	if (!(this->GetStatus(DX_BUTTON_STATUS_IS_PRESSING)))
	{
		if (this->CheckIsClick() )
		{
			if (this->Feature & DX_BUTTON_FEATURE_ONCLICK)
				this->EventOnClick();
		}
		if (this->GetStatus(DX_BUTTON_STATUS_IS_SELECT))
		{
			if (!this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
				this->SetColors(this->Settings.ReadyColor);
			if (this->Feature & DX_BUTTON_FEATURE_ONSELECT)
				this->EventOnSelect();
		}
		else
		{
			if (!this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
				this->SetColors(this->Settings.IdleColor);
			if (this->GetStatus(DX_BUTTON_STATUS_WAS_SELECT) && (this->Feature & DX_BUTTON_FEATURE_ONSTOPINQUISITION))
				this->EventOnStopInquisition();
			if (!this->GetStatus(DX_BUTTON_STATUS_WORKING) && this->GetStatus(DX_BUTTON_STATUS_WAS_WORKING))
				this->ToggleStatus(DX_BUTTON_STATUS_WAS_WORKING);
			this->SetStatus(DX_BUTTON_STATUS_WORKING, false);
		}

		if (this->GetStatus(DX_BUTTON_STATUS_WAS_EXECUTE))
		{

			if (!this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
				this->SetStatus(DX_BUTTON_STATUS_WAS_EXECUTE,false);

			if (this->GetStatus(DX_BUTTON_STATUS_IS_EXECUTING))
				this->SetStatus(DX_BUTTON_STATUS_IS_EXECUTING, false);
		}

	}
	return true;
}

void ButtonInterface::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, void(*func)(void*), void* arg)
{

	this->Arg = arg;

	switch (DX_BUTTON_FUNC_TYPE_)
	{
	case DX_BUTTON_FUNC_TYPE_ONSELECT:
	{
		this->FuncOnSelect = func;
		this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONPRESS:
	{
		this->FuncOnPress = func;
		this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONCLICK:
	{
		this->FuncOnClick = func;
		this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
	{
		this->FuncOnStopInquisition = func;
		this->Feature |= DX_BUTTON_FEATURE_ONSTOPINQUISITION;
		return;
	}
	}

}
