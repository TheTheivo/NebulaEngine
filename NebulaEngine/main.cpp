#include "SystemCore.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdLine, int nShowCmd)
{
	SystemCore* System;
	bool result;

	System = new SystemCore;
	if (!System)
	{
		return 0;
	}

	result = System->Initialize();

	if (result)
	{
		System->Run();
	}

	System->ShutDown();
	delete System;
	System = nullptr;

	return 0;
}
