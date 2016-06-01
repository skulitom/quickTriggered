#include "Button.h"

ButtonInterface::ButtonInterface(BasicInterface* super, ButtonSettings& bs)
	:Element(super)
{
	DeclareElementName(ButtonInterface, this->EName);
	this->SetSettings(bs);
}

void ButtonInterface::Disable(bool visibleOnEneble)
{
	this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE, !this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE));
	this->SetIsNeedRender(this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE) * visibleOnEneble);
}

void ButtonInterface::SetSettings(ButtonSettings& bSettings)
{
	this->Settings = bSettings;
	this->SetStatus(DX_BUTTON_STATUS_IS_ACTIVE, bSettings.IsActive);
	if (this->Settings.TextureName != "")
		this->SetTexture(this->Settings.TextureName);
	this->SetIsNeedRender(this->Settings.IsVisible);
}

bool ButtonInterface::CheckIsSelected()
{
	if (this->Settings.IsActive)
	{
		Vector2d HalfSizes = this->GetSizes() * 0.5f;
		Vector2d MousePos = this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->GetIndexOfViewPort()));
		FLOAT BRadius = HalfSizes.GetLength();
		HalfSizes = this->GetPosition() - MousePos;
		FLOAT Radius = HalfSizes.GetLength();
		if (Radius - BRadius <= 0)
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
	if ((this->Input->GetStatus()) && this->GetStatus(DX_BUTTON_STATUS_IS_SELECT))
	{
		this->MButtonUsed = 0;
		if (!(this->GetStatus(DX_BUTTON_STATUS_WAS_PRESSED)))
			this->PressTime = 1;
		this->PressTime += deltaTime;
		this->SetStatus(DX_BUTTON_STATUS_IS_PRESSING);
		return true;
	}
	this->SetStatus(DX_BUTTON_STATUS_IS_PRESSING, false);
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

bool ButtonInterface::Update(FLOAT deltaTime)
{
	if (!ElementInterface::Update(deltaTime))
		return false;
	if (!this->GetStatus(DX_BUTTON_STATUS_IS_ACTIVE))
	{
		this->SetColors(this->Settings.InActiveColor);
		return true;
	}
	this->SetStatus(DX_BUTTON_STATUS_WAS_SELECT, this->GetStatus(DX_BUTTON_STATUS_IS_SELECT));
	this->SetStatus(DX_BUTTON_STATUS_IS_SELECT | DX_BUTTON_STATUS_WORKING, this->CheckIsSelected());
	if (this->CheckIsPress(deltaTime))
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
			if (this->GetStatus(DX_BUTTON_STATUS_WAS_SELECT) && (this->Feature & DX_BUTTON_FEATUDE_ONSTOPINQUISITION))
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