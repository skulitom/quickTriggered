#include "BasicInterface.h"

BasicInterface::BasicInterface(bool paused, bool resizing, HWND hWnd, D3DAPPINPUT* input)
	:D3DAPP(paused, resizing, hWnd)
{

	this->Input = input;

}

BasicInterface::~BasicInterface()
{

	D3DDelete(this->ElementBase);
	D3DDelete(this->Draw2D);

}

void BasicInterface::Init()
{

	this->Draw2D = new Basic2DDraw(this);
	this->ElementBase = new ElementsMLand(this, this->Input, Draw2D);

}