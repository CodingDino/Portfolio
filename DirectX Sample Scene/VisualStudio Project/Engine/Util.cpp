// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// Util
//		Game-wide utilities.

// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Util.h"
#include <Windows.h>

void debug(const char* msg, int level) 
{ 
	if (level <= DEBUG_MODE)
	{
		OutputDebugStringA(msg);
		OutputDebugStringA("\n");
	}
}