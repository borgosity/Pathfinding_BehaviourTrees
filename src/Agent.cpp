#include "Agent.h"
#include "IBehaviour.h"
#include "IBehaviourTree.h"
#include "SpriteBatch.h"
#include <cmath>
#include <glm\glm.hpp>
// dependencies includes
#include <GLFW/glfw3.h>
#include "GameDef.h"


#define M_PI       3.14159265358979323846

Agent::~Agent()
{
}

float Agent::size()
{
	return m_size;
}

float Agent::size(float newSize)
{
	m_size = newSize;
	return m_size;
}

int Agent::state()
{
	return m_state;
}

int Agent::state(int newState)
{
	m_state = newState;
	return m_state;
}

SpriteBatch * Agent::spriteBatch()
{
	return m_movementInfo.m_spriteBatch;
}

SpriteBatch * Agent::spriteBatch(SpriteBatch * spriteBatch)
{
	m_movementInfo.m_spriteBatch = spriteBatch;
	return m_movementInfo.m_spriteBatch;
}

Texture * Agent::texture()
{
	return m_texture;
}

Texture * Agent::texture(Texture * texture)
{
	m_texture = texture;

	return m_texture;
}

Graph::Node * Agent::startPoint()
{
	return m_startPoint;
}

Graph::Node * Agent::startPoint(Graph::Node * startPoint)
{
	m_startPoint = startPoint;
	return m_startPoint;
}

Graph::Node * Agent::endPoint()
{
	return m_endPoint;
}

Graph::Node * Agent::endPoint(Graph::Node * endPoint)
{
	m_endPoint = endPoint;
	return m_endPoint;
}

std::list<Graph::Node*> * Agent::pathList()
{
	return &m_pathList;
}

std::list<Graph::Node*> * Agent::pathList(std::list<Graph::Node*> pathList)
{
	m_pathList = pathList;
	return &m_pathList;
}

spObstacle Agent::closetObstacle()
{
	return m_spClosestObstacle;
}

spObstacle Agent::closetObstacle(spObstacle closestObstacle)
{
	m_spClosestObstacle = closestObstacle;
	return m_spClosestObstacle;
}

spAgent Agent::closetAgent()
{
	return m_spClosetAgent;
}

spAgent Agent::closetAgent(spAgent closestAgent)
{
	m_spClosetAgent = closestAgent;
	return m_spClosetAgent;
}

void Agent::offScreen()
{
	// gone off east side of screen
	if (m_movementInfo.m_position.x > (SCREEN_W + m_size))
	{
		m_movementInfo.m_position.x = (0.0f + m_size);
	}
	// gone off west side of screen
	if (m_movementInfo.m_position.x < (0.0f - m_size))
	{
		m_movementInfo.m_position.x = (SCREEN_W - m_size);
	}
	// gone off north side of screen
	if (m_movementInfo.m_position.y >(SCREEN_H + m_size))
	{
		m_movementInfo.m_position.y = (0.0f + m_size);
	}
	// gone off south side of screen
	if (m_movementInfo.m_position.y < (0.0f - m_size))
	{
		m_movementInfo.m_position.y = (SCREEN_H - m_size);
	}
}
