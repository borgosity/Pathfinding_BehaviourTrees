#include "PursueBehaviour.h"
#include <glm\glm.hpp>
#include "Agent.h"
#include "PlayerAgent.h"
#include "Application2D.h"

PursueBehaviour::PursueBehaviour()
{
	m_spTarget = nullptr;
	m_eBehaviourName = BH_PURSUE;
}

PursueBehaviour::PursueBehaviour(spAgent target) : m_spTarget(target)
{
	m_fWeight = 0;
	m_eBehaviourName = BH_PURSUE;
}

PursueBehaviour::PursueBehaviour(spAgent target, float weight)
{
	m_spTarget = target;
	m_fWeight = weight;
	m_eBehaviourName = BH_PURSUE;
}

PursueBehaviour::~PursueBehaviour()
{
}

Status PursueBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		this->m_spTarget = Application2D::getInstance()->getPlayer();
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void PursueBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{

	// subtract agent postion from target position + targets velocity 
	glm::vec2 direction = (m_spTarget->m_movementInfo.m_position + m_spTarget->m_movementInfo.m_velocity) - behaviour.m_position;


	// scale resultant vector by maxSpeed
	// calculate the acceleration required to move agent away to targets estimated location
	glm::vec2 acceleration = (glm::normalize(direction) * behaviour.m_maxSpeed) - behaviour.m_velocity;

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
