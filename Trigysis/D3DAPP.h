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

// Основной класс приложения DX
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
	////Функции для создания приложения
	/////////////////////////////////////////////////////////////////////////////////////////////////

	// Создаёт окно Windows
	HWND CreateD3DWindow(const HINSTANCE hInstance, LRESULT CALLBACK WINPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam),
		const int xPos, const int yPos, const int width, const int height, const LPSTR classname, const LPSTR winname, const UINT winType = WS_OVERLAPPEDWINDOW);
	// Рисует окно Windows
	void ShowD3DWindow(int cmd);
	// Закрывает окно Windows
	void CloseD3DWindow();

	//Создаёт основные устройства DX
	bool DXCreateDeviceAndSwapChain(const int bufferCount, const int sampleDescCount, const bool isWindowed);
	// Создаёт Target view и Depth view
	bool DXCreateTargetViewAndDepthView(const int sampleDescCount);
	// Создаёт Depth stencil state
	bool DXCreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC& dsd, std::string& name);
	// НЕ РАБОТАЕТ!
	void m4xMsaaQuality();


	// Вызывается во время изменения размера окна Windows
	virtual void OnResize(); 
	// Возвращает высоту и ширину экрана(mWindowHeight,mWindowWidth)
	void UpdateWindowRect();
	// Отчищает окно Windows и Depth view
	void ClearScreen(float r, float g, float b, float a, bool depthClear);
	// Рисует сцену
	virtual void Draw(); 
	// Удаляет все устройства для создания базового приложения DX
	virtual void ReleaseDefault();
	// Настройка рендера
	virtual void SetStandartRenderSettings(D3D11_FILL_MODE fmode, D3D11_CULL_MODE cmode);

	virtual void SetPaused(bool pause);

	virtual bool SetDepthStencilStateByName(std::string& name);
	virtual bool SetDepthStencilStateByIndex(UINT index);

	// Возвращает координаты окна Windows по X
	virtual float GetWindowPosX();
	// Возвращает координаты окна Windows по Y
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

	// Возвращает окно
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

	// Имя окна(Windows)
	HWND HWnd;
	// Сглаживание
	UINT MMsaa;

	// Приложение DX на паузе?
	bool IsPaused;
	// Окно(Windows) приложения DX меняет размеры?
	bool IsResizing;

	// Координаты окна(Windows) по X
	float WindowCoorX;
	// Координаты окна(Windows) по y
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

// Класс DX отвечающий за ввод
class D3DAPPINPUT
{
public:
	D3DAPPINPUT();
	~D3DAPPINPUT();

	// Вызывается, если зажата клавиша мыши
	void OnMouseDown(bool left = true);
	// Вызывается, если отпущена клавиша мыши
	void OnMouseUp(bool left = true);
	// Вызывается, если мышь движется
	void OnMouseMove(float CursorPosX, float CursorPosY);
	// Записывает позиции мыши
	void MousePos(float CursorPosX, float CursorPosY);
	// Вызывается, если используется колесо мыши
	void OnMouseScroll(float scrollUp);
	
	void SetWinSizes(WindowSizes& winSizes);

	// Возвращает координаты мыши по Х
	float GetMouseX();
	// Возвращает координаты мыши по У
	float GetMouseY();
private:
	//координаты мыши по Х
	float mMouseX;
	//координаты мыши по У
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
