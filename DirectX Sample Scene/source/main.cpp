// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// Main
//		Program wrapper.


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "systemclass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	
	
	// Create the system object.
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if(result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}

/*
Journal of DirectX

04-12-2012
Got model movement and transformations working, on multiple models (hard coded)
Interesting mistake in order of transforms caused an orbiting sphere, pretty neat
Learned more about how pitch/yaw/roll works, will be using that function for rotations
Won't be using "rotate about an axis" function, that will have to be done in the game object itself to determine it's rotation
Decided game objects will have a pointer to the model, and will draw from that. Model contains all DX references so all game object knows is that it passes it's model to the renderer with it's parameters and it gets drawn - nothing about DX API.
Wrote a render function accepting a model, scale, translation, and rotation
Wrote a coordinate class (basically a struct) with x, y, z floats (public) for use with render function and elsewhere in the program
Added a dynamic array of models - got stuck on array initialization though. When attempting to Initiallize a model in the array, program completely locks up and can't be force exited.
Wrote debug function, debugged issue - hadn't actually created model objects (oops)
Fixed issue, dynamic array implemented!

05-12-2012
Noticed that in my line of spheres, the lighting direction seems to change on each model slightly, from upper left to directly above. Going to need to investigate this.
I should note that several days ago I changed this to DX10 so it's compatible with my laptop.
Made file names uniform in style
Made comments uniform in style
Added commented explanations for each class, function, and data member
Removed references to "deltavalue" and "variablebuffer" as they aren't used in the program now.

TODO
	- DONE! Write debug function
	- DONE! Debug problem with dynamic array model initialization
	- DONE! Make file names, commenting, headers, etc more uniform
	- DONE!Remove references to deltavalue, variablebuffer - check rastertek tutorials
	- Investigate lighting change over different models or positions
	- Game objects with pointers to models, draw themselves
	- Input
	- Camera movement
	- point light source (sun)
	- set up planets rotating sun, moons rotating planets
	- get better textures for the sun and planets
	- add some kind of UI displaying useful info (coordinates, maybe fps, stuff like that)
	- add collision so player can't fly through planets - if player gets too close, notification of danger due to atmosphere, and turns back (or explodes?)
	- add sky box background
	- add animated space station
	- add fire effects around sun
	- add comet with ice trail particle effects
	- add nebula with particle effects / transparency
	- add asteroid field
	- add spaceship HUD overlay
	- add ability to switch between first and third person (see flying spaceship)
	- add music/sound
	- add lense flare from sun
	- add bloom from sun
*/