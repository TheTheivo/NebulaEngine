#pragma once

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void MouseMove(unsigned int);

	bool isKeyDown(unsigned int);

	bool ShutDown();

private:
	bool mKeys[256];
};

