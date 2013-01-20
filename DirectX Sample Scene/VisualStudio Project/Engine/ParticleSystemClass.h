// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// ParticleSystemClass
//		This class renders the particle textures to the screen as needed.
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <cmath>
#include "textureclass.h"
using namespace std;


// |----------------------------------------------------------------------------|
// |						 Class: ParticleSystemClass							|
// |----------------------------------------------------------------------------|
class ParticleSystemClass
{
private:
	
	//|------------------------------Type Declarations--------------------------|

	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocityX, velocityY, velocityZ;
		bool active;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};

public:

	//|-------------------------------Public Functions--------------------------|

	ParticleSystemClass();
	ParticleSystemClass(const ParticleSystemClass&);
	~ParticleSystemClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*, float camX, float camY, float camZ);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

	void SetPosition(float new_x, float new_y, float new_z);

private:

	//|------------------------------Private Functions--------------------------|

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float, float camX, float camY, float camZ);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext*);

	void RenderBuffers(ID3D11DeviceContext*);

private:
	
	//|-----------------------------Private Data Members------------------------|

	float x, y, z;

	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;

	int m_currentParticleCount;
	float m_accumulatedTime;

	TextureClass* m_Texture;

	ParticleType* m_particleList;

	int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
};
