#ifndef FastTriggered_H
#define FastTriggered_H

#include "ElementBaseManager.h"
#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
//#include "LogicalElement.h"
#include "Basic2DDraw.h"
//#include "Link.h"
#include "Files.h"

class FastTriggered;
typedef void (FastTriggered::*TFunc)(void);
class CCButton : public ButtonInterface
{
public:
	CCButton(ElementsMLand* ptrToMotherLand, ButtonSettings& bs = ButtonSettings());
	void SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, TFunc tf);
private:
	void EventOnSelect() {(this->PTrigClass->*this->TFOnSelect)();}
	void EventOnClick() { (this->PTrigClass->*this->TFOnClick)(); }
	void EventOnPress() { (this->PTrigClass->*this->TFOnPress)(); }
	void EventOnStopInquisition() { (this->PTrigClass->*this->TFOnStopInquisition)(); }
private:
	TFunc TFOnSelect;
	TFunc TFOnClick;
	TFunc TFOnPress;
	TFunc TFOnStopInquisition;
	FastTriggered* PTrigClass;
};
class FastTriggered : public D3DAPP
{
public:
	FastTriggered(HWND hWnd, D3DAPPINPUT* input) :D3DAPP(false, false, hWnd)
	{	this->Input = input;}
	void ReleaseDefault() override;
	bool InitApp();
	void Update(FLOAT deltaTime, FLOAT totalTime);
private:
	/////////////////////////////
	//**Functions for buttons
	/////////////////////////////

private:

	D3DAPPINPUT* Input;
	Basic2DDraw* Draw2d;

	ElementsMLand* ElementsBase;

};
#endif //FastTriggered_H