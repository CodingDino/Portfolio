// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// FontClass
//		Holds the font information


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "FontClass.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
FontClass::FontClass() :
	m_Font(0),
	m_Texture(0)
{
}

	
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
FontClass::FontClass(const FontClass& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
FontClass::~FontClass()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool FontClass::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename) 
{
	bool result;

	// Load in the text file containing the font data.
	result = LoadFontData(fontFilename);
	if(!result)
	{
		return false;
	}

	// Load the texture that has the font characters on it.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void FontClass::Shutdown()
{
	// Release the font texture.
	ReleaseTexture();

	// Release the font data.
	ReleaseFontData();

	return;
}


// |----------------------------------------------------------------------------|
// |							 LoadFontData									|
// |----------------------------------------------------------------------------|
bool FontClass::LoadFontData(char* filename)
{
	ifstream fin;
	int i;
	char temp;

	/*First we create an array of the FontType structure. The size of the array 
	is set to 95 as that is the number of characters in the texture and hence the 
	number of indexes in the fontdata.txt file.*/

	// Create the font spacing buffer.
	m_Font = new FontType[95];
	if(!m_Font)
	{
		return false;
	}

	/*Now we open the file and read each line into the array m_Font. We only 
	need to read in the texture TU left and right coordinates as well as the 
	pixel size of the character.*/

	// Read in the font size and spacing between chars.
	fin.open(filename);
	if(fin.fail())
	{
		return false;
	}

	// Read in the 95 used ascii characters for text.
	for(i=0; i<95; i++)
	{
		fin.get(temp);
		while(temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while(temp != ' ')
		{
			fin.get(temp);
		}

		fin >> m_Font[i].left;
		fin >> m_Font[i].right;
		fin >> m_Font[i].size;
	}

	// Close the file.
	fin.close();

	return true;
}


// |----------------------------------------------------------------------------|
// |							ReleaseFontData									|
// |----------------------------------------------------------------------------|
void FontClass::ReleaseFontData()
{
	// Release the font data array.
	if(m_Font)
	{
		delete [] m_Font;
		m_Font = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |							 LoadTexture									|
// |----------------------------------------------------------------------------|
bool FontClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |							 ReleaseTexture									|
// |----------------------------------------------------------------------------|
void FontClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |							   GetTexture									|
// |----------------------------------------------------------------------------|
ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_Texture->GetTexture();
}


// |----------------------------------------------------------------------------|
// |							BuildVertexArray								|
// |----------------------------------------------------------------------------|
void FontClass::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i, letter;


	// Coerce the input vertices into a VertexType structure.
	vertexPtr = (VertexType*)vertices;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(sentence);

	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for(i=0; i<numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;

		// If the letter is a space then just move over three pixels.
		if(letter == 0)
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			// First triangle in quad.
			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX, (drawY - 16), 0.0f);  // Bottom left.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 1.0f);
			index++;

			// Second triangle in quad.
			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX + m_Font[letter].size, drawY, 0.0f);  // Top right.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 1.0f);
			index++;

			// Update the x location for drawing by the size of the letter and one pixel.
			drawX = drawX + m_Font[letter].size + 1.0f;
		}
	}

	return;
}