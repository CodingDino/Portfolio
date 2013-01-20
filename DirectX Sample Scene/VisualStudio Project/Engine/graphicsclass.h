// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// GraphicsClass
//		Overall control of graphics and rendering, holds model objects and other graphics objects
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "d3dclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "textureshaderclass.h"
#include "lightclass.h"
#include "Coord.h"
#include "Util.h"
#include "BitmapClass.h"
#include "textclass.h"
#include "PlanetClass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"


// |----------------------------------------------------------------------------|
// |								 Globals									|
// |----------------------------------------------------------------------------|
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const int NUM_MODELS=20;


// |----------------------------------------------------------------------------|
// |					       Class: GraphicsClass								|
// |----------------------------------------------------------------------------|
class GraphicsClass
{
public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	
	// Creates and initializes all data members, sets initial graphics state
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

	// Performs shutdown, deallocation, and cleanup for data members
	void Shutdown();

	// Frame-by-frame graphics processing
	bool Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime, 
		Coord camera_rotation, Coord camera_position, bool transfer);

private:

	//|-------------------------------Private Functions-------------------------|

	// Calls render functions in order
	bool Render(int mouseX, int mouseY, Coord camera_position);

	// Rendering setup (starts scene, gets world, view, and projection matrix)
	bool BeginRender();

	// Rendering cleanup (ends the scene)
	bool EndRender();

	// Renders the passed in model using the given transforms
	bool ModelRender(ModelClass& to_render, D3DXMATRIX scale, 
		D3DXMATRIX translate, D3DXMATRIX rotate);
	bool SunRender(ModelClass& to_render, D3DXMATRIX scale, 
		D3DXMATRIX translate, D3DXMATRIX rotate);

	// Renders the passed in bitmap using the given transforms
	bool BitmapRender(BitmapClass& to_render, int x, int y);

private:

	//|-----------------------------Private Data Members------------------------|

	// DirectX object
	D3DClass* m_D3D;

	// Camera
	CameraClass* m_Camera;

	// Shaders
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;

	// Light source
	LightClass* m_Light;

	// Matrices
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// 2D Bitmaps
	BitmapClass* crosshairs;
	BitmapClass* HUD;
	BitmapClass* m_titleScreen;
	BitmapClass* m_controlsScreen;

	// Screen
	int m_screen;
	float m_screen_counter;

	// FPS output
	TextClass* m_Text;

	// Planets
	PlanetClass* m_sun;
	PlanetClass* m_mercury;
	PlanetClass* m_venus;
	PlanetClass* m_earth;
	PlanetClass* m_mars;
	PlanetClass* m_jupiter;
	PlanetClass* m_saturn;
	PlanetClass* m_uranus;
	PlanetClass* m_neptune;
	PlanetClass* m_halley;
	PlanetClass* m_luna;
	PlanetClass* m_phobos;
	PlanetClass* m_deimos ;

	// Skubox
	ModelClass* m_skybox;

	// Screen dimmensions
	int m_screenWidth;
	int m_screenHeight;

	// Particle system
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
};