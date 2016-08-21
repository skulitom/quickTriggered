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
	const int xPos, const int yPos, enum EDisplayModes mode, const LPSTR classname, const LPSTR winname, const UINT winType)
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

	Vector2d Sizes = this->GetWindowModeSize(mode);

	this->HWnd = CreateWindowEx(NULL, classname, winname, winType, xPos, yPos, Sizes.X, Sizes.Y, NULL, NULL, hInstance, NULL);
	
	this->UpdateWindowRect();

	return this->HWnd;
}

Vector2d& D3DAPP::GetWindowModeSize(enum EDisplayModes mode)
{

	Vector2d Sizes;

	switch (mode)
	{
		case DX_DISPLAY_MODE_1024_768:
		{
			Sizes = Vector2d(1024, 768);
			break;
		}
		case DX_DISPLAY_MODE_1152_864:
		{
			Sizes = Vector2d(1152, 864);
			break;
		}
		case DX_DISPLAY_MODE_1280_1024:
		{
			Sizes = Vector2d(1280, 1024);
			break;
		}
		case DX_DISPLAY_MODE_1280_600:
		{
			Sizes = Vector2d(1280, 600);
			break;
		}
		case DX_DISPLAY_MODE_1280_720:
		{
			Sizes = Vector2d(1280, 720);
			break;
		}
		case DX_DISPLAY_MODE_1280_768:
		{
			Sizes = Vector2d(1280, 768);
			break;
		}
		case DX_DISPLAY_MODE_1360_768:
		{
			Sizes = Vector2d(1360, 768);
			break;
		}
		case DX_DISPLAY_MODE_1440_900:
		{
			Sizes = Vector2d(1440, 900);
			break;
		}
		case DX_DISPLAY_MODE_1600_1024:
		{
			Sizes = Vector2d(1600, 1024);
			break;
		}
		case DX_DISPLAY_MODE_1600_1200:
		{
			Sizes = Vector2d(1600, 1200);
			break;
		}
		case DX_DISPLAY_MODE_1600_900:
		{
			Sizes = Vector2d(1600, 900);
			break;
		}
		case DX_DISPLAY_MODE_1680_1050:
		{
			Sizes = Vector2d(1680, 1050);
			break;
		}
		case DX_DISPLAY_MODE_1920_1080:
		{
			Sizes = Vector2d(1920, 1080);
			break;
		}
		case DX_DISPLAY_MODE_640_480:
		{
			Sizes = Vector2d(640, 480);
			break;
		}
		case DX_DISPLAY_MODE_800_600:
		{
			Sizes = Vector2d(800, 600);
			break;
		}
		default:
		case DX_DISPLAY_MODE_FULL_SCREEN:
		{
			XMFLOAT2 SSizes = this->GetScreenSizes();
			Sizes = Vector2d(SSizes.x, SSizes.y);
			break;
		}

	}

	return Sizes;

}

void D3DAPP::ShowD3DWindow(int cmd)
{
	ShowWindow(this->HWnd,cmd);
}

void D3DAPP::CloseD3DWindow()
{
	CloseWindow(this->HWnd);
}

bool D3DAPP::InitAdapters()
{
	
	/////////////////////////////////////////
	//**Delete Adapters
	//**Reset Pointers
	/////////////////////////////////////////
	this->ResetAllAdapters();

	HRESULT HR = S_OK;
	DXGI_ADAPTER_DESC AdapterDesc;

	IDXGIFactory* Factory = 0;

	////////////////////////////////////////
	//**Load Adapters
	////////////////////////////////////////

	HR = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)&Factory);
	if (FAILED(HR))
	{
		MessageBox(this->HWnd, "Create DXGIFactory failed!", "Create Factory error!", MB_ICONERROR);
		return false;
	}

	for (int i = 0; Factory->EnumAdapters(i, &this->CurrentAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{

		Adapters.push_back(this->CurrentAdapter);
		HR = this->CurrentAdapter->EnumOutputs(0, &this->CurrentOutput);
		if (SUCCEEDED(HR))
		{
			Outputs.push_back(this->CurrentOutput);
		}
		else
			Outputs.push_back(nullptr);
	}

	if (Adapters.size() == 0)
	{

		MessageBox(this->HWnd, "WTF?! No Video Adapers!", "Create Adapters Error", MB_ICONERROR);
		return false;

	}

	////////////////////////////////
	//**Get Best Adapter
	/////////////////////////////////////
	UINT MaxRevision = 0;
	for (int cnt = 0; cnt < Adapters.size(); cnt++)
	{

		Adapters.at(cnt)->GetDesc(&AdapterDesc);
		if (AdapterDesc.Revision >= MaxRevision)
		{

			this->CurrentAdapter = this->Adapters.at(cnt);
			this->CurrentOutput = this->Outputs.at(cnt);
			MaxRevision = AdapterDesc.Revision;

		}

	}

	return true;

}

bool D3DAPP::CreateOutput(UINT mode)
{

	for (int i = 0; i < this->Outputs.size(); i++)
	{

		if (this->Outputs.at(i))
		{

			this->CurrentOutput = this->Outputs.at(i);

			DXGI_MODE_DESC* MD = nullptr;
			UINT NumOfModes = 0;

			this->CurrentOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumOfModes, nullptr);

			MD = new DXGI_MODE_DESC[NumOfModes];

			this->CurrentOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumOfModes, MD);

			//for (int j = 0; j < NumOfModes; j++)
			//{

			//	if (this->WinSizes.ClientWWidth + this->WinSizes.LCOffSet+  == MD[j].Width)
			//		if (this->WinSizes.ClientWHeight == MD[j].Height)
			//		{

			//			this->Numenator = MD[j].RefreshRate.Numerator;
			//			this->Denomirator = MD[j].RefreshRate.Denominator;

			//		}

			//}

			if (MD)
				delete[] MD;

			return true;

		}

	}

	return false;

}

bool D3DAPP::CreateDevice(IDXGIAdapter* pAdapter)
{

	HRESULT HR = S_OK;

	///////////////////////////////////////////////
	//**Features
	///////////////////////////////////////////////
	D3D_FEATURE_LEVEL FeatureLevelStruct[] =
	{

		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0

	};

	UINT NumOfFeatuereLevels = ARRAYSIZE(FeatureLevelStruct);

	D3D_DRIVER_TYPE DriverTypeStruct[] =
	{

		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE

	};

	UINT NumOfDriverTypes = ARRAYSIZE(DriverTypeStruct);

	UINT DeviceFlags = 0;

	/////////////////////////////////////////////
	//**Create Device
	/////////////////////////////////////////////
	if (pAdapter)
	{

		for (int i = 0; i < NumOfFeatuereLevels; i++)
		{

			HR = D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, 0, DeviceFlags, nullptr, 0, D3D11_SDK_VERSION,
				&this->Device, &FeatureLevelStruct[i], &this->DeviceContext);

			if (SUCCEEDED(HR))
				break;

		}

		if (FAILED(HR))
		{
			MessageBox(this->HWnd, "Your Video Adapter and DirectX Version are not Compatible!", "Create Device Error", MB_ICONERROR);
			return false;
		}

	}
	else
	{
		for (int i = 0; i < NumOfFeatuereLevels; i++)
		{
			for (int j = 0; j < NumOfDriverTypes; j++)
			{
				HR = D3D11CreateDevice(this->CurrentAdapter, DriverTypeStruct[j], 0, DeviceFlags, nullptr, 0, D3D11_SDK_VERSION,
					&this->Device, &FeatureLevelStruct[i], &this->DeviceContext);

				if (SUCCEEDED(HR))
					break;
			}

			if (SUCCEEDED(HR))
				break;
		}

		if (FAILED(HR))
		{
			MessageBox(this->HWnd, "Your Video Adapters and DirectX Version are not Compatible!", "Create Device Error", MB_ICONERROR);
			return false;
		}

		IDXGIDevice* DXDevice = nullptr;
		this->Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXDevice);
		DXDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&this->CurrentAdapter);
		D3DRelease(DXDevice);

	}

	this->CurrentAdapter->GetDesc(&this->AdapterDesc);

	return true;

}

bool D3DAPP::CreateSwapChain(INT numOfCounts, bool isInWindow)
{

	HRESULT HR = S_OK;

	if (this->CurrentAdapter)
	{

		this->NumOfCounts = this->GetMaxMSQuality(DXGI_FORMAT_R8G8B8A8_UNORM, numOfCounts);

		IDXGIDevice* DXDevice = nullptr;
		IDXGIFactory* DXFactory = nullptr;
		this->CurrentAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&DXFactory);
		
		//////////////////////////////////////
		//**SwapChain DESC
		//////////////////////////////////////
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.Windowed = true;
		if (!isInWindow)
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
		if (this->MMsaa)
		{
			scd.SampleDesc.Count = this->NumOfCounts;
			scd.SampleDesc.Quality = this->MMsaa - 1;
		}
			
		else
		{
			scd.SampleDesc.Count = 1;
			scd.SampleDesc.Quality = 0;
		}
			
		scd.Flags = 0;

		//////////////////////////////////////
		//**Create SwapChain
		//////////////////////////////////////
		HR = DXFactory->CreateSwapChain(this->Device, &scd, &this->SwapChain);

		D3DRelease(DXDevice);
		D3DRelease(DXFactory);

		if (FAILED(HR))
		{

			MessageBox(this->HWnd, "Failed To Create SwapChain!", "Create SwapChain Error!", MB_ICONERROR);
			return false;

		}


	}

	return true;

}

bool D3DAPP::CreateMainRenderTargetAndDepthStencilViews()
{

	HRESULT HR = S_OK;

	/////////////////////////////////////////////
	//**Create Main Render Target View
	/////////////////////////////////////////////

	ID3D11Texture2D *TargetBuffer;
	D3D11_TEXTURE2D_DESC TD;
	HR = this->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&TargetBuffer));
	if (FAILED(HR))
	{

		MessageBox(this->HWnd, "Failed to create Render Target Buffer!", "Create Render Target Error!", MB_ICONERROR);
		D3DRelease(TargetBuffer);
		return false;

	}
	TargetBuffer->GetDesc(&TD);
	D3D11_RENDER_TARGET_VIEW_DESC RTVD;
	ZeroMemory(&RTVD, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RTVD.Format = TD.Format;
	RTVD.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	RTVD.Texture2DMS.UnusedField_NothingToDefine = 0;
	RTVD.Texture2D.MipSlice = 0;

	HR = Device->CreateRenderTargetView(TargetBuffer, nullptr, &MainRenderTarget);
	D3DRelease(TargetBuffer);
	if (FAILED(HR))
	{

		MessageBox(this->HWnd, "Failed to create Main Render Target!", "Create Render Target Error!", MB_ICONERROR);
		return false;

	}

	/////////////////////////////////////////////
	//**Create Main Depth View
	/////////////////////////////////////////////
	D3D11_TEXTURE2D_DESC DepthTextureDesc;
	//ZeroMemory(&DepthTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	this->NumOfCounts = this->GetMaxMSQuality(DXGI_FORMAT_D24_UNORM_S8_UINT, this->NumOfCounts);

	DepthTextureDesc.ArraySize = 1;
	DepthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthTextureDesc.CPUAccessFlags = NULL;
	DepthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthTextureDesc.Height = this->WinSizes.ClientWHeight;
	DepthTextureDesc.Width = this->WinSizes.ClientWWidth;
	DepthTextureDesc.MipLevels = 1;
	DepthTextureDesc.MiscFlags = NULL;

	if (this->MMsaa)
	{
		DepthTextureDesc.SampleDesc.Count = this->NumOfCounts;
		DepthTextureDesc.SampleDesc.Quality = this->MMsaa - 1;
	}
	
	else
	{
		DepthTextureDesc.SampleDesc.Count = 1;
		DepthTextureDesc.SampleDesc.Quality = 0;
	}
	DepthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	

	ID3D11Texture2D* DepthBuffer;

	Device->CreateTexture2D(&DepthTextureDesc, 0, &DepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DepthTextureDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2DMS.UnusedField_NothingToDefine = 0;
	descDSV.Texture2D.MipSlice = 0;

	HR = Device->CreateDepthStencilView(DepthBuffer, &descDSV, &MainDepth);
	D3DRelease(DepthBuffer);

	if (FAILED(HR))
	{

		MessageBox(this->HWnd, "Failed to create Depth Stancil View!", "create Depth Stancil View Error!", MB_ICONERROR);
		return false;

	}

	return true;

}

bool D3DAPP::CreateMainDepthStencilStates()
{

	bool Status = true;

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

	if (!this->CreateDepthStencilState(Dsd, std::string("DepthRenderState")))
		Status =  false;

	////////////////////////////////////////////////////
	//Create Depth stencil state (3d)
	////////////////////////////////////////////////////
	ZeroMemory(&Dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

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

	if(!this->CreateDepthStencilState(Dsd, std::string("2DRenderState")))
		Status =  false;

	this->CreateViewPort(0, 0, this->WinSizes.ClientWWidth, this->WinSizes.ClientWHeight, 1.f, 0.f);

	return Status;

}

ID3D11RenderTargetView* D3DAPP::CreateRenderTarget(ID3D11Texture2D* textureRenderTo)
{

	if (!textureRenderTo)
		return nullptr;

	ID3D11RenderTargetView* NewRTV;

	HRESULT HR = this->Device->CreateRenderTargetView(textureRenderTo, 0, &NewRTV);
	
	if (FAILED(HR))
		return nullptr;

	return NewRTV;

}

void D3DAPP::ResetMainCOM()
{

	this->DeviceContext->OMSetRenderTargets(0, 0, 0);

	this->DeleteAllDepthStencilStates();

	D3DRelease(this->MainRenderTarget);
	D3DRelease(this->MainDepth);
	this->DeviceContext->Flush();

	for (int i = 0; i < this->NumOfVPorts; i++)
	{

		D3DRelease(this->ViewPorts[i].RTView);
		D3DDelete(this->ViewPorts[i].MaterialToRender);

	}

	D3DRelease(this->Device);
	D3DRelease(this->DeviceContext);

	if (this->SwapChain)
		this->SwapChain->SetFullscreenState(false, NULL);
	D3DRelease(this->SwapChain);


}

void D3DAPP::ResetAllAdapters()
{

	for (int i = 0; i < this->Adapters.size(); i++)
	{

		D3DRelease(this->Adapters.at(i));
		D3DRelease(this->Outputs.at(i));

	}
	this->CurrentAdapter = nullptr;
	this->CurrentOutput = nullptr;

	this->Adapters.clear();
	this->Adapters.shrink_to_fit();

	this->Outputs.clear();
	this->Outputs.shrink_to_fit();

}

UINT D3DAPP::CreateViewPort(const FLOAT topLeftX, const FLOAT topLeftY, 
	const FLOAT width, const FLOAT height, const FLOAT maxDepth, const FLOAT minDepth, char* shaderName)
{

	if (this->NumOfVPorts >= 8)
		return 1;
		
	Vector2d Pos;
	Pos.X = (topLeftX + width * 0.5f);
	Pos.Y = (topLeftY + height * 0.5f);

	this->ViewPorts[this->NumOfVPorts].WinPos = Pos;

	Pos.X = Pos.X - this->WinSizes.ClientWWidth * 0.5f;
	Pos.Y = -Pos.Y + this->WinSizes.ClientWHeight * 0.5f;

	this->ViewPorts[this->NumOfVPorts].WorldPos = Pos;

	this->ViewPorts[this->NumOfVPorts].VPort.Height = height;
	this->ViewPorts[this->NumOfVPorts].VPort.Width = width;
	this->ViewPorts[this->NumOfVPorts].VPort.TopLeftX = 0;
	this->ViewPorts[this->NumOfVPorts].VPort.TopLeftY = 0;
	this->ViewPorts[this->NumOfVPorts].VPort.MaxDepth = maxDepth;
	this->ViewPorts[this->NumOfVPorts].VPort.MinDepth = minDepth;

	D3DXMatrixOrthoLH(&this->ViewPorts[this->NumOfVPorts].PMatrix, this->ViewPorts[this->NumOfVPorts].VPort.Width,
		this->ViewPorts[this->NumOfVPorts].VPort.Height, 0, 1);

	ID3D11Texture2D* Texture = this->CreateSTexture2D(width, height, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, DXGI_FORMAT_R32G32B32A32_FLOAT);

	this->ViewPorts[this->NumOfVPorts].MaterialToRender = new Material;

	this->ViewPorts[this->NumOfVPorts].MaterialToRender->Texture = this->CreateSShaderResourceView(Texture, DXGI_FORMAT_R32G32B32A32_FLOAT);

	if (shaderName)
	this->ViewPorts[this->NumOfVPorts].MaterialToRender->ShaderName = shaderName;

	this->ViewPorts[this->NumOfVPorts].RTView = this->CreateRenderTarget(Texture);

	this->NumOfVPorts++;

	return this->NumOfVPorts;

}

bool D3DAPP::SetViewPort(const SHORT indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return false;

	this->DeviceContext->RSSetViewports(1, &this->ViewPorts[indexOfVPort].VPort);

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

	this->DeviceContext->OMSetRenderTargets(1, &renderTV, this->MainDepth);

}

VPortStruct& D3DAPP::GetVPStruct(const short indexOfVPort)
{

	if (indexOfVPort < 0 || indexOfVPort > ARRAYSIZE(this->ViewPorts))
		return VPortStruct();

	return this->ViewPorts[indexOfVPort];

}

bool D3DAPP::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC & dsd, std::string & name)
{

	DepthStencilState DSS;

	HRESULT hr = this->Device->CreateDepthStencilState(&dsd, &DSS.PDepthStencilState);
	if (FAILED(hr))
	{

		MessageBox(this->HWnd, "Depth stencil state failed!", "Create DX error!", MB_ICONERROR);

		return false;

	}

	DSS.Name = name;

	this->DepthStencilStates.push_back(DSS);

	return true;

}

bool D3DAPP::SetDepthStencilStateByName(std::string & name)
{

	for (int i = 0; i < this->DepthStencilStates.size(); i++)
	{

		if (this->DepthStencilStates.at(i).Name == name)
		{

			this->DeviceContext->OMSetDepthStencilState(this->DepthStencilStates.at(i).PDepthStencilState, 1);
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

	this->NumOfCounts = this->GetMaxMSQuality(format, this->NumOfCounts);
	ID3D11Texture2D* RenderBufferTexture;
	D3D11_TEXTURE2D_DESC T2DD;
	ZeroMemory(&T2DD, sizeof(D3D11_TEXTURE2D_DESC));
	T2DD.ArraySize = 1;
	T2DD.BindFlags = bindFlags;
	T2DD.CPUAccessFlags = 0;
	T2DD.Format = format;
	T2DD.Height = height;
	T2DD.Width = width;
	T2DD.MipLevels = 1;
	T2DD.MiscFlags = 0;
	T2DD.SampleDesc.Count = this->NumOfCounts;
	T2DD.SampleDesc.Quality = this->MMsaa - 1;
	T2DD.Usage = D3D11_USAGE_DEFAULT;
	HRESULT hr = this->Device->CreateTexture2D(&T2DD, 0, &RenderBufferTexture);

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

	HRESULT hr = this->Device->CreateBuffer(&VBD, 0, &VBuffer);
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
	SRVD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	SRVD.Buffer.ElementOffset = 0;
	SRVD.Buffer.FirstElement = 0;
	SRVD.Buffer.NumElements = 1;
	SRVD.BufferEx.FirstElement = 0;
	SRVD.BufferEx.Flags = 0;
	SRVD.BufferEx.NumElements = 1;
	HRESULT hr = this->Device->CreateShaderResourceView(renderBufferTexture, &SRVD, &ResourceView);
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
	HRESULT hr = this->Device->CreateBuffer(&IBD, &SRD, &IBuffer);

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

	HRESULT hr = this->Device->CreateBuffer(&CBD, 0, &CBuffer);

	if (SUCCEEDED(hr))
		return CBuffer;

	return nullptr;

}

bool D3DAPP::SetDepthStencilStateByIndex(UINT index)
{

	if (index >= 0 && index < this->DepthStencilStates.size())
	{

		this->DeviceContext->OMSetDepthStencilState(this->DepthStencilStates.at(index).PDepthStencilState, 1);
		return true;

	}

	if (!this->LoopError)
	{
		MessageBox(this->HWnd, "Set depth stencil state failed!", "Render warning!", MB_ICONWARNING);
		this->LoopError = true;
		return false;
	}
}

void D3DAPP::DeleteAllDepthStencilStates()
{

	for (int i = 0; i < this->DepthStencilStates.size(); i++)
	{
		D3DRelease(this->DepthStencilStates.at(i).PDepthStencilState);
	}
	this->DepthStencilStates.clear();
	this->DepthStencilStates.shrink_to_fit();

}

void D3DAPP::CreateBasicBlendState()
{

	D3D11_BLEND_DESC BD = { 0 };
	BD.AlphaToCoverageEnable = false;
	BD.IndependentBlendEnable = false;
	BD.RenderTarget[0].BlendEnable = true;
	BD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	BD.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	BD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	BD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BD.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	D3DAPP::CreateBlendState(BD, "Basic");

	BD.AlphaToCoverageEnable = false;
	BD.IndependentBlendEnable = false;
	BD.RenderTarget[0].BlendEnable = true;
	BD.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	BD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BD.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	D3DAPP::CreateBlendState(BD, "Trans");

}

void D3DAPP::CreateBlendState(D3D11_BLEND_DESC desc, char* name)
{

	BlendState NBS;
	this->Device->CreateBlendState(&desc, &NBS.PBlendState);
	NBS.Name = name;
	this->BlendStates.push_back(NBS);

}

void D3DAPP::DeleteAllBlendStates()
{

	for (int i = 0; i < this->BlendStates.size(); i++)
	{
		D3DRelease(this->BlendStates.at(i).PBlendState);
		//D3DDelete(this->BlendStates.at(i).Name);
	}

}

BlendState* D3DAPP::GetBlendState(UINT index)
{

	if (index >= this->BlendStates.size())
		return nullptr;

	return &this->BlendStates.at(index);

}
BlendState* D3DAPP::GetBlendState(char* name)
{

	for (int i = 0; i < this->BlendStates.size(); i++)
	{

		if (!strcmp(name, this->BlendStates.at(i).Name))
			return &this->BlendStates.at(i);

	}

	return nullptr;

}

void D3DAPP::SetBlendState(BlendState* bState, float bFactors[4])
{

	if (bState != this->CurrBlendState)
	{
		this->CurrBlendState = bState;
		this->DeviceContext->OMSetBlendState(this->CurrBlendState->PBlendState, bFactors, 0xffffffff);
	}

}

bool D3DAPP::SetBlendState(BlendState* pBlendState)
{

	float BFactors[4] = { 0, 0, 0, 0 };

	D3DAPP::SetBlendState(pBlendState, BFactors);

	return true;
	
}

bool D3DAPP::SetBlendState(UINT index)
{
	float BFactors[4] = { 0, 0, 0, 0 };

	if (index >= this->BlendStates.size())
		return false;

	BlendState* BS = this->GetBlendState(index);

	D3DAPP::SetBlendState(BS, BFactors);

	return true;

}
bool D3DAPP::SetBlendState(char* name)
{

	float BFactors[4] = { 0, 0, 0, 0 };

	BlendState* BS = this->GetBlendState(name);

	if (!BS)
		return false;

	D3DAPP::SetBlendState(BS, BFactors);

	return true;

}

void D3DAPP::DeleteAllVPorts()
{

	for (int i = 0; i < this->NumOfVPorts; i++)
	{
		this->ViewPorts[i].MaterialToRender->EffectShader = nullptr;
		D3DRelease(this->ViewPorts[i].MaterialToRender->Texture);
		D3DRelease(this->ViewPorts[i].RTView);
		D3DDelete(this->ViewPorts[i].MaterialToRender);
	}

	this->NumOfVPorts = 0;

}

void D3DAPP::Resize(enum EDisplayModes mode)
{

	if (this->Device)
	{

		////////////////////////////////////////////////////
		//**Release
		////////////////////////////////////////////////////
		this->DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

		D3DRelease(this->MainDepth);
		D3DRelease(this->MainRenderTarget);
		
		this->DeleteAllVPorts();
		this->DeleteAllDepthStencilStates();

		////////////////////////////////////////////////////
		//**Resize
		////////////////////////////////////////////////////
		Vector2d Sizes = this->GetWindowModeSize(mode);
		
		MoveWindow(this->HWnd, 0, 0, Sizes.X, Sizes.Y, false);
		this->UpdateWindowRect();

		this->SwapChain->ResizeBuffers(1, this->WinSizes.ClientWWidth, this->WinSizes.ClientWHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		this->CreateMainRenderTargetAndDepthStencilViews();
		this->CreateMainDepthStencilStates();

	}

}

UINT D3DAPP::GetMaxMSQuality(enum DXGI_FORMAT format, INT numOfCounts)
{

	HRESULT HR = S_OK;

	while (numOfCounts > 0)
	{

		HR = Device->CheckMultisampleQualityLevels(format, numOfCounts, &this->MMsaa);

		if (SUCCEEDED(HR) && this->MMsaa > 0)
			break;

		numOfCounts = numOfCounts / 2;

	}

	if (FAILED(HR) || numOfCounts < 1)
	{
		this->MMsaa = 1;
	}

	return numOfCounts;

}

D3DAPP::~D3DAPP()
{

	/*this->SwapChain->SetFullscreenState(false, NULL);
	this->MainDepth->Release();
	this->Device->Release();
	this->DeviceContext->Release();
	this->MainRenderTarget->Release();
	this->SwapChain->Release();*/

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

	this->SizeKoeff = float(this->WinSizes.ClientWWidth) / (800 - this->WinSizes.LCOffSet - this->WinSizes.RCOffSet);

}

XMFLOAT2& D3DAPP::GetScreenSizes()
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
	DeviceContext->ClearRenderTargetView(rtv, (float*)&color);
	if (dsv)
		DeviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, NULL);
}

void D3DAPP::Draw()
{
	SwapChain->Present(0, 0);
}

void D3DAPP::ReleaseDefault()
{

	if (this->SwapChain)
	this->SwapChain->SetFullscreenState(false, NULL);
	
	this->DeleteAllMaterials();
	this->DeleteAllVPorts();
	this->ResetAllAdapters();
	this->DeleteAllBlendStates();

	D3DRelease(this->StandartRastState);
	this->ResetMainCOM();

	D3DDelete(this->Timer);

}

void D3DAPP::SetStandartRenderSettings(D3D11_FILL_MODE fmode, D3D11_CULL_MODE cmode)
{

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));

	rsDesc.FillMode = fmode;
	rsDesc.CullMode = cmode;
	rsDesc.FrontCounterClockwise = true;
	rsDesc.DepthClipEnable = true;
	rsDesc.AntialiasedLineEnable = false;
	rsDesc.MultisampleEnable = false;

	this->Device->CreateRasterizerState(&rsDesc, &this->StandartRastState);

}

bool D3DAPP::SInit(int bufferCount, int sampleDestCount, bool windowed)
{

	if (!this->InitAdapters())
		return false;

	if (!this->CreateOutput())
		return false;

	if (!this->CreateDevice(nullptr))
		return false;

	if (!this->CreateSwapChain(1))
		return false;

	if (!this->CreateMainRenderTargetAndDepthStencilViews())
		return false;

	if (!this->CreateMainDepthStencilStates())
		return false;

	this->CreateBasicBlendState();

	return true;

}

bool D3DAPP::SInitMaterials()
{

	FileManager* FManager = new FileManager();
	std::vector<std::string> MaterialFileList;

	////////////////////////////////////////////////
	//**Init Materials
	////////////////////////////////////////////////

	MaterialFileList = FileHelp::FindFiles(this->GetCatalogName() + "\\Resources\\Materials\\*.txt");

	for (size_t i = 0; i < MaterialFileList.size(); i++)
	{

		FManager->Open(this->GetCatalogName() + "\\Resources\\Materials\\" + MaterialFileList.at(i));

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

				NewMaterial->Texture = this->LoadTexture(Line, this->GetCatalogName() + "\\Resources\\Textures\\");

				if (NewMaterial->Texture)
				{
					D3D11_SHADER_RESOURCE_VIEW_DESC DS;
					NewMaterial->Texture->GetDesc(&DS);
				}

			}
			else if (!Line.compare("$ATexture:"))
			{

				Line = FManager->GetStringFromFile();

				NewMaterial->AdditionalTexture = this->LoadTexture(Line, this->GetCatalogName() + "\\Resources\\Textures\\");

			}
			else if (!Line.compare("$TextureScale:"))
			{
				NewMaterial->Scale.x = FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$ATextureScale:"))
			{
				NewMaterial->Scale.y = FManager->GetINTFromFile() / 100.f;
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
			else if (!Line.compare("$TextureOffSetRight:"))
			{
				NewMaterial->TextureOffset.x = -FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$TextureOffSetUp:"))
			{
				NewMaterial->TextureOffset.y = FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$ATextureOffSetRight:"))
			{
				NewMaterial->TextureOffset.z = -FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$ATextureOffSetUp:"))
			{
				NewMaterial->TextureOffset.w = FManager->GetINTFromFile() / 100.f;
			}
			else if (!Line.compare("$NumOfFrames:"))
			{
				NewMaterial->Animate.x = FManager->GetINTFromFile();
			}
			else if (!Line.compare("$FrameSize:"))
			{
				NewMaterial->Animate.y = FManager->GetINTFromFile();
			}
			else if (!Line.compare("$FrameTime:"))
			{
				NewMaterial->Animate.z = FManager->GetINTFromFile();
			}
			else if (!Line.compare("$Size:"))
			{
				NewMaterial->Animate.w = FManager->GetINTFromFile();
			}
		}

		if (!NewMaterial->Animate.x || !NewMaterial->Animate.y || !NewMaterial->Animate.w)
			NewMaterial->Animate = XMSHORT4((short)0, (short)0, (short)0, (short)0);

		if (NewMaterial->Name != "" && NewMaterial->Texture)
			this->Materials.push_back(NewMaterial);

		FManager->Close();

	}

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

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(this->Device, path.c_str(),
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

ID3D11SamplerState* D3DAPP::SCreateSampler(enum D3D11_TEXTURE_ADDRESS_MODE adress, enum D3D11_FILTER filter, UINT maxAnisotropy)
{

	ID3D11SamplerState* NewSampler;
	D3D11_SAMPLER_DESC SD;
	ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
	SD.AddressU = adress;
	SD.AddressV = adress;
	SD.AddressW = adress;
	SD.Filter = filter;
	SD.MaxAnisotropy = maxAnisotropy;
	HRESULT hr = this->Device->CreateSamplerState(&SD, &NewSampler);

	return NewSampler;

}

/////////////////////////////////////////////////////////////////////////////////////////////////
////INPUT
/////////////////////////////////////////////////////////////////////////////////////////////////

#define KB_STATUS_DEFAULT 0
#define KB_STATUS_PRESS 1

D3DAPPINPUT::D3DAPPINPUT()
{
	MousePos(0, 0);
	this->KStatus = KB_STATUS_DEFAULT;
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
	MouseX = CursorPosX;
	MouseY = CursorPosY;
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

	//this->MouseScroll = scrollUp;

}

FLOAT D3DAPPINPUT::GetMousePosXCenter(FLOAT shiftByX)
{

	return this->MouseX - (this->WinSizes.ClientWWidth) / 2.f - shiftByX;
}

FLOAT D3DAPPINPUT::GetMousePosYCenter(FLOAT shiftByY)
{

	return this->WinSizes.ClientWWidth / 2.f - shiftByY - this->MouseY;
	
}

void D3DAPPINPUT::GetMousePosCenterVPort(VPortStruct& viewPortStruct, Vector2d* oPtrMPos)
{

	if (oPtrMPos)
	{
		oPtrMPos->X = this->MouseX - viewPortStruct.WinPos.X;
		oPtrMPos->Y = -this->MouseY + viewPortStruct.WinPos.Y;
	}

}

bool D3DAPPINPUT::KBPress(int vKey)
{
	return (GetAsyncKeyState(vKey) & 0x8000);
}
bool D3DAPPINPUT::KBClicked(int vKey)
{

	if (this->KStatus == KB_STATUS_DEFAULT && this->KBPress(vKey))
	{
		this->KStatus = KB_STATUS_PRESS;
		return false;
	}
	if (this->KStatus == KB_STATUS_PRESS && !this->KBPress(vKey))
	{
		this->KStatus = KB_STATUS_DEFAULT;
		return true;
	}

	return false;

}
