// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// TextureClass
//		Holds one texture
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx11tex.h>


// |----------------------------------------------------------------------------|
// |						  Class: TextureClass								|
// |----------------------------------------------------------------------------|
class TextureClass
{
public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	// Initiallizes a texture
	bool Initialize(ID3D11Device* device, WCHAR* filename);

	// Releases texture data
	void Shutdown();

	// Getter functions
	ID3D11ShaderResourceView* GetTexture();

private:

	//|-----------------------------Private Data Members------------------------|

	// Texture
	ID3D11ShaderResourceView* m_texture;

};