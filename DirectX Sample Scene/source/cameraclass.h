// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// CameraClass
//		Methods for setting the position and rotation of the camera.
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3dx10math.h>


// |----------------------------------------------------------------------------|
// |						   Class: CameraClass								|
// |----------------------------------------------------------------------------|
class CameraClass
{
public:
	//|-------------------------------Public Functions--------------------------|

	// Constrcutors and Deconstructors
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	// Get and set functions
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void GetViewMatrix(D3DXMATRIX&);

	// Transforms the viewMatrix for use with rendering
	void Render();

private:
	//|-----------------------------Private Data Members------------------------|

	// Position of the camera in the game world
	float m_positionX, m_positionY, m_positionZ;

	// Rotation of the camera in the game world
	float m_rotationX, m_rotationY, m_rotationZ;

	// Matrix for use with world transformations, set by Render function
	D3DXMATRIX m_viewMatrix;
};