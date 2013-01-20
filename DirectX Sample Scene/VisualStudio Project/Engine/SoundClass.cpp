// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// SoundClass
//		The SoundClass encapsulates the DirectSound functionality as well as the 
//		.wav audio loading and playing capabilities.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "soundclass.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
SoundClass::SoundClass() :
	m_DirectSound(0),
	m_primaryBuffer(0),
	m_music(0),
	m_shipEngine(0),
	m_playMusic(false),
	m_playShipEngine(false),
	m_globalMute(false),
	m_volumeMusic(DSBVOLUME_MIN),
	m_volumeShipEngine(DSBVOLUME_MIN)
{
}
 
 
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
SoundClass::SoundClass(const SoundClass& other)
{
}
 
 
// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
SoundClass::~SoundClass()
{
}
 
 
// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool SoundClass::Initialize(HWND hwnd)
{
	bool result;

	// Initialize direct sound and the primary sound buffer.
	result = InitializeDirectSound(hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize direct sound.", L"Error", MB_OK);
		return false;
	}
 
	// Load a wave audio file onto a secondary buffer.
	result = LoadWaveFile("../../data/music03.wav", &m_music, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not load music03.wav.", L"Error", MB_OK);
		return false;
	}
 
	// Load a wave audio file onto a secondary buffer.
	result = LoadWaveFile("../../data/engine_sound02.wav", &m_shipEngine, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not load engine_sound02.wav.", L"Error", MB_OK);
		return false;
	}

	// Start everything playing (it will be silent)
	m_music->Play(0, 0, DSBPLAY_LOOPING);
	m_shipEngine->Play(0, 0, DSBPLAY_LOOPING);

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void SoundClass::Shutdown()
{
	// Release the secondary buffers.
	ShutdownWaveFile(&m_music);
	ShutdownWaveFile(&m_shipEngine);

	// Shutdown the Direct Sound API.
	ShutdownDirectSound();
 
	return;
}


// |----------------------------------------------------------------------------|
// |						   InitializeDirectSound							|
// |----------------------------------------------------------------------------|
bool SoundClass::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
 
	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"DirectSoundCreate8 failed.", L"Error", MB_OK);
		return false;
	}
 
	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"SetCooperativeLevel failed.", L"Error", MB_OK);
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
 
	// Get control of the primary sound buffer on the default sound device.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"CreateSoundBuffer failed.", L"Error", MB_OK);
		return false;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"m_primaryBuffer->SetFormat failed.", L"Error", MB_OK);
		return false;
	}
 
	return true;
}


// |----------------------------------------------------------------------------|
// |						     ShutdownDirectSound							|
// |----------------------------------------------------------------------------|
void SoundClass::ShutdownDirectSound()
{
	// Release the primary sound buffer pointer.
	if(m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}
 
	// Release the direct sound interface pointer.
	if(m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}
 
	return;
}


// |----------------------------------------------------------------------------|
// |						         LoadWaveFile								|
// |----------------------------------------------------------------------------|
bool SoundClass::LoadWaveFile(char* filename, IDirectSoundBuffer8** secondaryBuffer, HWND hwnd)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		MessageBox(hwnd, L"Open file failed.", L"Error", MB_OK);
		return false;
	}
 
	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if(count != 1)
	{
		MessageBox(hwnd, L"Reading header failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the chunk ID is the RIFF format.
	if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') || 
	   (waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		MessageBox(hwnd, L"Check for chunk ID in the RIFF format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the file format is the WAVE format.
	if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
	   (waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		MessageBox(hwnd, L"Check for WAVE file format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the sub chunk ID is the fmt format.
	if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
	   (waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		MessageBox(hwnd, L"Check for sub chunk ID in fmt format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the audio format is WAVE_FORMAT_PCM.
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		MessageBox(hwnd, L"Check for WAVE_FORMAT_PCM audio format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the wave file was recorded in stereo format.
	if(waveFileHeader.numChannels != 2)
	{
		MessageBox(hwnd, L"Check for stereo format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if(waveFileHeader.sampleRate != 44100)
	{
		MessageBox(hwnd, L"Check for sample rate of 44.1 KHz failed.", L"Error", MB_OK);
		return false;
	}
 
	// Ensure that the wave file was recorded in 16 bit format.
	if(waveFileHeader.bitsPerSample != 16)
	{
		MessageBox(hwnd, L"Check for 16 bit format failed.", L"Error", MB_OK);
		return false;
	}
 
	// Check for the data chunk header.
	if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
	   (waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		MessageBox(hwnd, L"Check for data chunk header failed.", L"Error", MB_OK);
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"CreateSoundBuffer failed.", L"Error", MB_OK);
		return false;
	}
 
	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"QueryInterface failed.", L"Error", MB_OK);
		return false;
	}
 
	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);
 
	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if(!waveData)
	{
		MessageBox(hwnd, L"Creating waveData array failed.", L"Error", MB_OK);
		return false;
	}
 
	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if(count != waveFileHeader.dataSize)
	{
		MessageBox(hwnd, L"fread wavedata array failed.", L"Error", MB_OK);
		return false;
	}
 
	// Close the file once done reading.
	error = fclose(filePtr);
	if(error != 0)
	{
		MessageBox(hwnd, L"Closing file failed.", L"Error", MB_OK);
		return false;
	}
 
	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"Locking secondary buffer failed.", L"Error", MB_OK);
		return false;
	}
 
	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);
 
	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		MessageBox(hwnd, L"Unlocking secondary buffer failed.", L"Error", MB_OK);
		return false;
	}
	
	// Release the wave data since it was copied into the secondary buffer.
	delete [] waveData;
	waveData = 0;
 
	return true;
}


// |----------------------------------------------------------------------------|
// |						        ShutdownWaveFile							|
// |----------------------------------------------------------------------------|
void SoundClass::ShutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	// Release the secondary sound buffer.
	if(*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						        StartShipEngine								|
// |----------------------------------------------------------------------------|
bool SoundClass::Frame(float frameTime)
{
	bool result;

	// Process Music
	result =  ProcessSound(frameTime, m_music, m_playMusic, m_volumeMusic);
	if(!result)
	{
		return false;
	}

	// Process Ship Engine
	result =  ProcessSound(frameTime, m_shipEngine, m_playShipEngine, m_volumeShipEngine);
	if(!result)
	{
		return false;
	}

	return true;

}


// |----------------------------------------------------------------------------|
// |						        ProcessSound								|
// |----------------------------------------------------------------------------|
bool SoundClass::ProcessSound(float frameTime, IDirectSoundBuffer8* &buffer, 
	bool &onOffSetting, LONG &volume)
{
	HRESULT result;
 
	// Update volume
	//if (onOffSetting) volume = DSBVOLUME_MAX;
	//else volume = DSBVOLUME_MIN;
	if (onOffSetting) volume += 100;
	else volume -= 100;
	if (volume > DSBVOLUME_MAX) volume = DSBVOLUME_MAX;
	if (volume < DSBVOLUME_MIN) volume = DSBVOLUME_MIN;
	if (m_globalMute) volume = DSBVOLUME_MIN;
	result = buffer->SetVolume(volume);
	if(FAILED(result))
	{
		return false;
	}

	return true;

}


// |----------------------------------------------------------------------------|
// |						        StartShipEngine								|
// |----------------------------------------------------------------------------|
bool SoundClass::StartShipEngine()
{
	m_playShipEngine = true;
	return true;
}


// |----------------------------------------------------------------------------|
// |						        StopShipEngine								|
// |----------------------------------------------------------------------------|
bool SoundClass::StopShipEngine()
{
	m_playShipEngine = false;
	return true;
}


// |----------------------------------------------------------------------------|
// |						          StartMusic								|
// |----------------------------------------------------------------------------|
bool SoundClass::StartMusic()
{
	m_playMusic = true;
	return true;
}


// |----------------------------------------------------------------------------|
// |						           StopMusic								|
// |----------------------------------------------------------------------------|
bool SoundClass::StopMusic()
{
	m_playMusic = false;
	return true;
}


// |----------------------------------------------------------------------------|
// |						            Mute									|
// |----------------------------------------------------------------------------|
bool SoundClass::Mute()
{
	m_globalMute = true;

	return m_globalMute;
}


// |----------------------------------------------------------------------------|
// |						            UnMute									|
// |----------------------------------------------------------------------------|
bool SoundClass::UnMute()
{
	m_globalMute = false;

	return m_globalMute;
}