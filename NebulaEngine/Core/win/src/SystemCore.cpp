#include "SystemCore.h"



SystemCore::SystemCore()
{
	mInput = nullptr;
	mGraphics = nullptr;
}

SystemCore::SystemCore(const SystemCore& another)
{
}

SystemCore::~SystemCore()= default;

bool SystemCore::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;
	
	//Initialize the windows api
	InitializeWindows(screenWidth, screenHeight);

	mInput = new InputClass();

	if (!mInput)
	{
		return false;
	}

	mInput->Initialize();

	mGraphics = new GraphicsCore();

	if (!mGraphics)
	{
		return false;
	}

	result = mGraphics->Initialize(screenWidth, screenHeight, mHwnd);

	if (!result)
	{
		return false;
	}

	return true;
}

void SystemCore::ShutDown()
{
	if (mGraphics)
	{
		mGraphics->ShutDown();
		delete mGraphics;
		mGraphics = nullptr;
	}
	if (mInput)
	{
		mInput->ShutDown();
		delete mInput;
		mInput = nullptr;
	}

	ShutDownWindows();
}

void SystemCore::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;

	while (!done)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}

	}
}

LRESULT CALLBACK SystemCore::MessageHandeler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
	{
		mInput->KeyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP:
	{
		mInput->KeyUp((unsigned int)wparam);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		mInput->MouseMove((unsigned int)wparam);
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

bool SystemCore::Frame()
{
	bool result;

	if (mInput->isKeyDown(VK_ESCAPE))
	{
		return false;
	}

	result = mGraphics->Frame();
	if (!result)
	{
		return false;
	}
	return true;
}

void SystemCore::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;/*Structure to create window*/
	DEVMODE dmScreenSettings;/*Structure containing data about init and environment of monitor*/
	int posX, posY;
	
	ApplicationHandle = this;

	mHInstance = GetModuleHandle(nullptr);
	mApplicationName = "Nebula Project";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mHInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = mApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	//Gets resolution of the system monitor
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//TODO: Re implement this to take info from config file
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
		mHwnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, nullptr, nullptr, mHInstance, nullptr);
	}
	else
	{
		screenHeight = screenHeight;
		screenWidth = screenWidth;
		posX = posY = 0;
		mHwnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName, WS_OVERLAPPEDWINDOW, posX, posY, screenWidth, screenHeight, nullptr, nullptr, mHInstance, nullptr);
		
	}
	
	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	SetFocus(mHwnd);

	ShowCursor(true);
}

void SystemCore::ShutDownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}
	DestroyWindow(mHwnd);
	mHwnd = nullptr;

	UnregisterClass((LPCSTR)mApplicationName, mHInstance);

	mHInstance = nullptr;
	ApplicationHandle = nullptr;
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT umessege, WPARAM wparam, LPARAM lparam)
{
	switch (umessege)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return ApplicationHandle->MessageHandeler(hwnd, umessege, wparam, lparam);
		}
	}
}