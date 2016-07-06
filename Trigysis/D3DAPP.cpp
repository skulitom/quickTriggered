#include "D3DAPP.h"
#include <direct.h>

#include "Files.h"

#define GetCurrentDir _getcwd

D3DAPP::D3DAPP(bool Paused, bool Resizing, HWND hWnd)
{
	this->HWnd = hWnd;
	IsPaused = Paused;
	IsResizing = Resizing;

	char CatalogPath[FILENAME_MAX];
	
	int Size = FILENAME_MAX;

	GetCurrentDir(CatalogPath, sizeof(CatalogPath));

	this->Catalog = CatalogPath;

	this->Timer = new D3DAPPTIMER(1.f);

}

HWND D3DAPP::CreateD3DWindow(const HINSTANCE hInstance, LRESULT CALLBACK WINPROC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam),
	const int xPos, const int yPos, const int width, const int height, const LPSTR classname, const LPSTR winname, const UINT winType)
{

	WNDCLASSEX WC;

	ZeroMemory(&WC, sizeof(WNDCLASSEX));

	WC.cbSize = sizeof(WNDCLASSEX);
	WC.hbrBackground = HBRUSH(COLOR_WINDOW);
	WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC.hInstance = hInstance;
	WC.lpfnWndProc = WINPROC;
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpszClassName = classname;

	RegisterClassEx(&WC);

	this->HWnd = CreateWindowEx(NULL, classname, winname, winType, xPos, yPos, width, height, NULL, NULL, hInstance, NULL);
	
	this->UpdateWindowRect();

	return this->HWnd;
}

void D3DAPP::ShowD3DWindow(int cmd)
{
	ShowWindow(this->HWnd,cmd);
}

void D3DAPP::CloseD3DWindow()
{
	CloseWindow(this->HWnd);
}

void D3DAPP::SetPaused(bool pause)
{

	this->IsPaused = pause;

}

bool D3DAPP::GetPaused()
{

	return this->IsPaused;

}

WindowSizes& D3DAPP::GetWindowSizes()
{

	return this->WinSizes;

}

bool D3DAPP::DXCreateDeviceAndSwapChain(const int bufferCount, const int sampleDescCount, const bool isWindowed)
{

	HRESULT HR = S_OK;

	IDXGIFactory* dxgiFactory = 0;
	IDXGIAdapter* dxgiAdapter = 0;
	IDXGIOutput* dxgiOutput = 0;

	DXGI_MODE_DESC* DisplayModeDesc;
	DXGI_ADAPTER_DESC AdapterDesc;

	UINT NumModes = 0;

	HR = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)&dxgiFactory);
	if (FAILED(HR))
		return false;

	HR = dxgiFactory->EnumAdapters(0, &dxgiAdapter);
	if (FAILED(HR))
		return false;

	HR = dxgiAdapter->EnumOutputs(0, &dxgiOutput);
	if (FAILED(HR))
		return false;

	HR = dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &NumModes, nullptr);
	if (FAILED(HR))
		return false;

	DisplayModeDesc = new DXGI_MODE_DESC[NumModes];
	if (!DisplayModeDesc)
		return false;

	HR = dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &NumModes, DisplayModeDesc);
	if (FAILED(HR))
		return false;

	for (int i = 0; i < NumModes; i++)
	{

		if (DisplayModeDesc[i].Width == (UINT)this->ScreenSizes.x)
			if (DisplayModeDesc[i].Height == (UINT)this->ScreenSizes.y)
			{
				this->Numenator = DisplayModeDesc[i].RefreshRate.Numerator;
				this->Denomirator = DisplayModeDesc[i].RefreshRate.Denominator;
			}

	}

	HR = dxgiAdapter->GetDesc(&AdapterDesc);
	if (FAILED(HR))
		return false;

	this->VCardMem = (int)(AdapterDesc.DedicatedVideoMemory / 1024 / 1024);

	UINT StringL;
	int Error = wcstombs_s(&StringL, this->VCardDescription, 128, AdapterDesc.Description,
		128);
	if (Error != 0)
		return false;

	delete[] DisplayModeDesc;
	DisplayModeDesc = 0;

	D3DRelease(dxgiOutput);
	

	D3D_FEATURE_LEVEL FeatureLevelStruct[] =
	{

		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0

	};

	UINT NumOfFeatuereLevels = ARRAYSIZE(FeatureLevelStruct);
	
	D3D_DRIVER_TYPE DriverTypeStruct[] =
	{

		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE

	};

	UINT NumOfDriverTypes = ARRAYSIZE(DriverTypeStruct);

	UINT createDeviceFlags = 0;

	HRESULT hr = S_OK;
	D3D_DRIVER_TYPE DType;
	D3D_FEATURE_LEVEL FLevel;
	for (UINT i = 0; i < NumOfDriverTypes; i++)
	{

		DType = DriverTypeStruct[i];

		for (UINT j = 0; j < NumOfFeatuereLevels; j++)
		{

			FLevel = FeatureLevelStruct[j];

			hr = D3D11CreateDevice(0, DType, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &dxDevice, &FLevel, &dxDeviceCon);

			if (SUCCEEDED(hr))
				break;
		}
		if (SUCCEEDED(hr))
			break;

	}

	if (FAILED(hr))
	{
		MessageBox(this->HWnd, "Device failed!", "", MB_ICONERROR);
		this->ReleaseDefault();
		return false;
	}
	
	this->m4xMsaaQuality();

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.Windowed = isWindowed;
	if (!isWindowed)
	{

		this->WinSizes.ClientWWidth = this->GetScreenSizes().x;
		this->WinSizes.ClientWHeight = this->GetScreenSizes().y;

	}
	scd.BufferDesc.Height = this->WinSizes.ClientWHeight;
	scd.BufferDesc.Width = this->WinSizes.ClientWWidth;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = this->HWnd;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//scd.SampleDesc.Count = 2;
	//scd.SampleDesc.Quality = 0;
	if (this->MMsaa > 1)
		scd.SampleDesc.Count = 4;
	else
		scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = this->MMsaa - 1;
	scd.Flags = 0;

	IDXGIDevice* dxgiDevice = 0;
	dxDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);


	hr = dxgiFactory->CreateSwapChain(dxDevice, &scd, &dxSwapChain);

	if (FAILED(hr))
	{

		MessageBox(HWnd, "Swap chain failed!", "", MB_ICONERROR);
		this->ReleaseDefault();
		return false;

	}

	D3DRelease(dxgiFactory);
	D3DRelease(dxgiAdapter);
	D3DRelease(dxgiDevice);

	//this->UpdateWindowRect();

	return true;

}

bool D3DAPP::DXCreateTargetViewAndDepthView(const int sampleDescCount)
{
	ID3D11Texture2D *TargetBuffer;
	dxSwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D), 
		reinterpret_cast<void**>(&TargetBuffer));
	
	HRESULT hr = S_OK;

	hr = dxDevice->CreateRenderTargetView(TargetBuffer, 0, &dxRenderTargetView);

	if (FAILED(hr))
	{

		MessageBox(this->HWnd, "Render targer view failed!", "Create DX error!", MB_ICONERROR);

		return false;

	}

	D3D11_TEXTURE2D_DESC DepthTextureDesc;
	//ZeroMemory(&DepthTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	DepthTextureDesc.ArraySize = 1;
	DepthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthTextureDesc.CPUAccessFlags = NULL;
	DepthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthTextureDesc.Height = this->WinSizes.ClientWHeight;
	DepthTextureDesc.MipLevels = 1;
	DepthTextureDesc.MiscFlags = NULL;
	//DepthTextureDesc.SampleDesc.Count = 1;
	//DepthTextureDesc.SampleDesc.Quality = 1;
	if (this->MMsaa > 1)
		DepthTextureDesc.SampleDesc.Count = 4;
	else
		DepthTextureDesc.SampleDesc.Count = 1;
	DepthTextureDesc.SampleDesc.Quality = this->MMsaa - 1;
	DepthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthTextureDesc.Width = this->WinSizes.ClientWWidth;

	dxDevice->CreateTexture2D(&DepthTextureDesc, 0, &DepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DepthTextureDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	////////////////////////////////////////////////////
	//Create Depth stencil state (3d)
	////////////////////////////////////////////////////
	D3D11_DEPTH_STENCIL_DESC Dsd;

	Dsd.DepthEnable = TRUE;
	Dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Dsd.DepthFunc = D3D11_COMPARISON_LESS;
	Dsd.StencilEnable = TRUE;
	Dsd.StencilReadMask = 0xFF;
	Dsd.StencilWriteMask = 0xFF;

	Dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	Dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	Dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	Dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	Dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	Dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	Dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	Dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//Dsd.FrontFace.

	std::string Name = "DepthRenderState";
	this->DXCreateDepthStencilState(Dsd, Name);

	////////////////////////////////////////////////////
	//Create Depth stencil state (3d)
	////////////////////////////////////////////////////
	ZeroMemory(&Dsd,sizeof(D3D11_DEPTH_STENCIL_DESC));

	Dsd.DepthEnable = FALSE;
	Dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Dsd.DepthFunc = D3D11_COMPARISON_LESS;
	Dsd.StencilEnable = TRUE;
	Dsd.StencilReadMask = 0xFF;
	Dsd.StencilWriteMask = 0xFF;

	Dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	Dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	Dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	Dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	Dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	Dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	Dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	Dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//Dsd.FrontFace.

	Name.clear();
	Name = "2DRenderState";
	this->DXCreateDepthStencilState(Dsd, Name);

	dxDevice->CreateDepthStencilView(DepthBuffer, &descDSV, &dxDepthView);

	dxDeviceCon->OMSetRenderTargets(1, &dxRenderTargetView, dxDepthView);

	D3DRelease(TargetBuffer);

	this->CreateViewPort(0, 0, this->WinSizes.ClientWWidth, this->WinSizes.ClientWHeight, 1.f, 0.f);

	return true;

}

ID3D11RenderTargetView* D3DAPP::CreateRenderTarget(ID3D11Texture2D* textureRenderTo)
{

	if (!textureRenderTo)
		return nullptr;

	ID3D11RenderTargetView* NewRTV;

	HRESULT HR = this->dxDevice->CreateRenderTargetView(textureRenderTo, 0, &NewRTV);
	
	if (FAILED(HR))
		return nullptr;

	return NewRTV;

}

UINT D3DAPP::CreateViewPort(const FLOAT topLeftX, const FLOAT topLeftY, 
	const FLOAT width, const FLOAT height, const FLOAT maxDepth, const FLOAT minDepth, SHORT indexOfNewVPort)
{

	if (indexOfNewVPort < 0 || indexOfNewVPort > ARRAYSIZE(this->ViewPorts))
	{

		MessageBox(this->HWnd, "View Port array overflow!", "Create View Port error!", MB_ICONERROR);
		return false;

	}
		
	indexOfNewVPort = (indexOfNewVPort != 0) ? indexOfNewVPort : this->NumOfVPorts;

	Vector2d Pos;
	Pos.X = (topLeftX + width * 0.5f);
	Pos.Y = (topLeftY + height * 0.5f);

	this->ViewPorts[indexOfNewVPort].WinPos = Pos;

	Pos.X = Pos.X - this->WinSizes.ClientWWidth * 0.5f;
	Pos.Y = -Pos.Y + this->WinSizes.ClientWHeight * 0.5f;

	this->ViewPorts[indexOfNewVPort].WorldPos = Pos;

	this->ViewPorts[indexOfNewVPort].VPort.Height = height;
	this->ViewPorts[indexOfNewVPort].VPort.Width = width;
	this->ViewPorts[indexOfNewVPort].VPort.TopLeftX = 0;
	this->ViewPorts[indexOfNewVPort].VPort.TopLeftY = 0;
	this->ViewPorts[indexOfNewVPort].VPort.MaxDepth = maxDepth;
	this->ViewPorts[indexOfNewVPort].VPort.MinDepth = minDepth;

	D3DXMatrixOrthoLH(&this->ViewPorts[indexOfNewVPort].PMatrix, this->ViewPorts[indexOfNewVPort].VPort.Width,
		this->ViewPorts[indexOfNewVPort].VPort.Height, 0, 1);

	ID3D11Texture2D* Texture = this->CreateSTexture2D(width, height, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, DXGI_FORMAT_R32G32B32A32_FLOAT);

	this->ViewPorts[indexOfNewVPort].MaterialToRender = new Material;

	this->ViewPorts[indexOfNewVPort].MaterialToRender->Texture = this->CreateSShaderResourceView(Texture, DXGI_FORMAT_R32G32B32A32_FLOAT);
	
	this->ViewPorts[indexOfNewVPort].RTView = this->CreateRenderTarget(Texture);

	this->NumOfVPorts++;

	if (indexOfNewVPort != 0)
		return indexOfNewVPort;
	else
		return this->NumOfVPorts - 1;

}

bool D3DAPP::SetViewPort(const SHORT indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return false;

	this->dxDeviceCon->RSSetViewports(1, &this->ViewPorts[indexOfVPort].VPort);

	return true;

}

D3D11_VIEWPORT& D3DAPP::GetViewPort(const SHORT indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return this->ViewPorts[0].VPort;

	return this->ViewPorts[indexOfVPort].VPort;

}

D3DXMATRIX& D3DAPP::GetVPMatrix(const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return *D3DXMatrixIdentity(nullptr);

	return this->ViewPorts[indexOfVPort].PMatrix;

}

Material* D3DAPP::GetVPMaterial(const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return nullptr;

	return this->ViewPorts[indexOfVPort].MaterialToRender;

}

ID3D11RenderTargetView* D3DAPP::GetVPRenderTV(const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return nullptr;

	return this->ViewPorts[indexOfVPort].RTView;

}

void D3DAPP::SetRenderTarget(ID3D11RenderTargetView* renderTV)
{

	if (!renderTV)
		return;

	this->dxDeviceCon->OMSetRenderTargets(1, &renderTV, this->dxDepthView);

}

VPortStruct& D3DAPP::GetVPStruct(const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return VPortStruct();

	return this->ViewPorts[indexOfVPort];

}

bool D3DAPP::DXCreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC & dsd, std::string & name)
{

	DepthStencilState DSS;

	HRESULT hr = this->dxDevice->CreateDepthStencilState(&dsd, &DSS.PDepthStencilState);
	if (FAILED(hr))
	{

		MessageBox(this->HWnd, "Depth stencil state failed!", "Create DX error!", MB_ICONERROR);

		return false;

	}

	DSS.Name = name;

	this->dxDepthState.push_back(DSS);

	return true;

}

bool D3DAPP::SetDepthStencilStateByName(std::string & name)
{

	for (int i = 0; i < this->dxDepthState.size(); i++)
	{

		if (this->dxDepthState.at(i).Name == name)
		{

			this->dxDeviceCon->OMSetDepthStencilState(this->dxDepthState.at(i).PDepthStencilState, 1);
			return true;

		}

	}

	if (!this->LoopError)
	{
		MessageBox(this->HWnd, "Set depth stencil state failed!", "Render warning!", MB_ICONWARNING);
		this->LoopError = true;
		return false;
	}

}

ID3D11Texture2D* D3DAPP::CreateSTexture2D(UINT width, UINT height, UINT bindFlags, DXGI_FORMAT format)
{

	ID3D11Texture2D* RenderBufferTexture;
	D3D11_TEXTURE2D_DESC T2DD;
	ZeroMemory(&T2DD, sizeof(D3D11_TEXTURE2D_DESC));
	T2DD.ArraySize = 1;
	T2DD.BindFlags = bindFlags;
	T2DD.CPUAccessFlags = 0;
	T2DD.Format = format;
	//T2DD.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	T2DD.Height = height;
	T2DD.Width = width;
	T2DD.MipLevels = 1;
	T2DD.MiscFlags = 0;
	T2DD.SampleDesc.Count = 1;
	T2DD.SampleDesc.Quality = 0;
	T2DD.Usage = D3D11_USAGE_DEFAULT;
	HRESULT hr = this->dxDevice->CreateTexture2D(&T2DD, 0, &RenderBufferTexture);

	if (SUCCEEDED(hr))
		return RenderBufferTexture;

	return nullptr;

}

ID3D11Buffer* D3DAPP::CreateSVertexBuffer(bool dynamic, UINT size, UINT numOfElements)
{

	ID3D11Buffer* VBuffer;

	D3D11_BUFFER_DESC VBD;
	ZeroMemory(&VBD, sizeof(D3D11_BUFFER_DESC));
	VBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBD.ByteWidth = size * numOfElements;
	VBD.StructureByteStride = 0;
	VBD.MiscFlags = 0;

	if (dynamic)
	{
		VBD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		VBD.Usage = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		VBD.CPUAccessFlags = 0;
		VBD.Usage = D3D11_USAGE_IMMUTABLE;
	}

	//D3D11_SUBRESOURCE_DATA VSRD;
	//ZeroMemory(&VSRD, sizeof(D3D11_SUBRESOURCE_DATA));
	//VSRD.pSysMem = &this->Vertices[0];

	HRESULT hr = this->dxDevice->CreateBuffer(&VBD, 0, &VBuffer);
	if (SUCCEEDED(hr))
		return VBuffer;

	return nullptr;

}

ID3D11ShaderResourceView* D3DAPP::CreateSShaderResourceView(ID3D11Texture2D* renderBufferTexture, DXGI_FORMAT format)
{

	if (!renderBufferTexture)
		return nullptr;

	ID3D11ShaderResourceView* ResourceView;

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVD;
	ZeroMemory(&SRVD, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	SRVD.Format = format;
	SRVD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVD.Buffer.ElementOffset = 0;
	SRVD.Buffer.FirstElement = 0;
	SRVD.Buffer.NumElements = 1;
	SRVD.BufferEx.FirstElement = 0;
	SRVD.BufferEx.Flags = 0;
	SRVD.BufferEx.NumElements = 1;
	SRVD.Texture2D.MipLevels = 1;
	SRVD.Texture2D.MostDetailedMip = 0;
	HRESULT hr = this->dxDevice->CreateShaderResourceView(renderBufferTexture, &SRVD, &ResourceView);
	if (SUCCEEDED(hr))
		return ResourceView;

	return nullptr;

}

ID3D11Buffer* D3DAPP::CreateSIndexBuffer(std::vector<UINT>& indexBuffer)
{

	ID3D11Buffer* IBuffer;
	D3D11_BUFFER_DESC IBD;
	IBD.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBD.ByteWidth = sizeof(UINT) * indexBuffer.size();
	IBD.CPUAccessFlags = 0;
	IBD.MiscFlags = 0;
	IBD.StructureByteStride = 0;
	IBD.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA SRD;
	SRD.pSysMem = &indexBuffer.at(0);
	HRESULT hr = this->dxDevice->CreateBuffer(&IBD, &SRD, &IBuffer);

	if (SUCCEEDED(hr))
		return IBuffer;

	return nullptr;

}

ID3D11Buffer* D3DAPP::CreateSConstantBuffer(UINT size)
{

	ID3D11Buffer* CBuffer;
	D3D11_BUFFER_DESC CBD;
	CBD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBD.ByteWidth = size;
	CBD.CPUAccessFlags = 0;
	CBD.MiscFlags = 0;
	CBD.StructureByteStride = 0;
	CBD.Usage = D3D11_USAGE_DEFAULT;

	HRESULT hr = this->dxDevice->CreateBuffer(&CBD, 0, &CBuffer);

	if (SUCCEEDED(hr))
		return CBuffer;

	return nullptr;

}

bool D3DAPP::SetDepthStencilStateByIndex(UINT index)
{

	if (index >= 0 && index < this->dxDepthState.size())
	{

		this->dxDeviceCon->OMSetDepthStencilState(this->dxDepthState.at(index).PDepthStencilState, 1);
		return true;

	}

	if (!this->LoopError)
	{
		MessageBox(this->HWnd, "Set depth stencil state failed!", "Render warning!", MB_ICONWARNING);
		this->LoopError = true;
		return false;
	}
}

void D3DAPP::OnResize()
{

	if (this->dxRenderTargetView != NULL)
	{

		this->dxDeviceCon->OMSetRenderTargets(0, 0, 0);

		this->dxRenderTargetView->Release();
		D3DRelease(this->dxDepthView);
		this->dxDeviceCon->Flush();

		this->UpdateWindowRect();

		this->dxSwapChain->ResizeBuffers(1, this->WinSizes.ClientWWidth, this->WinSizes.ClientWHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		this->DXCreateTargetViewAndDepthView(4);

		//this->DXCreateViewPort(this->WinSizes.mWindowHeight, this->WinSizes.mWindowWidth, 1.0f, 0.0f, 0, 0);
	}
}

void D3DAPP::m4xMsaaQuality()
{

	if (this->MMsaa == NULL)
	{
		HRESULT hr = dxDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R32G32B32A32_UINT, 4, &this->MMsaa);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Quality faild!", "ERROR", MB_ICONERROR);
			this->MMsaa = 1;
		}
	}
}

D3DAPP::~D3DAPP()
{

	/*this->dxSwapChain->SetFullscreenState(false, NULL);
	this->dxDepthView->Release();
	this->dxDevice->Release();
	this->dxDeviceCon->Release();
	this->dxRenderTargetView->Release();
	this->dxSwapChain->Release();*/

}

void D3DAPP::UpdateWindowRect()
{
	RECT wRc;
	GetWindowRect(this->HWnd, &wRc);
	RECT cRc;
	GetClientRect(this->HWnd, &cRc);
	
	this->WinSizes.WinPos = XMFLOAT2(wRc.left, wRc.top);
	this->WinSizes.ClientWWidth = cRc.right - cRc.left;
	this->WinSizes.ClientWHeight = cRc.bottom - cRc.top;
	this->WinSizes.LCOffSet = cRc.left - wRc.left;
	this->WinSizes.RCOffSet = wRc.right - cRc.right;
	this->WinSizes.TCOffSet = cRc.top - wRc.top;
	this->WinSizes.BCOffSet = wRc.bottom - cRc.bottom;

}

XMFLOAT2 & D3DAPP::GetScreenSizes()
{
	
	RECT sRc;

	const HWND hDesctop = GetDesktopWindow();
	GetWindowRect(hDesctop, &sRc);
	this->ScreenSizes.y = sRc.bottom - sRc.top;
	this->ScreenSizes.x = sRc.right - sRc.left;

	return this->ScreenSizes;

}

void D3DAPP::ClearScreen(XMFLOAT4& color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	dxDeviceCon->ClearRenderTargetView(rtv, (float*)&color);
	if (dsv)
		dxDeviceCon->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, NULL);
}

void D3DAPP::Draw()
{
	dxSwapChain->Present(0, 0);
}

void D3DAPP::ReleaseDefault()
{

	if (this->dxSwapChain)
	this->dxSwapChain->SetFullscreenState(false, NULL);
	
	this->DeleteAllMaterials();

	for (int i = 0; i < this->NumOfVPorts; i++)
	{

		D3DRelease(this->ViewPorts[i].RTView);
		D3DDelete(this->ViewPorts[i].MaterialToRender);

	}

	D3DRelease(this->dxDepthView);
	D3DRelease(this->dxDevice);
	D3DRelease(this->dxDeviceCon);
	D3DRelease(this->dxRenderTargetView);
	D3DRelease(this->dxSwapChain);
	D3DRelease(this->dxDepthView);
	D3DRelease(this->DepthBuffer);
	D3DRelease(this->StandartRastState);

	D3DDelete(this->Timer);

}

HWND D3DAPP::GetWindow()
{
	return HWnd;
}

float D3DAPP::GetWindowPosX()
{
	return this->WindowCoorX;
}

float D3DAPP::GetWindowPosY()
{
	return this->WindowCoorY;
}

std::string& D3DAPP::GetCatalogName()
{
	return this->Catalog;
}

void D3DAPP::SetStandartRenderSettings(D3D11_FILL_MODE fmode, D3D11_CULL_MODE cmode)
{

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));

	rsDesc.FillMode = fmode;
	rsDesc.CullMode = cmode;
	rsDesc.FrontCounterClockwise = true;
	rsDesc.DepthClipEnable = true;
	rsDesc.AntialiasedLineEnable = true;
	rsDesc.MultisampleEnable = true;

	this->dxDevice->CreateRasterizerState(&rsDesc, &this->StandartRastState);

}

bool D3DAPP::SInit(int bufferCount, int sampleDestCount, bool windowed)
{

	if (!this->DXCreateDeviceAndSwapChain(1, 4, true))
	{

		MessageBox(this->GetWindow(), "Create device failed!", "Device error!", MB_ICONERROR);

		return false;

	}

	if (!this->DXCreateTargetViewAndDepthView(4))
	{

		MessageBox(this->GetWindow(), "Create target view failed!", "Target view error!", MB_ICONERROR);

		return false;

	}

	//this->DXCreateViewPort(this->GetWindowHeight(), this->GetWindowWidth(), 1.0f, 0.f, 0.f, 0.f);

	//this->SetRenderSettings(D3D11_FILL_SOLID, D3D11_CULL_NONE, this->mRastStateSolidBack);

	return true;

}

bool D3DAPP::SInitMaterials()
{

	FileManager* FManager = new FileManager();
	std::vector<std::string> TextureFileList;
	std::vector<std::string> MaterialFileList;

	///////////////////////////////////////////////
	//**Load Textures
	///////////////////////////////////////////////

	std::vector<TextureStruct*> Textures;

	TextureFileList = FileHelp::FindFiles(this->GetCatalogName() + "\\Textures\\*.dds");

	//for (int i = 0; i < TextureFileList.size(); i++)
	//{

		//Textures.push_back(this->LoadTexture(TextureFileList.at(i), this->GetCatalogName() + "\\Textures\\"));

	//}


	//for (int i = 0; i < FileList.size(); i++)
	//{
	//
	//	Textures.push_back(this->LoadTexture(FileList.at(i), this->GetCatalogName() + "\\Textures\\"));
	//
	//}
	//
	//FileList.clear();
	//FileList.shrink_to_fit();

	////////////////////////////////////////////////
	//**Init Materials
	////////////////////////////////////////////////

	MaterialFileList = FileHelp::FindFiles(this->GetCatalogName() + "\\Textures\\*.txt");

	for (size_t i = 0; i < MaterialFileList.size(); i++)
	{

		FManager->Open(this->GetCatalogName() + "\\Textures\\" + MaterialFileList.at(i));

		Material* NewMaterial = new Material();

		std::string Line;

		while (!FManager->GetFILE().eof())
		{

			Line = FManager->GetStringFromFile();

			if (!Line.compare("$Name:"))
			{

				NewMaterial->Name = FManager->GetStringFromFile();

			}
			else if (!Line.compare("$Texture:"))
			{

				Line = FManager->GetStringFromFile();

				NewMaterial->Texture = this->LoadTexture(Line, this->GetCatalogName() + "\\Textures\\");

				//for (int j = 0; j < TextureFileList.size(); j++)
				//{
				//	if (Textures.at(j)->TextureName == Line) // <-
				//	{
				//		NewMaterial.Texture = Textures.at(j)->Texture;
				//		if (NewMaterial.Name == "")
				//			NewMaterial.Name = Textures.at(j)->TextureName;
				//		break;
				//	}
				//}

			}
			else if (!Line.compare("$ATexture:"))
			{

				Line = FManager->GetStringFromFile();

				NewMaterial->AdditionalTexture = this->LoadTexture(Line, this->GetCatalogName() + "\\Textures\\");

				//for (int j = 0; j < Textures.size(); j++)
				//{
				//	if (this->TextureNames.at(i) == Line)
				//	{
				//		NewMaterial.AdditionalTexture = Textures.at(i)->Texture;
				//		break;
				//	}
				//}

			}
			else if (!Line.compare("$Alpha"))
			{
				NewMaterial->UseAlpha = true;
			}
			else if (!Line.compare("$Shader:"))
			{
				NewMaterial->ShaderName = FManager->GetStringFromFile();
			}
			else if (!Line.compare("$GlobalTexCoords"))
			{
				NewMaterial->UseGlobalCoords = true;
			}
			else if (!Line.compare("$TextureMoveUp:"))
			{
				NewMaterial->TextureMove.y = FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$TextureMoveRight:"))
			{
				NewMaterial->TextureMove.x = -FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$ATextureMoveUp:"))
			{
				NewMaterial->TextureMove.w = FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$ATextureMoveRight:"))
			{
				NewMaterial->TextureMove.z = -FManager->GetINTFromFile() / 100.f;
			}
		}

		this->Materials.push_back(NewMaterial);
		FManager->Close();

	}

	//Textures.clear();

	//MateFileList.clear();

	FManager->Close();
	D3DDelete(FManager);

	return true;

}

void D3DAPP::DeleteAllMaterials()
{

	for (int i = 0; i < this->Materials.size(); i++)
	{
		D3DDelete(this->Materials.at(i));
	}

}

Material* D3DAPP::GetMaterial(std::string& materialName)
{

	for (size_t i = 0; i < this->Materials.size(); i++)
	{

		if (this->Materials.at(i)->Name == materialName)
		{

			return this->Materials.at(i);

		}

	}

	return nullptr;

}

ID3D11ShaderResourceView* D3DAPP::LoadTexture(std::string& textureName, std::string& path)
{

	//TextureStruct* TStruct = new TextureStruct;

	ID3D11ShaderResourceView* SRV;

	path = path + textureName;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(this->dxDevice, path.c_str(),
		NULL, NULL, &SRV, NULL);

	if (FAILED(hr))
	{

		return nullptr;

	}
	//TStruct->Texture = SRV;
	//TStruct->TextureName = textureName;
	//this->TextureViews.push_back(SRV);
	//this->TextureNames.push_back(textureName);

	return SRV;

}

bool D3DAPP::GetIsInVPort(XMFLOAT2& pos, const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return false;

	if (pos.x < this->ViewPorts[indexOfVPort].VPort.TopLeftX || pos.y < this->ViewPorts[indexOfVPort].VPort.TopLeftY)
		return false;
	if (pos.x > this->ViewPorts[indexOfVPort].VPort.Width + this->ViewPorts[indexOfVPort].VPort.TopLeftX
		|| pos.y > this->ViewPorts[indexOfVPort].VPort.TopLeftY + this->ViewPorts[indexOfVPort].VPort.Height)
		return false;

	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////////////
////INPUT
/////////////////////////////////////////////////////////////////////////////////////////////////

D3DAPPINPUT::D3DAPPINPUT()
{
	MousePos(0, 0);
	this->Status = 0;
}

D3DAPPINPUT::~D3DAPPINPUT()
{

}

void D3DAPPINPUT::SetWinSizes(WindowSizes& winSizes)
{

	this->WinSizes = winSizes;

}

void D3DAPPINPUT::MousePos(float CursorPosX,float CursorPosY)
{
	mMouseX = CursorPosX;
	mMouseY = CursorPosY;
}

void D3DAPPINPUT::OnMouseDown(bool left)
{
	if (left)
		this->Status = this->Status | DX_MOUSE_DOWN_LEFT;
	else
		this->Status = this->Status | DX_MOUSE_DOWN_RIGHT;
}

void D3DAPPINPUT::OnMouseUp(bool left)
{
	if (left)
		this->Status = this->Status & (~DX_MOUSE_DOWN_LEFT);
	else
		this->Status = this->Status & (~DX_MOUSE_DOWN_RIGHT);
}

void D3DAPPINPUT::OnMouseMove(float CursorPosX, float CursorPosY)
{
	MousePos(CursorPosX, CursorPosY);
}

void D3DAPPINPUT::OnMouseScroll(FLOAT scrollUp)
{

	this->MouseScroll = scrollUp;

}

float D3DAPPINPUT::GetMouseX()
{
	return mMouseX;
}

float D3DAPPINPUT::GetMouseY()
{
	return mMouseY;
}

FLOAT D3DAPPINPUT::GetMapMousePosX(XMFLOAT4X4 mProject, XMFLOAT3 cameraPos)
{
	this->mMapMouseX = (2.f*this->mMouseX / this->WinSizes.ClientWWidth - 1.f) / mProject(0, 0);
	return  this->mMapMouseX;

}

FLOAT D3DAPPINPUT::GetMapMousePosY(XMFLOAT3 cameraPos)
{

	return this->mMapMouseY = this->WinSizes.ClientWHeight - this->mMouseX;

}

XMFLOAT3& D3DAPPINPUT::GetCoordX(XMFLOAT3& objPos, XMFLOAT3 cameraPos)
{

	XMFLOAT3 Start = { cameraPos.x, cameraPos.y, cameraPos.z };
	XMFLOAT3 End = { this->mMapMouseX, 0, objPos.z };

	XMVECTOR V = XMLoadFloat3(&Start) - XMLoadFloat3(&End);

	V = XMVector3Normalize(V);

	XMStoreFloat3(&End, V);

	objPos.x = End.x;

	 return objPos;
}

FLOAT D3DAPPINPUT::GetMousePosXCenter(FLOAT shiftByX)
{

	return this->mMouseX - (this->WinSizes.ClientWWidth) / 2.f - shiftByX;
}

FLOAT D3DAPPINPUT::GetMousePosYCenter(FLOAT shiftByY)
{

	return this->WinSizes.ClientWWidth / 2.f - shiftByY - this->mMouseY;
	
}

FLOAT D3DAPPINPUT::GetMouseScroll()
{

	FLOAT Scroll = this->MouseScroll;
	this->MouseScroll = 0;

	return Scroll;

}

Vector2d& D3DAPPINPUT::GetMousePosCenterVPort(VPortStruct& viewPortStruct)
{

	return Vector2d(this->mMouseX - viewPortStruct.WinPos.X, this->mMouseY - viewPortStruct.WinPos.Y);

}

unsigned short D3DAPPINPUT::GetStatus()
{

	return this->Status;

}