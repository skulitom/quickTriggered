#ifndef QuickTriggered_H
#define QuickTriggered_H

#include "ElementBaseManager.h"
#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
//#include "LogicalElement.h"
#include "Basic2DDraw.h"
//#include "Link.h"
#include "Files.h"

class QuickTriggered;
typedef void (QuickTriggered::*QTFunc)(void);
class CCButton : public ButtonInterface
{
public:
	CCButton(ElementsMLand* ptrToMotherLand, ButtonSettings& bs = ButtonSettings());
	void SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, QTFunc tf);
private:
	void EventOnSelect() {(this->PQTClass->*this->QTFOnSelect)();}
	void EventOnClick() { (this->PQTClass->*this->QTFOnClick)(); }
	void EventOnPress() { (this->PQTClass->*this->QTFOnPress)(); }
	void EventOnStopInquisition() { (this->PQTClass->*this->QTFOnStopInquisition)(); }
private:
	QTFunc QTFOnSelect;
	QTFunc QTFOnClick;
	QTFunc QTFOnPress;
	QTFunc QTFOnStopInquisition;
	QuickTriggered* PQTClass;
};

//////////////////////////////////////////////////////
//*QuickTriggered
//////////////////////////////////////////////////////
class QuickTriggered : public D3DAPP
{
public:
	QuickTriggered(HWND hWnd, D3DAPPINPUT* input) :D3DAPP(false, false, hWnd)
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
#endif //QuickTriggered_H
