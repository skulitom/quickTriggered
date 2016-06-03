#ifndef D3DAPP_H
#define D3DAPP_H
#include <Windows.h>
#include <windowsx.h>

#include "DXInclude\D3D11.h"
#include "DXInclude\D3DX10.h"
#include "DXInclude\D3DX11.h"
#include "DXInclude\xnamath.h"
#include "DXInclude\d3dx11effect.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Vector2d.h"

//#include "Shader.h"

#define D3DRelease(x){if(x) {x->Release() ; x = 0;}}
#define D3DDelete(x){if(x) {delete x; x = NULL;}}

#define DX_RS_DEPTH_RENDER_STATE 0
#define DX_RS_2D_RENDER_STATE 1

struct DepthStencilState
{

	DepthStencilState() { ZeroMemory(&this->PDepthStencilState, sizeof(ID3D11DepthStencilState)); }

	ID3D11DepthStencilState* PDepthStencilState;
	std::string Name;

};

struct WindowSizes
{

	WindowSizes() {};

	UINT ClientWWidth;
	UINT ClientWHeight;
	XMFLOAT2 WinPos;

	UINT LCOffSet;
	UINT RCOffSet;
	UINT TCOffSet;
	UINT BCOffSet;

};

// �������� ����� ���������� DX
class D3DAPP 
{
public:
	
	D3DAPP(bool Paused, bool Resizing, HWND hWnd);
	virtual ~D3DAPP();

	ID3D11Device* dxDevice;
	ID3D11DeviceContext* dxDeviceCon;
	IDXGISwapChain *dxSwapChain;
	ID3D11RenderTargetView* dxRenderTargetView;
	ID3D11DepthStencilView* dxDepthView;

	std::vector <DepthStencilState> dxDepthState;

	//ID3D11DepthStencilState* dxDepthState;
	ID3D11Texture2D *DepthBuffer;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	////������� ��� �������� ����������
	/////////////////////////////////////////////////////////////////////////////////////////////////

	// ������ ���� Windows
	HWND CreateD3DWindow(const HINSTANCE hInstance, LRESULT CALLBACK WINPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam),
		const int xPos, const int yPos, const int width, const int height, const LPSTR classname, const LPSTR winname, const UINT winType = WS_OVERLAPPEDWINDOW);
	// ������ ���� Windows
	void ShowD3DWindow(int cmd);
	// ��������� ���� Windows
	void CloseD3DWindow();

	//������ �������� ���������� DX
	bool DXCreateDeviceAndSwapChain(const int bufferCount, const int sampleDescCount, const bool isWindowed);
	// ������ Target view � Depth view
	bool DXCreateTargetViewAndDepthView(const int sampleDescCount);
	// ������ Depth stencil state
	bool DXCreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC& dsd, std::string& name);
	// �� ��������!
	void m4xMsaaQuality();


	// ���������� �� ����� ��������� ������� ���� Windows
	virtual void OnResize(); 
	// ���������� ������ � ������ ������(mWindowHeight,mWindowWidth)
	void UpdateWindowRect();
	// �������� ���� Windows � Depth view
	void ClearScreen(float r, float g, float b, float a, bool depthClear);
	// ������ �����
	virtual void Draw(); 
	// ������� ��� ���������� ��� �������� �������� ���������� DX
	virtual void ReleaseDefault();
	// ��������� �������
	virtual void SetStandartRenderSettings(D3D11_FILL_MODE fmode, D3D11_CULL_MODE cmode);

	virtual void SetPaused(bool pause);

	virtual bool SetDepthStencilStateByName(std::string& name);
	virtual bool SetDepthStencilStateByIndex(UINT index);

	// ���������� ���������� ���� Windows �� X
	virtual float GetWindowPosX();
	// ���������� ���������� ���� Windows �� Y
	virtual float GetWindowPosY(); 

	virtual bool GetPaused();

	virtual WindowSizes& GetWindowSizes();

	virtual XMFLOAT2& GetScreenSizes();

	UINT CreateViewPort(const FLOAT topLeftX, const FLOAT topLeftY,
		const FLOAT width, const FLOAT height, const FLOAT maxDepth, const FLOAT minDepth, const SHORT indexOfNewVPort = 0);
	bool SetViewPort(SHORT indexOfVPort);
	D3D11_VIEWPORT& GetViewPort(const SHORT indexOfVPort);

	bool SInit(int bufferCount, int sampleDestCount, bool windowed);

	void SetRenderSizesAndPos();

	// ���������� ����
	HWND GetWindow();

	virtual std::string& GetCatalogName();

	bool SLoadAllTextures();
	ID3D11ShaderResourceView* GetTextureViewPtr(std::string& textureName);

	bool GetIsInVPort(XMFLOAT2& pos,const short indexOfVPort);

	unsigned short GetNumOfVPorts(){ return this->NumOfVPorts; }

	ID3D11RasterizerState* GetStandartRastState() { return this->StandartRastState; }

public :

	ID3D11ShaderResourceView* CreateSShaderResourceView(ID3D11Texture2D* renderBufferTexture);
	ID3D11Texture2D* CreateSTexture2D(UINT width, UINT heigth, UINT bindFlags);
	ID3D11Buffer* CreateSVertexBuffer(bool dynamic, UINT size, UINT numOfElements);
	ID3D11Buffer* CreateSIndexBuffer(std::vector<UINT>& indexBuffer);
	ID3D11Buffer* CreateSConstantBuffer(UINT size);

private:

	void DeleteAllTextures();
	bool LoadTexture(std::string& textureName, std::string& path);

private:

	std::vector <ID3D11ShaderResourceView*> TextureViews;
	std::vector <std::string> TextureNames;

protected:

	unsigned short NumOfVPorts;

	// ��� ����(Windows)
	HWND HWnd;
	// �����������
	UINT MMsaa;

	// ���������� DX �� �����?
	bool IsPaused;
	// ����(Windows) ���������� DX ������ �������?
	bool IsResizing;

	// ���������� ����(Windows) �� X
	float WindowCoorX;
	// ���������� ����(Windows) �� y
	float WindowCoorY;

	WindowSizes WinSizes;
	XMFLOAT2 ScreenSizes;
	WindowSizes RenderSizes;

	std::string Catalog;

	bool LoopError;

	ID3D11RasterizerState* StandartRastState;

	D3D11_VIEWPORT ViewPorts[8];

};

#define DX_MOUSE_RELEASE 0x0
#define DX_MOUSE_DOWN_LEFT 0x1
#define DX_MOUSE_DOWN_RIGHT 0x2

// ����� DX ���������� �� ����
class D3DAPPINPUT
{
public:
	D3DAPPINPUT();
	~D3DAPPINPUT();

	// ����������, ���� ������ ������� ����
	void OnMouseDown(bool left = true);
	// ����������, ���� �������� ������� ����
	void OnMouseUp(bool left = true);
	// ����������, ���� ���� ��������
	void OnMouseMove(float CursorPosX, float CursorPosY);
	// ���������� ������� ����
	void MousePos(float CursorPosX, float CursorPosY);
	// ����������, ���� ������������ ������ ����
	void OnMouseScroll(float scrollUp);
	
	void SetWinSizes(WindowSizes& winSizes);

	// ���������� ���������� ���� �� �
	float GetMouseX();
	// ���������� ���������� ���� �� �
	float GetMouseY();
private:
	//���������� ���� �� �
	float mMouseX;
	//���������� ���� �� �
	float mMouseY;

public:
	//void InitMapMousePos(FLOAT windowWidth, FLOAT windowHeight, XMFLOAT3 cameraPos);

	FLOAT GetMapMousePosX(XMFLOAT4X4 mProject, XMFLOAT3 cameraPos);
	FLOAT GetMapMousePosY(XMFLOAT3 cameraPos);

	XMFLOAT3 GetCoordX(XMFLOAT3& objPos, XMFLOAT3 cameraPos);

	FLOAT GetMousePosXCenter(FLOAT shiftByX = 0);
	FLOAT GetMousePosYCenter(FLOAT shiftByY = 0);

	Vector2d GetMousePosCenterVPort(D3D11_VIEWPORT& viewPort);

	FLOAT GetMouseScroll();

	unsigned short GetStatus();

private:

	FLOAT mMapMouseX;
	FLOAT mMapMouseY;

	FLOAT MouseScroll;

	WindowSizes WinSizes;

	unsigned short Status;

};

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
}

#endif
