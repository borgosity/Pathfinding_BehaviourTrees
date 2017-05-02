#include "PlayerAgent.h"
#include "IBehaviour.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include <cmath>
// dependencies includes
#include <GLFW/glfw3.h>
#include "PlayerBT.h"
#include "GameDef.h"

#define M_PI       3.14159265358979323846

PlayerAgent::PlayerAgent()
{
	Init(glm::vec2(0.0f, 0.0f), 10.0f);
}

PlayerAgent::PlayerAgent(glm::vec2 position, float size)
{
	Init(position, size);
}

PlayerAgent::~PlayerAgent()
{
}

void PlayerAgent::Update(float deltaTime)
{
	// check agent isn't off screen
	offScreen();

	// execute behaviour tree
	Status result = m_spPlayerBT.get()->execute(this);

	// set players texture and run behaviour
	if (m_currentBehaviour != nullptr && result == BH_SUCCESS)
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

void PlayerAgent::Draw(SpriteBatch * spriteBatch)
{
	if (m_movementInfo.m_spriteBatch != nullptr)
	{
		m_currentBehaviour->Draw(&m_movementInfo);
	}
}

float PlayerAgent::size()
{
	return m_size;
}

float PlayerAgent::size(float newSize)
{
	m_size = newSize;
	return m_size;
}

int PlayerAgent::state()
{
	return m_state;
}

int PlayerAgent::state(int newState)
{
	m_state = newState;
	return m_state;
}

SpriteBatch * PlayerAgent::spriteBatch()
{
	return m_movementInfo.m_spriteBatch;
}

SpriteBatch * PlayerAgent::spriteBatch(SpriteBatch * spriteBatch)
{
	m_movementInfo.m_spriteBatch = spriteBatch;
	return m_movementInfo.m_spriteBatch;
}

Texture * PlayerAgent::texture()
{	
	if (m_currentBehaviour->behaviourType() == BH_WAITING)
	{
		m_texture = m_waitTexture.get();
	}
	if (m_currentBehaviour->behaviourType() == BH_PATH)
	{
		m_texture = m_pathTexture.get();
	}
	if (m_currentBehaviour->behaviourType() == BH_EVADE)
	{
		m_texture = m_evadeTexture.get();
	}
	return m_texture;
}

Texture * PlayerAgent::texture(Texture * texture)
{
	m_texture = texture;

	return m_texture;
}

void PlayerAgent::Init(glm::vec2 position, float size)
{
	// movement information
	m_movementInfo.m_position = position;	
	m_movementInfo.m_velocity.x = 0.0f;
	m_movementInfo.m_velocity.y = 0.0f;
	m_movementInfo.m_acceleration.x = 0.0f;
	m_movementInfo.m_acceleration.y = 0.0f;
	m_movementInfo.m_maxSpeed = PLAYER_MAX_SPEED;
	m_movementInfo.m_maxForce = PLAYER_MAX_FORCE;
	m_movementInfo.m_maxAcceleration = PLAYER_MAX_ACCEL;
	m_movementInfo.m_rotation = 0.0f;
	m_movementInfo.m_rotationDampening = 0.05f;
	m_movementInfo.m_spriteBatch = nullptr;

	// sensor setup
	m_movementInfo.m_sight = 20.0f;
	m_movementInfo.m_sensor += (position + m_movementInfo.m_sight);

	// textures
	m_pathTexture = std::make_shared<Texture>("./bin/textures/pathFind.png");
	m_waitTexture = std::make_shared<Texture>("./bin/textures/agent.png");
	m_evadeTexture = std::make_shared<Texture>("./bin/textures/evade.png");

	// others
	m_currentBehaviour = nullptr;
	m_size = size;
	m_state = 0;

	// path related
	m_startPoint = nullptr;
	m_endPoint = nullptr;
	m_pathList = {};
}
