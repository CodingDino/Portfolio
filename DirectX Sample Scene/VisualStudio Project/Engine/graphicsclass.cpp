// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// GraphicsClass
//		Overall control of graphics and rendering, holds model objects and other graphics objects


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "graphicsclass.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
GraphicsClass::GraphicsClass() :
	m_D3D(0),
	m_Camera(0),
	m_LightShader(0),
	m_TextureShader(0),
	m_Light(0),
	crosshairs(0),
	HUD(0),
	m_Text(0),
	m_sun(0),
	m_mercury(0),
	m_venus(0),
	m_earth(0),
	m_mars(0),
	m_saturn(0),
	m_jupiter(0),
	m_uranus(0),
	m_neptune(0),
	m_halley(0),
	m_skybox(0),
	m_ParticleShader(0),
	m_ParticleSystem(0),
	m_titleScreen(0),
	m_controlsScreen(0),
	m_screen(0),
	m_screen_counter(0),
	m_luna(0),
	m_phobos(0),
	m_deimos(0)
{
}

	
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
GraphicsClass::~GraphicsClass()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Record screen dimmensions
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create and initialize planets
	// NOTE: Sun is scaled down to better show planets
	// NOTE: Distance between planets scaled down drastically to better show them all
	m_sun = new PlanetClass;
	if(!m_sun) return false;
	result = m_sun->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",		// Model
		L"../../data/star_sol.png",		// Texture
		20.0f,								// Radius (compared to Earth)
		0.04f,								// Rotation speed (rot/sec ~ rot/day)
		7.25f,								// Axial tilt
		0.0f,								// Orbital speed (orbit/sec ~ orbit/day)
		0.0f,								// Orbital radius (in AU)
		Coord(0,0,0),						// Orbit center
		0.0f);								// Orbital tilt

	m_mercury = new PlanetClass;
	if(!m_mercury) return false;
	result = m_mercury->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_mercury.png",	// Texture
		0.38f,									// Radius (compared to Earth)
		0.0171f,								// Rotation speed (rot/sec ~ rot/day)
		2.11f,									// Axial tilt
		0.0113f,								// Orbital speed (orbit/sec ~ orbit/day)
		//0.467f,								// Orbital radius (in AU)
		2.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		7.0f);									// Orbital tilt

	m_venus = new PlanetClass;
	if(!m_venus) return false;
	result = m_venus->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_venus.png",		// Texture
		0.950f,									// Radius (compared to Earth)
		0.00412f,								// Rotation speed (rot/day)
		177.3f,									// Axial tilt
		0.00444f,								// Orbital speed (orbit/day)
		//0.723f,								// Orbital radius (in AU)
		3.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		3.39f);									// Orbital tilt

	m_earth = new PlanetClass;
	if(!m_earth) return false;
	result = m_earth->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_earth.png",		// Texture
		1.0f,									// Radius (compared to Earth)
		1.0f,									// Rotation speed (rot/day)
		23.0f,									// Axial tilt
		0.00274f,								// Orbital speed (orbit/day)
		//1.00f,									// Orbital radius (in AU)
		4.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		0.00f);									// Orbital tilt

	m_mars = new PlanetClass;
	if(!m_mars) return false;
	result = m_mars->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_mars.png",		// Texture
		0.533f,									// Radius (compared to Earth)
		0.976f,									// Rotation speed (rot/day)
		25.2f,									// Axial tilt
		0.00146f,								// Orbital speed (orbit/day)
		//1.52f,								// Orbital radius (in AU)
		5.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		1.85f);									// Orbital tilt

	m_jupiter = new PlanetClass;
	if(!m_jupiter) return false;
	result = m_jupiter->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_jupiter.png",	// Texture
		11.209f,								// Radius (compared to Earth)
		2.418f,									// Rotation speed (rot/day)
		3.13f,									// Axial tilt
		0.0002308f,								// Orbital speed (orbit/day)
		//5.204267f,							// Orbital radius (in AU)
		7.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		1.305f);								// Orbital tilt

	m_saturn = new PlanetClass;
	if(!m_saturn) return false;
	result = m_saturn->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_saturn.png",	// Texture
		9.4492f,								// Radius (compared to Earth)
		0.426f,									// Rotation speed (rot/day)
		26.73f,									// Axial tilt
		0.0000929f,								// Orbital speed (orbit/day)
		//9.582f,								// Orbital radius (in AU)
		8.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		2.485f);								// Orbital tilt

	m_uranus = new PlanetClass;
	if(!m_uranus) return false;
	result = m_uranus->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_uranus.png",	// Texture
		3.883f,									// Radius (compared to Earth)
		1.39f,									// Rotation speed (rot/day)
		97.77f,									// Axial tilt
		0.0000325f,								// Orbital speed (orbit/day)
		//19.229f,								// Orbital radius (in AU)
		9.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		0.772f);								// Orbital tilt

	m_neptune = new PlanetClass;
	if(!m_neptune) return false;
	result = m_neptune->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/planet_neptune.png",	// Texture
		4.007f,									// Radius (compared to Earth)
		1.4896f,								// Rotation speed (rot/day)
		28.32f,									// Axial tilt
		0.0000166f,								// Orbital speed (orbit/day)
		//30.1f,								// Orbital radius (in AU)
		10.0f,									// Orbital radius (in AU)
		Coord(0,0,0),							// Orbit center
		1.768f);								// Orbital tilt
	
	m_halley = new PlanetClass;
	if(!m_halley) return false;
	result = m_halley->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/comet.jpg",			// Texture
		0.1f,									// Radius
		0.5f,									// Rotation speed (rot/day)
		0.0f,									// Axial tilt
		0.0000364f,								// Orbital speed (orbit/day)
		5.0f,									// Orbital radius
		Coord(2,0,1),							// Orbit center
		162.0f);								// Orbital tilt

	m_luna = new PlanetClass;
	if(!m_luna) return false;
	result = m_luna->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/luna.jpg",				// Texture
		0.273f,									// Radius
		0.0357f,								// Rotation speed (rot/day)
		1.5f,									// Axial tilt
		0.0357f,								// Orbital speed (orbit/day)
		0.1f,									// Orbital radius
		Coord(0,0,0),							// Orbit center
		5.145f);								// Orbital tilt

	m_phobos = new PlanetClass;
	if(!m_phobos) return false;
	result = m_phobos->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/phobos.jpg",			// Texture
		0.21f,									// Radius
		0.3f,									// Rotation speed (rot/day)
		0.0f,									// Axial tilt
		0.3f,									// Orbital speed (orbit/day)
		0.05f,									// Orbital radius
		Coord(0,0,0),							// Orbit center
		26.04f);								// Orbital tilt

	m_deimos = new PlanetClass;
	if(!m_deimos) return false;
	result = m_deimos->Initialize(m_D3D->GetDevice(), 
		"../../data/sphere.txt",			// Model
		L"../../data/deimos.jpg",			// Texture
		0.097f,									// Radius
		0.0792f,								// Rotation speed (rot/day)
		0.0f,									// Axial tilt
		0.0792f,								// Orbital speed (orbit/day)
		0.1f,									// Orbital radius
		Coord(0,0,0),							// Orbit center
		27.58f);								// Orbital tilt

	m_skybox = new ModelClass;
	if(!m_skybox) return false;
	result = m_skybox->Initialize(m_D3D->GetDevice(), 
		"../../data/cube.txt",			
		L"../../data/starfield06.png");

	// Create the shader objects.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}
	m_TextureShader = new TextureShaderClass;
	if(!m_LightShader)
	{
		return false;
	}
	

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 0.75f, 1.0f);
	//m_Light->SetDirection(1.0f, -1.0f, 1.0f);
	m_Light->SetPosition(0.0f, 0.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Create the bitmap objects.
	crosshairs = new BitmapClass;
	if(!crosshairs)
	{
		return false;
	}
	HUD = new BitmapClass;
	if(!HUD)
	{
		return false;
	}
	m_titleScreen = new BitmapClass;
	if(!m_titleScreen)
	{
		return false;
	}
	m_controlsScreen = new BitmapClass;
	if(!m_controlsScreen)
	{
		return false;
	}

	// Initialize the bitmap objects.
	result = crosshairs->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../../data/crosshair.png", 60, 50);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the crosshairs object.", L"Error", MB_OK);
		return false;
	}
	result = HUD->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../../data/hud04.png", screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the HUD object.", L"Error", MB_OK);
		return false;
	}
	result = m_titleScreen->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../../data/titleScreen.png", screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_titleScreen object.", L"Error", MB_OK);
		return false;
	}
	result = m_controlsScreen->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../../data/controlScreen.png", screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_controlsScreen object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if(!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if(!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../../data/star.dds");
	if(!result)
	{
		return false;
	}


	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown										|
// |----------------------------------------------------------------------------|
void GraphicsClass::Shutdown()
{
	// Release the particle system object.
	if(m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if(m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the planets.
	if(m_sun)
	{
		m_sun->Shutdown();
		delete m_sun;
		m_sun = 0;
	}
	if(m_mercury)
	{
		m_mercury->Shutdown();
		delete m_mercury;
		m_mercury = 0;
	}
	if(m_venus)
	{
		m_venus->Shutdown();
		delete m_venus;
		m_venus = 0;
	}
	if(m_earth)
	{
		m_earth->Shutdown();
		delete m_earth;
		m_earth = 0;
	}
	if(m_mars)
	{
		m_mars->Shutdown();
		delete m_mars;
		m_mars = 0;
	}
	if(m_jupiter)
	{
		m_jupiter->Shutdown();
		delete m_jupiter;
		m_jupiter = 0;
	}
	if(m_saturn)
	{
		m_saturn->Shutdown();
		delete m_saturn;
		m_saturn = 0;
	}
	if(m_uranus)
	{
		m_uranus->Shutdown();
		delete m_uranus;
		m_uranus = 0;
	}
	if(m_neptune)
	{
		m_neptune->Shutdown();
		delete m_neptune;
		m_neptune = 0;
	}
	if(m_halley)
	{
		m_halley->Shutdown();
		delete m_halley;
		m_halley = 0;
	}
	if(m_luna)
	{
		m_luna->Shutdown();
		delete m_luna;
		m_luna = 0;
	}
	if(m_phobos)
	{
		m_phobos->Shutdown();
		delete m_phobos;
		m_phobos = 0;
	}
	if(m_deimos)
	{
		m_deimos->Shutdown();
		delete m_deimos;
		m_deimos = 0;
	}

	// Release skybox
	if(m_skybox)
	{
		m_skybox->Shutdown();
		delete m_skybox;
		m_skybox = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap objects.
	if(crosshairs)
	{
		crosshairs->Shutdown();
		delete crosshairs;
		crosshairs = 0;
	}
	if(HUD)
	{
		HUD->Shutdown();
		delete HUD;
		HUD = 0;
	}
	if(m_titleScreen)
	{
		m_titleScreen->Shutdown();
		delete m_titleScreen;
		m_titleScreen = 0;
	}
	if(m_controlsScreen)
	{
		m_controlsScreen->Shutdown();
		delete m_controlsScreen;
		m_controlsScreen = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the shader objects.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       Frame										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::Frame(int mouseX, int mouseY, int fps, int cpu, float frameTime,
	Coord camera_rotation, Coord camera_position, bool transfer)
{
	bool result;

	// Swap out bitmaps if needed
	if (transfer && m_screen_counter >= 1000)
	{
		m_screen_counter = 0;
		m_screen++;
	}
	m_screen_counter += frameTime;

	// Set the position of the camera.
	m_Camera->SetPosition(camera_position.x, camera_position.y, camera_position.z-300.0f);

	// Set the rotation of the camera.
	m_Camera->SetRotation(camera_rotation.x, camera_rotation.y, camera_rotation.z);

	// Update planets
	m_sun->Frame(frameTime);
	m_mercury->Frame(frameTime);
	m_venus->Frame(frameTime);
	m_earth->Frame(frameTime);
	m_mars->Frame(frameTime);
	m_jupiter->Frame(frameTime);
	m_saturn->Frame(frameTime);
	m_uranus->Frame(frameTime);
	m_neptune->Frame(frameTime);
	m_halley->Frame(frameTime);

	// Update moons
	D3DXMATRIX positionMatrix = m_earth->GetTranslate();
	m_luna->SetOrbitCenter(positionMatrix._41,positionMatrix._42,positionMatrix._43);
	m_luna->Frame(frameTime);
	positionMatrix = m_mars->GetTranslate();
	m_phobos->SetOrbitCenter(positionMatrix._41,positionMatrix._42,positionMatrix._43);
	m_phobos->Frame(frameTime);
	m_deimos->SetOrbitCenter(positionMatrix._41,positionMatrix._42,positionMatrix._43);
	m_deimos->Frame(frameTime);

	// Run the frame processing for the particle system.
	positionMatrix = m_halley->GetTranslate();
	m_ParticleSystem->SetPosition(positionMatrix._41,positionMatrix._42,positionMatrix._43);
	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext(), camera_position.x, camera_position.y, camera_position.z);
	
	// Render the graphics scene.
	result = Render(mouseX, mouseY, camera_position);
	if(!result)
	{
		return false;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}


	return true;
}


// |----------------------------------------------------------------------------|
// |						      Render										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::Render(int mouseX, int mouseY, Coord camera_position)
{
	bool result;
	static float rotation = 0.0f;

	result = BeginRender();

	// Turn off the Z buffer and culling for skybox
	m_D3D->TurnZBufferOff();
	m_D3D->TurnOffBackCulling();

	// Skybox rendering
	D3DXMATRIX ident, translationMatrix;
	D3DXMatrixIdentity(&ident);
	D3DXMatrixTranslation(&translationMatrix, camera_position.x, camera_position.y, camera_position.z-300);
	result = result && SunRender(*m_skybox, ident, translationMatrix, ident);

	// Turn the Z buffer and back culling on now that skybox is rendered.
	m_D3D->TurnZBufferOn();
	m_D3D->TurnOnBackCulling();

	// Render planets
	ModelClass* planet_model(0);

	m_sun->GetModel(planet_model);
	result = result && SunRender(*planet_model, m_sun->GetScale(), m_sun->GetTranslate(), 
		m_sun->GetRotate());
	
	m_mercury->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_mercury->GetScale(), m_mercury->GetTranslate(), 
		m_mercury->GetRotate());
	
	m_venus->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_venus->GetScale(), m_venus->GetTranslate(), 
		m_venus->GetRotate());
	
	m_earth->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_earth->GetScale(), m_earth->GetTranslate(), 
		m_earth->GetRotate());
	
	m_mars->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_mars->GetScale(), m_mars->GetTranslate(), 
		m_mars->GetRotate());
	
	m_jupiter->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_jupiter->GetScale(), m_jupiter->GetTranslate(), 
		m_jupiter->GetRotate());
	
	m_saturn->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_saturn->GetScale(), m_saturn->GetTranslate(), 
		m_saturn->GetRotate());
	
	m_uranus->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_uranus->GetScale(), m_uranus->GetTranslate(), 
		m_uranus->GetRotate());
	
	m_neptune->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_neptune->GetScale(), m_neptune->GetTranslate(), 
		m_neptune->GetRotate());
	
	m_halley->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_halley->GetScale(), m_halley->GetTranslate(), 
		m_halley->GetRotate());
	
	m_luna->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_luna->GetScale(), m_luna->GetTranslate(), 
		m_luna->GetRotate());
	
	m_phobos->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_phobos->GetScale(), m_phobos->GetTranslate(), 
		m_phobos->GetRotate());
	
	m_deimos->GetModel(planet_model);
	result = result && ModelRender(*planet_model, m_deimos->GetScale(), m_deimos->GetTranslate(), 
		m_deimos->GetRotate());

	// Turn on alpha blending.
	m_D3D->TurnOnAlphaBlending();

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the particles using the texture shader.
	D3DXMatrixIdentity(&worldMatrix);
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					  m_ParticleSystem->GetTexture());
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// BITMAP rendering
	result = result && BitmapRender(*crosshairs, mouseX-30, mouseY-25);
	result = result && BitmapRender(*HUD, 0, 0);

	// TEXT rendering
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// TITLE SCREEN rendering
	if (m_screen == 0) result = result && BitmapRender(*m_titleScreen, 0, 0);
	if (m_screen == 1) result = result && BitmapRender(*m_controlsScreen, 0, 0);

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Perform closing actions
	result = result && EndRender();

	return result;
}


// |----------------------------------------------------------------------------|
// |						    BeginRender										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::BeginRender()
{
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	return true;
}


// |----------------------------------------------------------------------------|
// |						    EndRender										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::EndRender()
{
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


// |----------------------------------------------------------------------------|
// |						    ModelRender										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::ModelRender(ModelClass& to_render, D3DXMATRIX scale, 
	D3DXMATRIX translate, D3DXMATRIX rotate)
{
	D3DXMATRIX scaleMatrix, translationMatrix, rotationMatrix;
	bool result = true;

	// Modify the world matrix as needed.
	D3DXMatrixIdentity(&worldMatrix);
	worldMatrix = scale * rotate * translate;
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	to_render.Render(m_D3D->GetDeviceContext());
	
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), to_render.GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								    m_Light->GetPosition(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), 
									m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), to_render.GetTexture());

	return result;
}


// |----------------------------------------------------------------------------|
// |						    SunRender										|
// |----------------------------------------------------------------------------|
bool GraphicsClass::SunRender(ModelClass& to_render, D3DXMATRIX scale, 
	D3DXMATRIX translate, D3DXMATRIX rotate)
{
	D3DXMATRIX scaleMatrix, translationMatrix, rotationMatrix;
	bool result = true;

	// Modify the world matrix as needed.
	D3DXMatrixIdentity(&worldMatrix);
	worldMatrix = scale * rotate * translate;
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	to_render.Render(m_D3D->GetDeviceContext());
	
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), to_render.GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								    m_Light->GetPosition(), D3DXVECTOR4(0.99f,0.99f,0.99f,1.0f), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), 
									m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), to_render.GetTexture());

	return result;
}



// |----------------------------------------------------------------------------|
// |						    BitmapRender									|
// |----------------------------------------------------------------------------|
bool GraphicsClass::BitmapRender(BitmapClass& to_render, int x, int y)
{
	bool result;

	// Change world matrix to identity before rendering.
	D3DXMatrixIdentity(&worldMatrix);
	
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = to_render.Render(m_D3D->GetDeviceContext(), x, y);
	if(!result)
	{
		return false;
	}
	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), to_render.GetIndexCount(), 
		worldMatrix, baseViewMatrix, orthoMatrix, to_render.GetTexture());
	if(!result)
	{
		return false;
	}

	return result;
}