#include "D3DAPP.h"
#include "QuickTriggered.h"
#include "MathHelper.h"
#include "Timer.h"

#include "Timer.h" 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevhInstance, LPSTR cmdline, int cmd);
HRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND HWnd;
D3DAPPINPUT* Input = new D3DAPPINPUT();
bool Init(QuickTriggered** ppQuickTriggeredAppPtr, HINSTANCE hInstance, int cmd)
{
	QuickTriggered* TAA = new QuickTriggered(HWnd, Input);
	
	HWnd = TAA->CreateD3DWindow(hInstance, WinProc, 0, 0, DX_DISPLAY_MODE_1366_768,
		"HDWND", "QuickTriggered", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
	if (!TAA->SInit(1, 4, true))
		return false;
	TAA->ShowD3DWindow(cmd);
	MathHelp::InitRand();
	*ppQuickTriggeredAppPtr = TAA;

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevhInstance, LPSTR cmdline, int cmd)
{
	MSG msg = { 0 };
	QuickTriggered* TAApp = nullptr;
	if (!Init(&TAApp, hInstance, cmd))
		return msg.wParam;
	//TAApp->GetTimer()->SetTimeScale(0.5f);
	TAApp->GetTimer()->Reset();
	TAApp->InitApp();
	
	while (TRUE)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			TAApp->GetTimer()->Tick();
			std::stringstream Str;
			Str << TAApp->GetTimer()->GetFPS();
			SetWindowText(HWnd, Str.str().c_str());
			if (!TAApp->GetTimer()->GetIsStoped())
				TAApp->Update();
		}
	}
	TAApp->CloseD3DWindow();
	TAApp->ReleaseDefault();
	D3DDelete(TAApp);
	D3DDelete(Input);
	_CrtDumpMemoryLeaks();
	return msg.wParam;
}

HRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		Input->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		Input->OnMouseDown();
		return 0;
	}
	case WM_LBUTTONUP:
	{
		Input->OnMouseUp();
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		Input->OnMouseDown(false);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		Input->OnMouseUp(false);
		return 0;
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}