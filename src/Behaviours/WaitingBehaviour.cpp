#include "WaitingBehaviour.h"
#include "Agent.h"
#include "Application2D.h"
#include <GLFW\glfw3.h>
#include <algorithm>
#include "GameDef.h"



WaitingBehaviour::WaitingBehaviour()
{
	m_eBehaviourName = BH_WAITING;
	m_vTargetPos = glm::vec2(PLAYER_START_X, PLAYER_START_Y);
	m_fDistance = PLAYER_SLOW_DIS;
	m_fWeight = 0;
}


WaitingBehaviour::~WaitingBehaviour()
{
}

Status WaitingBehaviour::execute(Agent * agent)
{
	float velocity = glm::distance(agent->m_movementInfo.m_velocity, glm::vec2(0.0f, 0.0f));
	float targetDis = glm::distance(agent->m_movementInfo.m_position, m_vTargetPos);
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		if (velocity > 0.05)
		{
			arrivalTarget(agent->m_movementInfo);
		}
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void WaitingBehaviour::Update(float deltaTime, MovementInfo & agentMI)
{
	float velocity = glm::distance(agentMI.m_velocity, glm::vec2(0.0f, 0.0f));
	if (velocity > 0.05)
	{
		// subtract agent postion from target position + targets velocity 
		glm::vec2 direction = glm::normalize(m_vTargetPos - agentMI.m_position);
		float distance = glm::distance(agentMI.m_position, m_vTargetPos);


		// scale resultant vector by maxSpeed
		// calculate the acceleration required to move agent away to targets estimated location
		glm::vec2 acceleration = glm::normalize(direction) * agentMI.m_maxSpeed;

		// distance scalar
		float scalar = std::min(distance / m_fDistance, 1.0f);

		// if within radius
		if (scalar < 1)
		{
			acceleration *= scalar;

			float d = glm::dot(direction, glm::normalize(agentMI.m_velocity));

			glm::vec2 resistance = -(glm::normalize(agentMI.m_velocity)) * glm::length(agentMI.m_velocity) * d * 2.0f;

			acceleration += resistance;

			agentMI.m_acceleration = acceleration;
		}
		acceleration -= agentMI.m_velocity;

		if (m_fWeight > 0)
		{
			// Apply accleration to agent
			agentMI.m_velocity += (acceleration * m_fWeight) * deltaTime;
		}
		else
		{
			// Apply accleration to agent
			agentMI.m_velocity += acceleration * deltaTime;
		}

		agentMI.m_position += agentMI.m_velocity * deltaTime;
	}
}

void WaitingBehaviour::arrivalTarget(MovementInfo & agentMI)
{
	// specify the location of the circle centre based on the agents current velocity
	// then normalise it and move(scale) it to the specified distance infront of the agent
	m_vTargetPos.x = agentMI.m_position.x;
	m_vTargetPos.y = agentMI.m_position.y;
	m_vTargetPos = glm::normalize(m_vTargetPos);

	// ** NEED TO GET THE DIRECTION THAT THE AGENT IS FACING **
	m_vTargetPos.x = m_fDistance*cos(agentMI.m_rotation) + agentMI.m_position.x;
	m_vTargetPos.y = m_fDistance*sin(agentMI.m_rotation) + agentMI.m_position.y;
	m_vTargetPos += m_fDistance; // moves circle ot in front of agent
}
