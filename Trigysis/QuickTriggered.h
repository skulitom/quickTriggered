#ifndef QuickTriggered_H
#define QuickTriggered_H

#include "ElementBaseManager.h"
#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
#include "BasicInterface.h"
#include "GUIFigures.h"
//#include "LogicalElement.h"
#include "Basic2DDraw.h"
//#include "Link.h"
#include "Files.h"
#include "Font.h"
#include "PrimaryGame.h"


class QuickTriggered;
typedef void (QuickTriggered::*QTFunc)(void);
class QTButton : public ButtonInterface
{
public:
	QTButton(BasicInterface* super, ButtonSettings& bs = ButtonSettings());
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
class QuickTriggered : public BasicInterface
{
public:
	QuickTriggered(HWND hWnd, D3DAPPINPUT* input) : BasicInterface(false, true, hWnd, input)
	{}
	void ReleaseDefault() override;
	bool InitApp();
	void Update();
	void InitVPorts();
	void Resize(enum EDisplayModes mode) override;
private:
	/////////////////////////////
	//**Functions for buttons
	/////////////////////////////

	//TestPipeline* TPipeline;
	void createFigure(int x, int y);
	void setBoard();

	
	PrimaryGame *primaryGame;
	FontManager* fontManager;

	Figure* FigToTest;

private:

};
#endif //QuickTriggered_H
