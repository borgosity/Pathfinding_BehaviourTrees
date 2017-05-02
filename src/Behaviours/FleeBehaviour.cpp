#include "FleeBehaviour.h"
#include <glm\glm.hpp>
#include "Agent.h"

FleeBehaviour::FleeBehaviour(std::shared_ptr<Agent> target) : m_spTarget(target)
{
	m_eBehaviourName = BH_FLEE;
}

FleeBehaviour::~FleeBehaviour()
{
}

Status FleeBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void FleeBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{
	// subtract target position from agent postion
	// scale resultant vector by maxSpeed
	// calculate the acceleration required to move agent to target (distance(first two steps) minus current velocity)
	glm::vec2 acceleration = (glm::normalize(behaviour.m_position - m_spTarget->m_movementInfo.m_position)
								* behaviour.m_maxSpeed) 
								- behaviour.m_velocity;

	// limit acceleration
	if (glm::length(acceleration) > behaviour.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
		behaviour.m_acceleration = acceleration;
	}

	// Apply accleration to agent
	behaviour.m_velocity += acceleration * deltaTime;
	behaviour.m_position += behaviour.m_velocity * deltaTime;
}
