// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// LightClass
//		Controls light direction, color, intensity, and type.
//		TODO: Revamp to allow multiple light sources, light sources in scene.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "lightclass.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
LightClass::LightClass()
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
LightClass::LightClass(const LightClass& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
LightClass::~LightClass()
{
}


// |----------------------------------------------------------------------------|
// |						    SetAmbientColor									|
// |----------------------------------------------------------------------------|
void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}


// |----------------------------------------------------------------------------|
// |						    SetDiffuseColor									|
// |----------------------------------------------------------------------------|
void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}



// |----------------------------------------------------------------------------|
// |						    SetDirection									|
// |----------------------------------------------------------------------------|
/*void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}*/


// |----------------------------------------------------------------------------|
// |						     SetPosition									|
// |----------------------------------------------------------------------------|
void LightClass::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR4(x, y, z, 1.0f);
	return;
}

// |----------------------------------------------------------------------------|
// |						   SetSpecularColor									|
// |----------------------------------------------------------------------------|
void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}


// |----------------------------------------------------------------------------|
// |						   SetSpecularPower									|
// |----------------------------------------------------------------------------|
void LightClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}


// |----------------------------------------------------------------------------|
// |						   GetAmbientColor									|
// |----------------------------------------------------------------------------|
D3DXVECTOR4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}


// |----------------------------------------------------------------------------|
// |						   GetDiffuseColor									|
// |----------------------------------------------------------------------------|
D3DXVECTOR4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


// |----------------------------------------------------------------------------|
// |						    GetDirection									|
// |----------------------------------------------------------------------------|
/*D3DXVECTOR3 LightClass::GetDirection()
{
	return m_direction;
}*/


// |----------------------------------------------------------------------------|
// |						    GetDirection									|
// |----------------------------------------------------------------------------|
D3DXVECTOR4 LightClass::GetPosition()
{
	return m_position;
}


// |----------------------------------------------------------------------------|
// |						   GetSpecularColor									|
// |----------------------------------------------------------------------------|
D3DXVECTOR4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}


// |----------------------------------------------------------------------------|
// |						   GetSpecularPower									|
// |----------------------------------------------------------------------------|
float LightClass::GetSpecularPower()
{
	return m_specularPower;
}