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
#include "SecondaryGame.h"
#include "Sound.h"

class QTButton : public ButtonInterface
{
public:
	QTButton(BasicInterface* super, ButtonSettings& bs = ButtonSettings());

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

	SecondaryGame *secondaryGame;
	PrimaryGame *primaryGame;
	FontManager* fontManager;

	Figure* FigToTest;			   
	
	SoundBasic* MainSound;

private:						   
								   
};								   
#endif //QuickTriggered_H		   
								   
