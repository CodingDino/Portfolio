// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// PlanetClass
//		Contains model and texture for the planet. Also contains data and methods
//		for radius, rotation speed, orbit speed, radius of orbit, center of orbit, and 
//		plane of orbit.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "PlanetClass.h"


//|----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
PlanetClass::PlanetClass() :
	m_model(0),
	m_radius(0),
	m_rotation_speed(0),
	m_rotation_tilt(0),
	m_orbit_speed(0),
	m_orbit_radius(0),
	m_orbit_center(0,0,0),
	m_orbit_tilt(0),
	m_rotation(0),
	m_orbit(0)
{
}

	
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
PlanetClass::PlanetClass(const PlanetClass& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
PlanetClass::~PlanetClass()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool PlanetClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename,
		float radius, float rotation_speed, float rotation_tilt, float orbit_speed, 
		float orbit_radius, Coord orbit_center, float orbit_tilt)
{
	// Create model
	m_model = new ModelClass;
	if(!m_model)
	{
		return false;
	}	
	// Initialize the model object.
	if(!(m_model->Initialize(device, modelFilename, textureFilename)))
	{
		return false;
	}

	// Set planet constants
	m_radius =			radius			* 1;
	m_rotation_speed =	rotation_speed	* 100;
	m_rotation_tilt =	rotation_tilt	* 1;
	m_orbit_speed =		orbit_speed		* 1000;
	m_orbit_radius =	orbit_radius	* 30;
	m_orbit_center =	Coord(orbit_center.x*30,orbit_center.y*30,orbit_center.z*30);
	m_orbit_tilt =		orbit_tilt		* 1;

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void PlanetClass::Shutdown()
{

	// Shutdown model
	if(m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       Frame										|
// |----------------------------------------------------------------------------|
void PlanetClass::Frame(float frameTime)
{

	// Apply rotation change
	m_rotation -= m_rotation_speed / frameTime;
	if(m_rotation < 0.0f)
	{
		m_rotation += 360.0f;
	}
	if(m_rotation > 360.0f)
	{
		m_rotation -= 360.0f;
	}

	// Apply orbit change
	m_orbit -= m_orbit_speed / frameTime;
	if(m_orbit < 0.0f)
	{
		m_orbit += 360.0f;
	}
	if(m_orbit > 360.0f)
	{
		m_orbit -= 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       Render										|
// |----------------------------------------------------------------------------|
void PlanetClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	if(m_model)
	{
		m_model->Render(deviceContext);
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       GetModel										|
// |----------------------------------------------------------------------------|
void PlanetClass::GetModel(ModelClass* &model)
{
	model = m_model;

	return;
}


// |----------------------------------------------------------------------------|
// |						       GetScale										|
// |----------------------------------------------------------------------------|
D3DXMATRIX PlanetClass::GetScale()
{
	D3DXMATRIX scaleMatrix;

	D3DXMatrixScaling(&scaleMatrix, m_radius, m_radius, m_radius);

	return scaleMatrix;
}


// |----------------------------------------------------------------------------|
// |						      GetTranslate									|
// |----------------------------------------------------------------------------|
D3DXMATRIX PlanetClass::GetTranslate()
{
	D3DXMATRIX worldMatrix, translationMatrix, radiusMatrix, orbitMatrix, tiltMatrix;

	// Translate to orbit center
	D3DXMatrixTranslation(&translationMatrix, m_orbit_center.x, m_orbit_center.y, m_orbit_center.z);

	// Translate out to orbit radius
	D3DXMatrixTranslation(&radiusMatrix, m_orbit_radius, 0, 0);

	// Determine point in orbit
	D3DXMatrixRotationYawPitchRoll(&orbitMatrix, 0.01745f*m_orbit, 0, 0);

	// Determine skew of orbit based on orbit rotation
	D3DXMatrixRotationYawPitchRoll(&tiltMatrix, 0, 0.01745f*m_orbit_tilt, 0);
	
	// Translate first, then rotate and skew
	worldMatrix = radiusMatrix * orbitMatrix * tiltMatrix * translationMatrix;

	return worldMatrix;
}


// |----------------------------------------------------------------------------|
// |						       GetRotate									|
// |----------------------------------------------------------------------------|
D3DXMATRIX PlanetClass::GetRotate()
{
	D3DXMATRIX worldMatrix, orbitMatrix, rotationMatrix, tiltMatrix;

	// Determine point in rotation
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 0.01745f*m_rotation, 0, 0);

	// Determine tilt
	D3DXMatrixRotationYawPitchRoll(&tiltMatrix, 0, 0, 0.01745f*m_rotation_tilt);

	// Determine point in orbit
	// Actually I don't think this is a thing
	D3DXMatrixRotationYawPitchRoll(&orbitMatrix, 0.01745f*-1*m_orbit, 0, 0);

	// Translate first, then rotate and skew
	worldMatrix = rotationMatrix * tiltMatrix;

	return worldMatrix;
}

// |----------------------------------------------------------------------------|
// |						      SetOrbitCenter								|
// |----------------------------------------------------------------------------|
void PlanetClass::SetOrbitCenter(float x, float y, float z)
{
	m_orbit_center.x = x;
	m_orbit_center.y = y;
	m_orbit_center.z = z;
}