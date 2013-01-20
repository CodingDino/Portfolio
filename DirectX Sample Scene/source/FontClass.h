// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// FontClass
//		Holds the font information
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "textureclass.h"
using namespace std;


// |----------------------------------------------------------------------------|
// |						     Class: FontClass								|
// |----------------------------------------------------------------------------|
class FontClass
{
private:

	//|---------------------------------Type Defs------------------------------|
	struct FontType
	{
		float left, right;
		int size;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:

	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	// Initiallizes a font
	bool Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);

	// Releases font data
	void Shutdown();
	
	// Builds the array of triangles that will render the characte sentence
	void BuildVertexArray(void*, char*, float, float);

	// Getter functions
	ID3D11ShaderResourceView* GetTexture();

private:

	//|-------------------------------Private Functions--------------------------|
	
	// Loads the given texture from file
	bool LoadTexture(ID3D11Device*, WCHAR*);

	// Releases the texture data
	void ReleaseTexture();

	// Loads the given font from file
	bool LoadFontData(char*);

	// Releases the font data
	void ReleaseFontData();

	//|-----------------------------Private Data Members------------------------|
	FontType* m_Font;
	TextureClass* m_Texture;

};