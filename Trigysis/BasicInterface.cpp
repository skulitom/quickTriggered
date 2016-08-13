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
	this->Font2D = new FontManager(this, this->Draw2D, "ArialFont.txt");

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

	this->Draw2D->GetShaderManager()->SetIsAdvanceRender(true);

	for (UINT i = 1; i < this->NumOfVPorts; i++)
	{

		this->Draw2D->DrawRectangle(this->ViewPorts[i].WorldPos, Vector2d(this->ViewPorts[i].VPort.Width, this->ViewPorts[i].VPort.Height),
			0, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(0, 0, 0, 1), this->ViewPorts[i].MaterialToRender);

	}

	this->Draw2D->GetShaderManager()->SetIsAdvanceRender(false);

	D3DAPP::Draw();

}
