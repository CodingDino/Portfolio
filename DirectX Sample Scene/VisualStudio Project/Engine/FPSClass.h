// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// FpsClass
//		Controls counter for FPS display
#pragma once


// |----------------------------------------------------------------------------|
// |							      Linking									|
// |----------------------------------------------------------------------------|
#pragma comment(lib, "winmm.lib")


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <windows.h>
#include <mmsystem.h>


// |----------------------------------------------------------------------------|
// |						     Class: FpsClass								|
// |----------------------------------------------------------------------------|
class FpsClass
{
public:
	
	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	FpsClass();
	FpsClass(const FpsClass&);
	~FpsClass();
	
	// Initiallizes the object
	void Initialize();

	// Called once each frame render
	void Frame();

	// Getter functions
	int GetFps();

private:

	//|-----------------------------Private Data Members------------------------|
	int m_fps, m_count;
	unsigned long m_startTime;

};
