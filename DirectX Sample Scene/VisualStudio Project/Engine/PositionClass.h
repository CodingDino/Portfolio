// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// PositionClass
//		Records and passes along camera position and angle
#pragma once


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <math.h>


// |----------------------------------------------------------------------------|
// |					       Class: PositionClass								|
// |----------------------------------------------------------------------------|
class PositionClass
{
public:

	//|-------------------------------Public Functions--------------------------|
	
	// Constructors and Destructors
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	// Setters
	void SetFrameTime(float);

	// Getters
	void GetRotation(float&, float&, float&);
	void GetPosition(float&, float&, float&);

	// Set rotation
	void TurnLeft(bool);
	void TurnRight(bool);
	void TurnUp(bool);
	void TurnDown(bool);
	void RollLeft(bool);
	void RollRight(bool);

	// Set movement
	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveLeft(bool);
	void MoveRight(bool);
	void MoveUp(bool);
	void MoveDown(bool);

private:

	//|-----------------------------Private Data Members------------------------|

	float m_frameTime;
	
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	float m_positionX;
	float m_positionY;
	float m_positionZ;

	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_leftRollSpeed, m_rightRollSpeed;
	float m_upTurnSpeed, m_downTurnSpeed;

	float m_forwardMoveSpeed, m_backwardMoveSpeed;
	float m_leftMoveSpeed, m_rightMoveSpeed;
	float m_upMoveSpeed, m_downMoveSpeed;
};