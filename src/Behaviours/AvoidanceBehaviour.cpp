#include "AvoidanceBehaviour.h"
#include <glm\glm.hpp>
#include "Agent.h"
#include "Obstacle.h"


AvoidanceBehaviour::AvoidanceBehaviour()
{
	m_spTarget = nullptr;
	m_fWeight = 0;
	m_eBehaviourName = BH_AVOID;
}

AvoidanceBehaviour::AvoidanceBehaviour(spObstacle target) : m_spTarget(target)
{
	m_fWeight = 0;
	m_eBehaviourName = BH_AVOID;
}

AvoidanceBehaviour::AvoidanceBehaviour(spObstacle target, float weight)
{
	m_spTarget = target;
	m_fWeight = weight;
	m_eBehaviourName = BH_AVOID;
}

AvoidanceBehaviour::~AvoidanceBehaviour()
{
}

Status AvoidanceBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		this->m_spTarget = agent->closetObstacle();
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void AvoidanceBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{

	// subtract target position + targets velocity from agent postion
	glm::vec2 direction = behaviour.m_position - (m_spTarget->m_configurationInfo.m_vPosition + m_spTarget->m_configurationInfo.m_fRadius);

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
