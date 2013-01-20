// Solar Exploration Sim
// Developed for DirectX Coursework for Abertay University, based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2011, all rights reserved.
//
// PositionClass
//		Records and passes along camera position and angle


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "positionclass.h"
#include <d3dx10math.h>


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
PositionClass::PositionClass() :
	m_frameTime(0.0f),
	m_rotationX(0.0f),
	m_rotationY(0.0f),
	m_rotationZ(0.0f),
	m_positionX(0.0f),
	m_positionY(0.0f),
	m_positionZ(0.0f),
	m_leftTurnSpeed(0.0f),
	m_rightTurnSpeed(0.0f),
	m_leftRollSpeed(0.0f),
	m_rightRollSpeed(0.0f),
	m_upTurnSpeed(0.0f),
	m_downTurnSpeed(0.0f),
	m_forwardMoveSpeed(0.0f),
	m_backwardMoveSpeed(0.0f),
	m_leftMoveSpeed(0.0f),
	m_rightMoveSpeed(0.0f),
	m_upMoveSpeed(0.0f),
	m_downMoveSpeed(0.0f)

{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
PositionClass::PositionClass(const PositionClass& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
PositionClass::~PositionClass()
{
}


// |----------------------------------------------------------------------------|
// |						     SetFrameTime									|
// |----------------------------------------------------------------------------|
void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


// |----------------------------------------------------------------------------|
// |						     GetRotation									|
// |----------------------------------------------------------------------------|
void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


// |----------------------------------------------------------------------------|
// |						     GetPosition									|
// |----------------------------------------------------------------------------|
void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


// |----------------------------------------------------------------------------|
// |						       TurnLeft										|
// |----------------------------------------------------------------------------|
void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  
	// If not slow down the turn speed.
	if(keydown)
	{
		m_leftTurnSpeed += 1.0f / m_frameTime;

		if(m_leftTurnSpeed > (15.0f / m_frameTime))
		{
			m_leftTurnSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_leftTurnSpeed -= 1.0f / m_frameTime;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
	if(m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       TurnRight									|
// |----------------------------------------------------------------------------|
void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  
	//If not slow down the turn speed.
	if(keydown)
	{
		m_rightTurnSpeed += 1.0f / m_frameTime;

		if(m_rightTurnSpeed > (15.0f / m_frameTime))
		{
			m_rightTurnSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_rightTurnSpeed -= 1.0f / m_frameTime;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
	if(m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       TurnUp										|
// |----------------------------------------------------------------------------|
void PositionClass::TurnUp(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns.  
	// If not slow down the turn speed.
	if(keydown)
	{
		m_upTurnSpeed += 1.0f / m_frameTime;

		if(m_upTurnSpeed > (15.0f / m_frameTime))
		{
			m_upTurnSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_upTurnSpeed -= 1.0f / m_frameTime;

		if(m_upTurnSpeed < 0.0f)
		{
			m_upTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX -= m_upTurnSpeed;
	if(m_rotationX < 0.0f)
	{
		m_rotationX += 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       TurnDown										|
// |----------------------------------------------------------------------------|
void PositionClass::TurnDown(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns.  
	// If not slow down the turn speed.
	if(keydown)
	{
		m_downTurnSpeed += 1.0f / m_frameTime;

		if(m_downTurnSpeed > (15.0f / m_frameTime))
		{
			m_downTurnSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_downTurnSpeed -= 1.0f / m_frameTime;

		if(m_downTurnSpeed < 0.0f)
		{
			m_downTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX += m_downTurnSpeed;
	if(m_rotationX > 360.0f)
	{
		m_rotationX -= 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       RollLeft										|
// |----------------------------------------------------------------------------|
void PositionClass::RollLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  
	// If not slow down the turn speed.
	if(keydown)
	{
		m_leftRollSpeed += 1.0f / m_frameTime;

		if(m_leftRollSpeed > (15.0f / m_frameTime))
		{
			m_leftRollSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_leftRollSpeed -= 1.0f / m_frameTime;

		if(m_leftRollSpeed < 0.0f)
		{
			m_leftRollSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationZ += m_leftRollSpeed;
	if(m_rotationZ > 360.0f)
	{
		m_rotationZ -= 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						       RollRight									|
// |----------------------------------------------------------------------------|
void PositionClass::RollRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  
	//If not slow down the turn speed.
	if(keydown)
	{
		m_rightRollSpeed += 1.0f / m_frameTime;

		if(m_rightRollSpeed > (15.0f / m_frameTime))
		{
			m_rightRollSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_rightRollSpeed -= 1.0f / m_frameTime;

		if(m_rightRollSpeed < 0.0f)
		{
			m_rightRollSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationZ -= m_rightRollSpeed;
	if(m_rotationZ < 0.0f)
	{
		m_rotationZ += 360.0f;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						     MoveForward									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveForward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_forwardMoveSpeed += 1.0f / m_frameTime;

		if(m_forwardMoveSpeed > (15.0f / m_frameTime))
		{
			m_forwardMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_forwardMoveSpeed -= 1.0f / m_frameTime;

		if(m_forwardMoveSpeed < 0.0f)
		{
			m_forwardMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, 0, 0, m_forwardMoveSpeed);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * 0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}


// |----------------------------------------------------------------------------|
// |						     MoveBackward									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveBackward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_backwardMoveSpeed += 1.0f / m_frameTime;

		if(m_backwardMoveSpeed > (15.0f / m_frameTime))
		{
			m_backwardMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_backwardMoveSpeed -= 1.0f / m_frameTime;

		if(m_backwardMoveSpeed < 0.0f)
		{
			m_backwardMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, 0, 0, -1*m_backwardMoveSpeed);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * 0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}


// |----------------------------------------------------------------------------|
// |						        MoveLeft									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_leftMoveSpeed += 1.0f / m_frameTime;

		if(m_leftMoveSpeed > (15.0f / m_frameTime))
		{
			m_leftMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_leftMoveSpeed -= 1.0f / m_frameTime;

		if(m_leftMoveSpeed < 0.0f)
		{
			m_leftMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, 0, -1*m_leftMoveSpeed, 0);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * -0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}


// |----------------------------------------------------------------------------|
// |						       MoveRight									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_rightMoveSpeed += 1.0f / m_frameTime;

		if(m_rightMoveSpeed > (15.0f / m_frameTime))
		{
			m_rightMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_rightMoveSpeed -= 1.0f / m_frameTime;

		if(m_rightMoveSpeed < 0.0f)
		{
			m_rightMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, 0, 1*m_rightMoveSpeed, 0);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * -0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}


// |----------------------------------------------------------------------------|
// |						          MoveUp									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveUp(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_upMoveSpeed += 1.0f / m_frameTime;

		if(m_upMoveSpeed > (15.0f / m_frameTime))
		{
			m_upMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_upMoveSpeed -= 1.0f / m_frameTime;

		if(m_upMoveSpeed < 0.0f)
		{
			m_upMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, m_upMoveSpeed, 0, 0);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * -0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}


// |----------------------------------------------------------------------------|
// |						        MoveDown									|
// |----------------------------------------------------------------------------|
void PositionClass::MoveDown(bool keydown)
{
	// If the key is pressed increase the speed at which the camera moves.  
	// If not slow down the move speed.
	if(keydown)
	{
		m_downMoveSpeed += 1.0f / m_frameTime;

		if(m_downMoveSpeed > (15.0f / m_frameTime))
		{
			m_downMoveSpeed = 15.0f / m_frameTime;
		}
	}
	else
	{
		m_downMoveSpeed -= 1.0f / m_frameTime;

		if(m_downMoveSpeed < 0.0f)
		{
			m_downMoveSpeed = 0.0f;
		}
	}

	// Modify speed based on rotation.
	D3DXMATRIX worldMatrix, moveMatrix, rotationMatrix;
	D3DXMatrixTranslation(&moveMatrix, -1*m_downMoveSpeed, 0, 0);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotationX * -0.0174532925f, 
		m_rotationY * -0.0174532925f, 
		m_rotationZ * -0.0174532925f);
	worldMatrix = moveMatrix * rotationMatrix;

	// Update the position.
	m_positionY += worldMatrix._41;
	m_positionX += worldMatrix._42;
	m_positionZ += worldMatrix._43;

	return;
}