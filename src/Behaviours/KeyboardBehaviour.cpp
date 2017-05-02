#include "KeyboardBehaviour.h"
#include "Agent.h"
#include "Application2D.h"
#include <GLFW\glfw3.h>



KeyboardBehaviour::KeyboardBehaviour()
{
	m_eBehaviourName = BH_KEYBOARD;
}


KeyboardBehaviour::~KeyboardBehaviour()
{
}

Status KeyboardBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		if (agent->pathList()->empty())
		{
			return BH_SUCCESS;
		}
		else
		{
			return BH_SUCCESS;
		}
	}
	else
	{
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void KeyboardBehaviour::Update(float deltaTime, MovementInfo & movementInfo)
{
	// W and S keys = force plus acceleration
	if (Application2D::getInstance()->keyPressed(GLFW_KEY_UP))
	{
		movementInfo.m_acceleration.y -= movementInfo.m_maxSpeed * deltaTime;
	}
	if (Application2D::getInstance()->keyPressed(GLFW_KEY_DOWN))
	{
		movementInfo.m_acceleration.y += movementInfo.m_maxSpeed * deltaTime;
	}
	// reduce speed if not pressed
	if (!(Application2D::getInstance()->keyPressed(GLFW_KEY_UP)) && !(Application2D::getInstance()->keyPressed(GLFW_KEY_DOWN)))
	{
		movementInfo.m_velocity.y -= movementInfo.m_velocity.y * deltaTime;
	}

	// A and D keys = force plus acceleration
	if (Application2D::getInstance()->keyPressed(GLFW_KEY_LEFT))
	{
		movementInfo.m_acceleration.x += movementInfo.m_maxSpeed * deltaTime;
	}
	if (Application2D::getInstance()->keyPressed(GLFW_KEY_RIGHT))
	{
		movementInfo.m_acceleration.x -= movementInfo.m_maxSpeed * deltaTime;
	}
	// reduce speed if not pressed
	if (!(Application2D::getInstance()->keyPressed(GLFW_KEY_LEFT)) && !(Application2D::getInstance()->keyPressed(GLFW_KEY_RIGHT)))
	{
		movementInfo.m_velocity.x -= movementInfo.m_velocity.x * deltaTime;
	}
}