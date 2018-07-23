#ifndef _DIRECTX3_H_
#define _DIRECTX3_H_

/**
 Linking libraries
 */
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class DirectX3
{
public:
	/**
	Initialize pointer to null
	If we do not initialize the pointer to null. If the object is
	not null it assumes it was valid created object and will attempt clean up.
	*/
	DirectX3(const DirectX3&);
	DirectX3();
	~DirectX3();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void ShutDown();

	/**
	 Called whenever we are going to draw a new scene at the beginning of each frame.
	 Initializes the buffers.
	 Param red - RGB red number
	 Param green - RGB green number
	 Param blue - RGB blue number
	 Param alpha - RGB alpha number
	 */
	void BeginScene(float, float, float, float);
	/**
	 * Tells swap chain to display drawings
	 */
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

private:
	bool mVsyncEnabled;
	int mVideoCardMemory;
	char mVideoCardDescription[128];
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11DepthStencilState* mDepthStencilState;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11RasterizerState* rRasterizerState;
	XMMATRIX mProjectionMatrix;
	XMMATRIX mWorldMatrix;
	XMMATRIX mOrthoMatrix;
};
#endif

