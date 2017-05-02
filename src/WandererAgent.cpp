#include "WandererAgent.h"
#include "IBehaviour.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include <cmath>
#include <glm\glm.hpp>
// dependencies includes
#include <GLFW/glfw3.h>
#include "WandererBT.h"
#include "GameDef.h"

#define M_PI       3.14159265358979323846

WandererAgent::WandererAgent()
{
	Init(glm::vec2(0.0f, 0.0f), 10.0f);
}

WandererAgent::WandererAgent(float positionX, float positionY, float size)
{
	m_movementInfo.m_position.x = positionX;
	m_movementInfo.m_position.y = positionY;
	Init(m_movementInfo.m_position, size);
}

WandererAgent::WandererAgent(glm::vec2 position, float size)
{
	Init(position, size);
}

WandererAgent::~WandererAgent()
{
}

void WandererAgent::Update(float deltaTime)
{
	// check agent isn't off screen
	offScreen();

	// execute behaviour tree
	m_spWandererBT.get()->execute(this);

	if (m_currentBehaviour != nullptr)
	{
		texture();
		m_currentBehaviour->Update(deltaTime, m_movementInfo);
	}


	// update velocity vector
	m_movementInfo.m_velocity += m_movementInfo.m_acceleration * deltaTime;

	glm::vec2 vel = m_movementInfo.m_velocity;

	// check if the magnitude of the velocity is greater than max speed
	if (glm::length(vel) > m_movementInfo.m_maxSpeed)
	{
		// update members old vars 
		vel = glm::normalize(vel) * m_movementInfo.m_maxSpeed;

		// update new vector style member vars
		m_movementInfo.m_velocity = glm::normalize(vel) * m_movementInfo.m_maxSpeed;

	}

	// set rotation
	m_movementInfo.m_rotation = (float)atan2(m_movementInfo.m_velocity.x, m_movementInfo.m_velocity.y) * M_PI / 2;

	// reset acceleration vector
	m_movementInfo.m_acceleration.x = 0.0f;
	m_movementInfo.m_acceleration.y = 0.0f;

	// increase postition vector by velocity vector
	m_movementInfo.m_position += m_movementInfo.m_velocity;

}

void WandererAgent::Draw(SpriteBatch * spriteBatch)
{
	if (m_movementInfo.m_spriteBatch != nullptr)
	{
		m_currentBehaviour->Draw(&m_movementInfo);
	}
}

float WandererAgent::size()
{
	return m_size;
}

float WandererAgent::size(float newSize)
{
	m_size = newSize;
	return m_size;
}

int WandererAgent::state()
{
	return m_state;
}

int WandererAgent::state(int newState)
{
	m_state = newState;
	return m_state;
}

SpriteBatch * WandererAgent::spriteBatch()
{
	return m_movementInfo.m_spriteBatch;
}

SpriteBatch * WandererAgent::spriteBatch(SpriteBatch * spriteBatch)
{
	m_movementInfo.m_spriteBatch = spriteBatch;
	return m_movementInfo.m_spriteBatch;
}

Texture * WandererAgent::texture()
{
	if (m_currentBehaviour != nullptr)
	{
		if (m_currentBehaviour->behaviourType() == BH_AVOID)
		{
			m_texture = m_fleeTexture.get();
		}
		if (m_currentBehaviour->behaviourType() == BH_FLEE)
		{
			m_texture = m_fleeTexture.get();
		}
		if (m_currentBehaviour->behaviourType() == BH_SEEK)
		{
			m_texture = m_seekTexture.get();
		}
		if (m_currentBehaviour->behaviourType() == BH_FOLLOW)
		{
			m_texture = m_seekTexture.get();
		}
		if (m_currentBehaviour->behaviourType() == BH_WANDER)
		{
			m_texture = m_wanderTexture.get();
		}
	}
	else
	{
		m_texture = m_wanderTexture.get();
	}


	return m_texture;
}

Texture * WandererAgent::texture(Texture * texture)
{
	m_texture = texture;

	return m_texture;
}

void WandererAgent::Init(glm::vec2 position, float size)
{
	m_movementInfo.m_position = position;	
	m_movementInfo.m_velocity.x = 0.0f;
	m_movementInfo.m_velocity.y = 0.0f;
	m_movementInfo.m_acceleration.x = 0.0f;
	m_movementInfo.m_acceleration.y = 0.0f;
	m_movementInfo.m_maxSpeed = 50.0f;
	m_movementInfo.m_maxForce = 0.1f;
	m_movementInfo.m_rotation = 0.0f;
	m_movementInfo.m_rotationDampening = 0.05f;
	m_movementInfo.m_spriteBatch = nullptr;

	// sensor setup
	m_movementInfo.m_sight = 20.0f;
	m_movementInfo.m_sensor += (position + m_movementInfo.m_sight);

	m_texture = m_wanderTexture.get();
	m_spCurrentBehaviour = nullptr;
	m_currentBehaviour = nullptr;
	m_spClosestObstacle = nullptr;
	m_size = size;
	m_state = 0;

	m_seekTexture = std::make_shared<Texture>("./bin/textures/seeker.png");
	m_fleeTexture = std::make_shared<Texture>("./bin/textures/flee.png");
	m_wanderTexture = std::make_shared<Texture>("./bin/textures/wander.png");

}


