#ifndef BASIC_INTERFACE_H
#define BASIC_INTERFACE_H

#include "D3DAPP.h"
#include "Vector2d.h"
#include "Files.h"
#include "BasicElement.h"
#include "Timer.h"
#include "Basic2DDraw.h"
#include "MathHelper.h"
#include "Font.h"
#include "Sound.h"

class BasicInterface : public D3DAPP
{

public:

	BasicInterface(bool paused, bool resizing, HWND hWnd, D3DAPPINPUT* input);
	virtual ~BasicInterface();

	void Init();

	Basic2DDraw* GetDraw2D() { return this->Draw2D; }
	ElementsMLand* GetElementBase() { return this->ElementBase; }
	D3DAPPINPUT* GetInput() { return this->Input; }
	FontManager* GetFont2D() { return this->Font2D; }
	SoundBasic* GetSound() { return this->BSound; }

	void Draw() override;

	virtual void ReleaseDefault() override;
	virtual void Resize(enum EDisplayModes mode) override;

	//D3DAPPTIMER* GetTimer() { return this->Timer; }

private:

	short Special;
	float Smooth;

protected:

	void InitVPShaders();

protected:

	Basic2DDraw* Draw2D;
	ElementsMLand* ElementBase;
	FontManager* Font2D;

	SoundBasic* BSound;

	D3DAPPINPUT* Input;
	//D3DAPPTIMER* Timer;

};

#endif // !BASIC_INTERFACE_H


