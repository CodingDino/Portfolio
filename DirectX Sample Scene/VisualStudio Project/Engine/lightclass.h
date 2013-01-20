// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// LightClass
//		Controls light direction, color, intensity, and type.
//		TODO: Revamp to allow multiple light sources, light sources in scene.
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3dx10math.h>


// |----------------------------------------------------------------------------|
// |						   Class: LightClass								|
// |----------------------------------------------------------------------------|
class LightClass
{
public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	LightClass();
	LightClass(const LightClass&);
	~LightClass();
	
	// Setter functions
	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	//void SetDirection(float, float, float);
	void SetPosition(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);
	
	// Getter functions
	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	//D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();
	D3DXVECTOR4 GetPosition();

private:

	//|-----------------------------Private Data Members------------------------|

	// Light colors
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_specularColor;

	// Direction (used for diffuse and specular)
	//D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_position;

	// Specular intensity
	float m_specularPower;

};