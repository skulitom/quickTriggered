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

	MathHelp::InitRand();

}

void BasicInterface::Draw()
{

	this->SetRenderTarget(this->dxRenderTargetView);

	for (UINT i = 1; i < this->NumOfVPorts; i++)
	{

		this->Draw2D->DrawRectangle(this->ViewPorts[i].WorldPos, Vector2d(this->ViewPorts[i].VPort.Width, this->ViewPorts[i].VPort.Height),
			0,XMFLOAT4(0,0,0,0), XMFLOAT4(0, 0, 0, 1), this->ViewPorts[i].MaterialToRender);
		//this->Draw2D->DrawRectangle(Vector2d(-50, 0), Vector2d(200, 200),
		//i, XMFLOAT4(0, 0, 0, 1), this->ViewPorts[i].TextureToRender);

	}

	D3DAPP::Draw();

}
