#include "EvadeBehaviour.h"
#include "IBehaviourTree.h"
#include <glm\glm.hpp>
#include "Agent.h"


EvadeBehaviour::EvadeBehaviour()
{
	m_fWeight = 0;
	m_eBehaviourName = BH_EVADE;
}

EvadeBehaviour::EvadeBehaviour(spAgent target) : m_spTarget(target)
{
	m_fWeight = 0;
	m_eBehaviourName = BH_EVADE;
}

EvadeBehaviour::EvadeBehaviour(spAgent target, float weight)
{
	m_spTarget = target;
	m_fWeight = weight;
	m_eBehaviourName = BH_EVADE;
}

EvadeBehaviour::~EvadeBehaviour()
{
}

Status EvadeBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		if (m_spTarget == nullptr)
		{
			m_spTarget = agent->closetAgent();
			agent->SetBehaviour(this);
			return BH_SUCCESS;
		}
		else
		{
			agent->SetBehaviour(this);
			return BH_SUCCESS;
		}
	}
}

void EvadeBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{

	// subtract target position + targets velocity from agent postion
	glm::vec2 direction = behaviour.m_position - (m_spTarget->m_movementInfo.m_position + m_spTarget->m_movementInfo.m_velocity);

	// scale resultant vector by maxSpeed
	// calculate the acceleration required to move agent away to targets estimated location
	glm::vec2 acceleration = (glm::normalize(direction)	* behaviour.m_maxSpeed) - behaviour.m_velocity;

	// limit acceleration
	if (glm::length(acceleration) > behaviour.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
		behaviour.m_acceleration = acceleration;
	}

	if (m_fWeight > 0)
	{
		// Apply accleration to agent
		behaviour.m_velocity += (acceleration * m_fWeight) * deltaTime;
	}
	else
	{
		// Apply accleration to agent
		behaviour.m_velocity += acceleration * deltaTime;
	}
	behaviour.m_position += behaviour.m_velocity * deltaTime;

}
