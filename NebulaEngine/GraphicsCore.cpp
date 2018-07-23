#include "GraphicsClass.h"



GraphicsCore::GraphicsCore()
{
	mDirect3D = nullptr;
}

GraphicsCore::GraphicsCore(const GraphicsCore &)
{
}


GraphicsCore::~GraphicsCore()= default;

bool GraphicsCore::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	mDirect3D = new DirectX3;
	if (!mDirect3D)
	{
		return false;
	}

	result = mDirect3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}
	return true;
}

void GraphicsCore::ShutDown()
{
	if (mDirect3D)
	{
		mDirect3D->ShutDown();
		delete mDirect3D;
		mDirect3D = nullptr;
	}
}

bool GraphicsCore::Frame()
{
	bool result;

	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}

bool GraphicsCore::Render()
{
	mDirect3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	mDirect3D->EndScene();

	return true;
}
