// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// TextClass
//		Handles all 2D text drawing, renders 2D text to the sreen
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "fontclass.h"
#include "fontshaderclass.h"


// |----------------------------------------------------------------------------|
// |					        Class: TextClass								|
// |----------------------------------------------------------------------------|
class TextClass
{
private:
	
	//|-----------------------------Private Data Types--------------------------|
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	TextClass();
	TextClass(const TextClass&);
	~TextClass();
	
	// Initializes object
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, 
		HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix);

	// Shutdown, deallocation, and cleanup
	void Shutdown();

	// Renders the font as a 2D texture to the DX device
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	// Sets the text to a display of the mouse position
	bool SetMousePosition(int, int, ID3D11DeviceContext*);	
	
	// Sets the text to a readout of the FPS and CPU
	bool SetFps(int, ID3D11DeviceContext*);
	bool SetCpu(int, ID3D11DeviceContext*);

private:

	//|-------------------------------Private Functions-------------------------|

	// Initiallizes the string
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);

	// Updates the sentence to the supplied string
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);

	// Shutdown operations for the sentence data
	void ReleaseSentence(SentenceType**);

	// Renders the sentence to the screen
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);

private:

	//|-----------------------------Private Data Members------------------------|

	// Font objects
	FontClass* m_Font;
	FontShaderClass* m_FontShader;

	// Screen stats
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;

	// TODO: 2 sentences used in the tutorial, may need to adjust this later
	SentenceType* m_sentence1;
	SentenceType* m_sentence2;
};
