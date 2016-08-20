#ifndef D3DAPP_H
#define D3DAPP_H
#include <Windows.h>
#include <windowsx.h>

#include "DXInclude\D3D11.h"
#include "DXInclude\D3DX10.h"
#include "DXInclude\D3DX11.h"
#include "DXInclude\xnamath.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Vector2d.h"
#include "Files.h"
#include "Timer.h"
#include "Camera.h"

#pragma comment(lib, "dxgi.lib")
//#include "Shader.h"
#pragma warning(disable : 4996)
#define D3DRelease(x){if(x) {x->Release() ; x = 0;}}
#define D3DDelete(x){if(x) {delete x; x = NULL;}}

#define DX_RS_DEPTH_RENDER_STATE 0
#define DX_RS_2D_RENDER_STATE 1

#define DX_BS_BASIC 0
#define DX_BS_TRANSPARENCY 1

#define COLOR_BLACK_3 XMFLOAT3(0,0,0)
#define COLOR_RED_3 XMFLOAT3(1,0,0)
#define COLOR_GREEN_3 XMFLOAT3(0,1,0)
#define COLOR_BLUE_3 XMFLOAT3(0,0,1)
#define COLOR_YELLOW_3 XMFLOAT3(1,1,0)
#define COLOR_PURPLE_3 XMFLOAT3(1,0,1)
#define COLOR_LBLUE_3 XMFLOAT3(0,1,1)
#define COLOR_WHITE_3 XMFLOAT3(1,1,1)

enum EDisplayModes
{

	DX_DISPLAY_MODE_FULL_SCREEN = 0,
	DX_DISPLAY_MODE_640_480,
	DX_DISPLAY_MODE_800_600,
	DX_DISPLAY_MODE_1024_768,
	DX_DISPLAY_MODE_1152_864,
	DX_DISPLAY_MODE_1280_600,
	DX_DISPLAY_MODE_1280_720,
	DX_DISPLAY_MODE_1280_768,
	DX_DISPLAY_MODE_1280_1024,
	DX_DISPLAY_MODE_1360_768,
	DX_DISPLAY_MODE_1366_768,
	DX_DISPLAY_MODE_1440_900,
	DX_DISPLAY_MODE_1600_900,
	DX_DISPLAY_MODE_1600_1024,
	DX_DISPLAY_MODE_1600_1200,
	DX_DISPLAY_MODE_1680_1050,
	DX_DISPLAY_MODE_1920_1080

};

struct TextureStruct
{
	TextureStruct() { Texture = nullptr; }
	ID3D11ShaderResourceView* Texture;
	std::string TextureName;
};

struct Material
{

	Material() { 
		Texture = nullptr; 
		AdditionalTexture = nullptr; 
		EffectShader = nullptr; 
		TextureMove = XMFLOAT4(0, 0, 0, 0);
		TextureOffset = XMFLOAT4(0, 0, 0, 0);
		Scale = XMFLOAT2(1,1);
		UseGlobalCoords = false;
		UseAlpha = false;
		LSize = XMFLOAT2(0, 0);
		Animate = XMSHORT4((short)0, (short)0, (short)0, (short)0);
		LFrameTime = 0;
		LFrameIndex = 0;
	}

	~Material()
	{
		D3DRelease(Texture);
		D3DRelease(AdditionalTexture);
	}

	ID3D11ShaderResourceView* Texture;
	ID3D11ShaderResourceView* AdditionalTexture;
	ID3D11PixelShader* EffectShader;
	XMFLOAT4 TextureMove;
	XMFLOAT4 TextureOffset;
	std::string ShaderName;
	std::string Name;
	XMFLOAT2 Scale;
	XMFLOAT2 LSize;
	//NumOfFrames
	//FrameSize
	//FrameTime
	//Size
	XMSHORT4 Animate;
	float LFrameTime;
	UINT LFrameIndex;
	bool UseGlobalCoords;
	bool UseAlpha;

};

struct VPortStruct
{
	VPortStruct() { MaterialToRender = nullptr; RTView = nullptr; }
	D3D11_VIEWPORT VPort;
	D3DXMATRIX PMatrix;
	Material* MaterialToRender;
	ID3D11RenderTargetView* RTView;
	Vector2d WinPos;
	Vector2d WorldPos;
	Camera VPCamera;
};

struct DepthStencilState
{

	DepthStencilState() { PDepthStencilState = nullptr; }

	ID3D11DepthStencilState* PDepthStencilState;
	std::string Name;

};

struct BlendState
{

	BlendState() { this->PBlendState = nullptr; this->Name = nullptr; }

	ID3D11BlendState* PBlendState;
	char* Name;
};

struct WindowSizes
{

	WindowSizes() { }

	UINT ClientWWidth;
	UINT ClientWHeight;
	XMFLOAT2 WinPos;

	UINT LCOffSet;
	UINT RCOffSet;
	UINT TCOffSet;
	UINT BCOffSet;

};

#define DX_COM_DEVICE_AND_CONTEXT 1
#define DX_COM_SWAPCHAIN 2

// PAPA Class
class D3DAPP 
{
public:
	
	D3DAPP(bool Paused, bool Resizing, HWND hWnd);
	virtual ~D3DAPP();

public:
	///////////////////////////////////////////
	//**Puplic COM Objects
	///////////////////////////////////////////
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	IDXGISwapChain* SwapChain;

public:

	///////////////////////////////////////////////
	//**INIT WINAPI
	///////////////////////////////////////////////
	// Create application window
	HWND CreateD3DWindow(const HINSTANCE hInstance, LRESULT CALLBACK WINPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam),
		const int xPos, const int yPos, enum EDisplayModes mode, const LPSTR classname, const LPSTR winname, const UINT winType = WS_OVERLAPPEDWINDOW);
	
	void ShowD3DWindow(int cmd);
	void CloseD3DWindow();

	///////////////////////////////////////////////
	//**INIT DIRECT3D
	///////////////////////////////////////////////
	bool InitAdapters();
	bool CreateOutput(UINT mode = 0);
	bool CreateDevice(IDXGIAdapter* pAdapter);
	bool CreateSwapChain(INT numOfCounts = -1, bool isInWindow = true);
	bool CreateMainRenderTargetAndDepthStencilViews();
	bool CreateMainDepthStencilStates();
	void ResetMainCOM();
	void ResetAllAdapters();

	///////////////////////////////////////////////
	//**ADDITIONAL CREATIONS
	///////////////////////////////////////////////
	bool CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC& dsd, std::string& name);
	ID3D11RenderTargetView* CreateRenderTarget(ID3D11Texture2D* textureRenderTo);
	UINT CreateViewPort(const FLOAT topLeftX, const FLOAT topLeftY,
		const FLOAT width, const FLOAT height, const FLOAT maxDepth, const FLOAT minDepth, char* shader = nullptr);
	///////////////////////////////////////////////
	//**ADDITIONAL METHODS
	///////////////////////////////////////////////
	inline HWND GetWindow() { return HWnd; }
	UINT GetMaxMSQuality(enum DXGI_FORMAT, INT numOfCounts = -1);
	void SetRenderTarget(ID3D11RenderTargetView* renderTV);
	virtual void Resize(enum EDisplayModes mode);
	void UpdateWindowRect();
	void ClearScreen(XMFLOAT4& color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv);
	virtual void Draw();
	virtual void ReleaseDefault();
	virtual void SetStandartRenderSettings(D3D11_FILL_MODE fmode, D3D11_CULL_MODE cmode);
	inline void SetPaused(bool pause) { this->IsPaused = pause; }
	inline bool GetPaused() { return this->IsPaused; }
	bool SetDepthStencilStateByName(std::string& name);
	bool SetDepthStencilStateByIndex(UINT index);
	void DeleteAllDepthStencilStates();
	inline WindowSizes& GetWindowSizes() { return this->WinSizes; }
	virtual XMFLOAT2& GetScreenSizes();
	bool SetViewPort(SHORT indexOfVPort);
	D3D11_VIEWPORT& GetViewPort(const SHORT indexOfVPort);
	D3DXMATRIX& GetVPMatrix(const short indexOfVPort);
	Material* GetVPMaterial(const short indexOfVPort);
	ID3D11RenderTargetView* GetVPRenderTV(const short indexOfVPort);
	VPortStruct& GetVPStruct(const short indexOfVPort);
	inline std::string& GetCatalogName() { return this->Catalog; }
	Material* GetMaterial(std::string& materialName);
	bool GetIsInVPort(XMFLOAT2& pos, const short indexOfVPort);
	inline unsigned short GetNumOfVPorts() { return this->NumOfVPorts; }
	inline ID3D11RasterizerState* GetStandartRastState() { return this->StandartRastState; }
	inline D3DAPPTIMER* GetTimer() { return this->Timer; }
	inline UINT GetMSAA() { return this->MMsaa; }
	Vector2d& GetWindowModeSize(enum EDisplayModes mode);
	void DeleteAllVPorts();
	void CreateBasicBlendState();
	void CreateBlendState(D3D11_BLEND_DESC desc, char* name);
	void DeleteAllBlendStates();
	BlendState* GetBlendState(UINT index);
	BlendState* GetBlendState(char* name);
	bool SetBlendState(BlendState* pBlendState);
	bool SetBlendState(UINT index);
	bool SetBlendState(char* name);
	bool SetBlendState(ID3D11BlendState* bState);
	float GetSizeKoeff() { return this->SizeKoeff; }

	///////////////////////////////////////////////
	//**SIMPLE-CREATION METHODS
	///////////////////////////////////////////////
	bool SInit(int bufferCount, int sampleDestCount, bool windowed);
	bool SInitMaterials();
	ID3D11SamplerState* SCreateSampler(enum D3D11_TEXTURE_ADDRESS_MODE adress, enum D3D11_FILTER filter, UINT maxAnisotropy);
	ID3D11ShaderResourceView* CreateSShaderResourceView(ID3D11Texture2D* renderBufferTexture, DXGI_FORMAT format);
	ID3D11Texture2D* CreateSTexture2D(UINT width, UINT height, UINT bindFlags, DXGI_FORMAT format);
	ID3D11Buffer* CreateSVertexBuffer(bool dynamic, UINT size, UINT numOfElements);
	ID3D11Buffer* CreateSIndexBuffer(std::vector<UINT>& indexBuffer);
	ID3D11Buffer* CreateSConstantBuffer(UINT size);

private:

	void DeleteAllMaterials();
	ID3D11ShaderResourceView* LoadTexture(std::string& textureName, std::string& path);

	void SetBlendState(BlendState* bState, float bFactors[4]);

private:

	UINT Numenator;
	UINT Denomirator;

	std::vector <Material*> Materials;

protected:

	/////////////////////////////////////
	//**Adapters
	/////////////////////////////////////
	std::vector<IDXGIAdapter*> Adapters;
	IDXGIAdapter* CurrentAdapter;
	DXGI_ADAPTER_DESC AdapterDesc;
	std::vector<IDXGIOutput*> Outputs;
	IDXGIOutput* CurrentOutput;
	UINT FeatureLevel;

	/////////////////////////////////////
	//**Views
	/////////////////////////////////////
	ID3D11RenderTargetView* MainRenderTarget;
	ID3D11DepthStencilView* MainDepth;
	std::vector <DepthStencilState> DepthStencilStates;
	std::vector <BlendState> BlendStates;
	BlendState* CurrBlendState;

	unsigned short NumOfVPorts;

	/////////////////////////////////////
	//**Other Pointers
	/////////////////////////////////////
	D3DAPPTIMER* Timer;
	ID3D11RasterizerState* StandartRastState;

	HWND HWnd;
	UINT MMsaa;
	UINT NumOfCounts;

	bool IsPaused;
	bool IsResizing;

	//float WindowCoorX;
	//float WindowCoorY;

	WindowSizes WinSizes;
	XMFLOAT2 ScreenSizes;
	WindowSizes RenderSizes;

	std::string Catalog;

	bool LoopError;

	VPortStruct ViewPorts[8];

	float SizeKoeff;
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

	XMFLOAT3& GetCoordX(XMFLOAT3& objPos, XMFLOAT3 cameraPos);

	FLOAT GetMousePosXCenter(FLOAT shiftByX = 0);
	FLOAT GetMousePosYCenter(FLOAT shiftByY = 0);

	void GetMousePosCenterVPort(VPortStruct& viewPortStruct, Vector2d* oPtrMPos);

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
