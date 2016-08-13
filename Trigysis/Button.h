#ifndef BUTTON_H
#define BUTTON_H
#include "BasicInterface.h"
#include "Element.h"
#define DX_BUTTON_FUNC_TYPE_ONSELECT 0
#define DX_BUTTON_FUNC_TYPE_ONPRESS 1
#define DX_BUTTON_FUNC_TYPE_ONCLICK 2
#define DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION 3

#define DX_BUTTON_STATUS_IS_ACTIVE		1
#define DX_BUTTON_STATUS_IS_PRESSING	2
#define DX_BUTTON_STATUS_WAS_PRESSED	4
#define DX_BUTTON_STATUS_CLICKED		8
#define DX_BUTTON_STATUS_WORKING		16
#define DX_BUTTON_STATUS_WAS_WORKING	32
#define DX_BUTTON_STATUS_IS_SELECT		64
#define DX_BUTTON_STATUS_WAS_SELECT		128
#define DX_BUTTON_STATUS_IS_EXECUTING	256
#define DX_BUTTON_STATUS_WAS_EXECUTE	512

#define DX_BUTTON_FEATURE_ONSELECT 0x1
#define DX_BUTTON_FEATURE_ONPRESS 0x2
#define DX_BUTTON_FEATURE_ONCLICK 0x4
#define DX_BUTTON_FEATURE_ONSTOPINQUISITION 0x8

#define DX_BUTTON_COLOR_STYLE_IDLE 1
#define DX_BUTTON_COLOR_STYLE_READY 2
#define DX_BUTTON_COLOR_STYLE_SUPPRESS 4
#define DX_BUTTON_COLOR_STYLE_INACTIVE 8

#define DX_BUTTON_MOUSE_USED_LEFT 0x1
#define DX_BUTTON_MOUSE_USED_RIGHT 0x2

struct ButtonSettings
{
	ButtonSettings()
	{
		this->IdleColor = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f);
		this->ReadyColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.f);
		this->SuppressColor = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.f);
		this->InActiveColor = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.f);
		this->MaterialName = std::string("");
		this->IsVisible = true; 
		this->IsActive = true; 
		this->IsLongTerm = false;
	}
	XMFLOAT4 IdleColor;
	XMFLOAT4 ReadyColor;
	XMFLOAT4 SuppressColor;
	XMFLOAT4 InActiveColor;
	std::string MaterialName;
	bool IsVisible;
	bool IsActive;
	bool IsLongTerm;
};

struct IndName
{
	IndName() { this->Name = 0; this->PtrNext = nullptr; }
	char* Name;
	IndName* PtrNext;
};

class ButtonInterface : public Element
{
public:
	ButtonInterface(BasicInterface* super, ButtonSettings& bs = ButtonSettings());
	virtual ~ButtonInterface(){ this->ReleaseIndNames(); }
	void ReleaseIndNames();
	void SetSettings(ButtonSettings& bSettings);
	ButtonSettings& GetSettings() { return this->Settings; }
	FLOAT GetPressTime() { return this->PressTime - 1.f; }
	bool GetStatus(unsigned __int16 DX_BUTTON_STATUS_) { return this->Status & DX_BUTTON_STATUS_; }
	bool Update() override;
	virtual void EventOnSelect(){};
	virtual void EventOnClick(){};
	virtual void EventOnPress(){};
	virtual void EventOnStopInquisition(){};
	void ToggleVisible(bool weakLink = false);
	void SetIsNeedRender(bool isNeedRender) override;
	virtual void SetColor(unsigned __int8 DX_BUTTON_COLOR_STYLE_, XMFLOAT4 color);
	void Disable(bool visibleOnEneble = true);
	void SetDone();
	void SetIndName(UINT prevLevel, char* name);
	char* GetIndName(UINT prevLevel);
private:
	bool CheckIsSelected();
	bool CheckIsPress(FLOAT deltaTime);
	bool CheckIsClick();
private:
	void SetStatus(unsigned __int16 DX_BUTTON_STATUS_, bool up = true) {
		if((this->Status & DX_BUTTON_STATUS_) != (DX_BUTTON_STATUS_ * up))
			this->Status = this->Status ^ (DX_BUTTON_STATUS_);
	}
	void ToggleStatus(unsigned __int16 DX_BUTTON_STATUS_) { this->Status ^= DX_BUTTON_STATUS_ ; }
private:
	FLOAT PressTime;
	ButtonSettings Settings;
	unsigned __int16 Status;
protected:
	unsigned __int8 Feature;
	unsigned __int8 MButtonUsed;
	bool IsCircle;
	IndName* IName;
};

//template<class BClass>
//class BOptionInterface : public Element
//{
//
//public:
//
//	BOptionInterface(BasicInterface* super);
//	virtual ~BOptionInterface();
//
//	void Show();
//	void Hide();
//
//	void Enable();
//	void Disable();
//
//	void EnableButton(UINT indexOfButton);
//	void DisableButton(UINT indexOfButton);
//
//	void AddButton(ButtonSettings bs, )
//
//private:
//
//	BClass* MButton;
//	std::vector<BClass*> Buttons;
//
//};

#endif //BUTTON_H
