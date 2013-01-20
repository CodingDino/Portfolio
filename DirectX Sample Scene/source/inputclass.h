// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// InputClass
//		Gets and processes input to be made available for game class to use in 
//		game logic.
#pragma once


// |----------------------------------------------------------------------------|
// |						Pre-Processing Directives							|
// |----------------------------------------------------------------------------|
#define DIRECTINPUT_VERSION 0x0800


// |----------------------------------------------------------------------------|
// |								 Linking									|
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <dinput.h>


// |----------------------------------------------------------------------------|
// |						   Class: InputClass								|
// |----------------------------------------------------------------------------|
class InputClass
{
public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
	
	// Initializes mouse and keyboard settings
	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
	
	// Performs shutdown, deallocation, and cleanup for input objects
	void Shutdown();
	
	// Gets input and processes it
	bool Frame();

	// Key press checks
	bool IsEscapePressed();
	bool IsLeftArrowPressed();
	bool IsRightArrowPressed();
	bool IsUpArrowPressed();
	bool IsDownArrowPressed();
	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsQPressed();
	bool IsEPressed();
	bool IsSpacePressed();
	bool IsLeftControlPressed();
	bool IsMPressed();
	bool IsNPressed();
	bool IsMovementPressed();

	// Gets mouse position
	void GetMouseLocation(int& mouseX, int& mouseY);

private:

	//|-------------------------------Private Functions-------------------------|

	// Read the current state of the keyboard
	bool ReadKeyboard();

	// Read the current state of the mouse
	bool ReadMouse();

	// Process the changes in the mouse and keyboard
	void ProcessInput();

private:

	//|-----------------------------Private Data Members------------------------|

	// Pointers to mouse, keyboard, input
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	// States for mouse and keyboard
	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	// screen dimensions for use with mouse
	int m_screenWidth, m_screenHeight;

	// mouse coordinates
	int m_mouseX, m_mouseY;
};