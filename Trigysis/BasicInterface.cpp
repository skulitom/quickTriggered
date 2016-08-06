#include "BasicInterface.h"

BasicInterface::BasicInterface(bool paused, bool resizing, HWND hWnd, D3DAPPINPUT* input)
	:D3DAPP(paused, resizing, hWnd)
{

	this->Input = input;

}

void BasicInterface::ReleaseDefault()
{

	D3DDelete(this->ElementBase);
	D3DDelete(this->Draw2D);
	D3DDelete(this->Font2D);

	D3DAPP::ReleaseDefault();

}

BasicInterface::~BasicInterface()
{



}

void BasicInterface::Init()
{

	this->SInitMaterials();

	this->Draw2D = new Basic2DDraw(this);
	this->ElementBase = new ElementsMLand(this, this->Input, Draw2D);
	this->Font2D = new FontManager(this, this->Draw2D, "ArialFontTiny.txt");

	MathHelp::InitRand();

}

void BasicInterface::InitVPShaders()
{

	for (int i = 1; i < this->NumOfVPorts; i++)
	{

		PrepareShader(this->ViewPorts[i].MaterialToRender, this->Draw2D->GetShaderManager());

	}

}

void BasicInterface::Resize(enum EDisplayModes mode)
{

	D3DAPP::Resize(mode);

}

void BasicInterface::Draw()
{

	this->SetRenderTarget(this->MainRenderTarget);

	Vector2d MousePos = this->Input->GetMousePosCenterVPort(this->ViewPorts[1]);

	if (GetAsyncKeyState(VK_F2))
		Special = 1;
	if (GetAsyncKeyState(VK_F1))
		Special = 0;
	if (GetAsyncKeyState(VK_F3))
		Special = 2;

	if (GetAsyncKeyState(VK_NUMPAD6))
		this->Smooth = this->Smooth + 0.01;
	else if (GetAsyncKeyState(VK_NUMPAD4))
		this->Smooth = this->Smooth - 0.01;

	this->Draw2D->GetShaderManager()->SetIsAdvanceRender(true);

	for (UINT i = 1; i < this->NumOfVPorts; i++)
	{

		this->Draw2D->DrawRectangle(this->ViewPorts[i].WorldPos, Vector2d(this->ViewPorts[i].VPort.Width, this->ViewPorts[i].VPort.Height),
			0, XMFLOAT4(MousePos.X, MousePos.Y, Special, this->Smooth), XMFLOAT4(0, 0, 0, 1), this->ViewPorts[i].MaterialToRender);
		//this->Draw2D->DrawRectangle(Vector2d(-50, 0), Vector2d(200, 200),
		//i, XMFLOAT4(0, 0, 0, 1), this->ViewPorts[i].TextureToRender);

	}

	this->Draw2D->GetShaderManager()->SetIsAdvanceRender(false);

	D3DAPP::Draw();

}
