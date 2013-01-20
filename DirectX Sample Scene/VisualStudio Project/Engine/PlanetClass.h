// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// PlanetClass
//		Contains model and texture for the planet. Also contains data and methods
//		for radius, rotation speed, orbit speed, radius of orbit, center of orbit, and 
//		plane of orbit.
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "ModelClass.h"
#include "Coord.h"


// |----------------------------------------------------------------------------|
// |					       Class: PlanetClass								|
// |----------------------------------------------------------------------------|
class PlanetClass
{
public:

	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	PlanetClass();
	PlanetClass(const PlanetClass&);
	~PlanetClass();

	// Initialize the model, reads in a vertex and texture file
	bool Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename,
		float radius, float rotation_speed, float rotation_tilt, float orbit_speed, 
		float orbit_radius, Coord orbit_center, float orbit_tilt);

	// Releases data associated with the model
	void Shutdown();

	// Updates position for this planet based on it's orbit and rotation
	void Frame(float frameTime);

	// Renders the model to the supplied context
	void Render(ID3D11DeviceContext* deviceContext);

	// Getter functions
	void GetModel(ModelClass* &model);
	D3DXMATRIX GetScale();
	D3DXMATRIX GetTranslate();
	D3DXMATRIX GetRotate();

	void SetOrbitCenter(float x, float y, float z);

private:

	//|-----------------------------Private Data Members------------------------|
	ModelClass* m_model;

	// Planet constants
	float m_radius;
	float m_rotation_speed;
	float m_rotation_tilt;
	float m_orbit_speed;
	float m_orbit_radius;
	Coord m_orbit_center;
	float m_orbit_tilt;

	// Planet position
	float m_rotation;
	float m_orbit;

};