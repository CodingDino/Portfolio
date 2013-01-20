// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// BitmapClass
//		Holds one bitmap
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"


// |----------------------------------------------------------------------------|
// |						  Class: BitmapClass								|
// |----------------------------------------------------------------------------|
class BitmapClass
{
private:

	//|---------------------------------Type Defs------------------------------|
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	// Initiallizes a bitmap
	bool Initialize(ID3D11Device* device, int screenWidth, int screenHeight, 
		WCHAR* textureFilename, int bitmapWidth, int bitmapHeight);

	// Releases bitmap data
	void Shutdown();
	
	// Renders to screen
	bool Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY);

	// Getter functions
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:

	//|-------------------------------Private Functions--------------------------|
	
	// Sets up the buffers associated with this bitmap
	bool InitializeBuffers(ID3D11Device*);

	// Releases buffers associated with this model
	void ShutdownBuffers();

	// Updates buffers associated with this model
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);

	// Renders the buffers
	void RenderBuffers(ID3D11DeviceContext*);
	
	// Loads the given texture from file
	bool LoadTexture(ID3D11Device*, WCHAR*);

	// Releases the texture data
	void ReleaseTexture();

	//|-----------------------------Private Data Members------------------------|

	// Model and texture data members
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;

	// Screen location information
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;

};