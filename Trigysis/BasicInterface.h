#ifndef BASIC_INTERFACE_H
#define BASIC_INTERFACE_H

#include "D3DAPP.h"
#include "Vector2d.h"
#include "Files.h"
#include "BasicElement.h"
#include "Timer.h"
#include "Basic2DDraw.h"

class BasicInterface : public D3DAPP
{

public:

	BasicInterface(bool paused, bool resizing, HWND hWnd, D3DAPPINPUT* input);
	virtual ~BasicInterface();

	void Init();

	Basic2DDraw* GetDraw2D() { return this->Draw2D; }
	ElementsMLand* GetElementBase() { return this->ElementBase; }
	D3DAPPINPUT* GetInput() { return this->Input; }

private:

protected:

	Basic2DDraw* Draw2D;
	ElementsMLand* ElementBase;

	D3DAPPINPUT* Input;

};

#endif // !BASIC_INTERFACE_H


