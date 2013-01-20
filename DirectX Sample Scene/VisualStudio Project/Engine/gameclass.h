// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// GameClass
//		Controls overall game logic and holds objects within the game
#pragma once


// |----------------------------------------------------------------------------|
// |						   Class: GameClass									|
// |----------------------------------------------------------------------------|
class GameClass
{
public:
	//|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	GameClass();
	GameClass(const GameClass&);
	~GameClass();
	
	// Initializes the game, setting up child objects
	bool Initialize();

	// Performs shutdown, deallocation, and cleanup for game objects
	void Shutdown();

	// Processes game logic for each frame
	bool Frame();

private:
	//|-----------------------------Private Data Members------------------------|


};