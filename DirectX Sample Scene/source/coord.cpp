// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// Coord
//		Simple struct-like class containing an x, y, and z float coordinate


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Coord.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Coord::Coord() :
	x(0), y(0), z(0)
{
}

	
// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Coord::Coord(const Coord& other)
	: x(other.x), y(other.y), z(other.z)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Coord::~Coord()
{
}


// |----------------------------------------------------------------------------|
// |							Other Constructors								|
// |----------------------------------------------------------------------------|
Coord::Coord(float new_x, float new_y, float new_z) :
	x(new_x), y(new_y), z(new_z)
{
}
	

// |----------------------------------------------------------------------------|
// |							  Operator =									|
// |----------------------------------------------------------------------------|
Coord Coord::operator= (const Coord& other)
{
	return Coord(other);
}
Coord Coord::operator= (const float uniform_value)
{
	return Coord(uniform_value, uniform_value, uniform_value);
}