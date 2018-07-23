#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/**
   Pre-Processing directives
   
   This define speeds up build process
 */
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "InputClass.h"
#include "GraphicsClass.h"

/**
  Core encapsulation of the whole system
 	
  This class take windows messages. It initialize and cleans up the whole application.
 */
class SystemCore

{
public:

	/**
	  Initialize pointer to null
	  If we do not initialize the pointer to null. If the object is 
	  not null it assumes it was valid created object and will attempt clean up.
	 */
	SystemCore(const SystemCore&);
	SystemCore();
	~SystemCore();


	bool Initialize();
	void Run();
	void ShutDown();

	/**
	  Handles messages passed from windows
	  
	  PARAM hwnd - Windows Handle class from win32 API
	  PARAM uint - key code of the input
	  PARAM wparam - unsigned int
	  PARAM lparam - unsigned long
	 */
	LRESULT CALLBACK MessageHandeler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutDownWindows();

	LPCTSTR mApplicationName;
	HINSTANCE mHInstance; /*Instance of this application to pass to CreateWindow*/
	HWND mHwnd;/*Windows Handle class from win32 API*/

	InputClass* mInput;/*Pointer to input instance*/
	GraphicsCore* mGraphics;/*Pointer to graphics instance*/
};

/**
 Handles messages passed from windows regarding window state

 PARAM hwnd - Windows Handle class from win32 API
 PARAM uint - key code of the input
 PARAM wparam - unsigned int
 PARAM lparam - unsigned long
*/
static LRESULT CALLBACK WindProc(HWND, UINT, WPARAM, LPARAM);
static SystemCore* ApplicationHandle = nullptr; /*Pointer to itself*/
#endif