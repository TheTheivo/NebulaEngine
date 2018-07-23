#pragma once
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "DirectX3.h"

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsCore
{
public:
	/**
	Initialize pointer to null
	If we do not initialize the pointer to null. If the object is
	not null it assumes it was valid created object and will attempt clean up.
	*/
	GraphicsCore(const GraphicsCore&);
	GraphicsCore();
	~GraphicsCore();

	bool Initialize(int, int, HWND);
	void ShutDown();
	bool Frame();

private:
	bool Render();
	DirectX3* mDirect3D;
};
#endif