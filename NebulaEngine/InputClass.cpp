#include "InputClass.h"



InputClass::InputClass()
= default;

InputClass::InputClass(const InputClass&)
{
}
InputClass::~InputClass()
= default;

void InputClass::Initialize()
{
	int i;

	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		mKeys[i] = false;
	}
}

void InputClass::KeyDown(unsigned int)
{

}

void InputClass::KeyUp(unsigned int)
{

}

void InputClass::MouseMove(unsigned int)
{

}

bool InputClass::isKeyDown(unsigned int)
{
	return false;
}

bool InputClass::ShutDown()
{
	return true;
}
