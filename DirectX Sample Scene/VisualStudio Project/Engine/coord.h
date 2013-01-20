// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// Coord
//		Simple struct-like class containing an x, y, and z float coordinate
#pragma once


// |----------------------------------------------------------------------------|
// |							 Class: Coord									|
// |----------------------------------------------------------------------------|
class Coord
{
public:
	//|-------------------------------Public Functions--------------------------|

	// Constrcutors and Deconstructors
	Coord();
	Coord(const Coord&);
	~Coord();
	
	// Argument Constructors and Operator Overloading
	Coord(const float new_x, const float new_y, const float new_z);
	Coord operator= (const Coord& other);
	Coord operator= (const float uniform_value);
	
	//|-----------------------------Public Data Members-------------------------|

	// floats holding coordinate values
	float x, y, z;
};