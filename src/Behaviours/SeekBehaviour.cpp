#include "SeekBehaviour.h"
#include <glm\glm.hpp>
#include "Agent.h"
#include "PlayerAgent.h"
#include "Application2D.h"

SeekBehaviour::SeekBehaviour()
{
	m_pTarget = nullptr;
	m_spTarget = nullptr;
	m_eBehaviourName = BH_SEEK;
}

SeekBehaviour::SeekBehaviour(Agent * target) : m_pTarget(target)
{
	m_spTarget = nullptr; // set smart pointer to null as it's not in use
	m_eBehaviourName = BH_SEEK;
}

SeekBehaviour::SeekBehaviour(std::shared_ptr<Agent> target) : m_spTarget(target)
{
	m_pTarget = nullptr; // set pointer to null as it's not in use
	m_eBehaviourName = BH_SEEK;
}

SeekBehaviour::~SeekBehaviour()
{
}

Status SeekBehaviour::execute(Agent * agent)
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

void SeekBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{
	if (m_pTarget != nullptr)
	{
		//// vector from agent to target
		//glm::vec2 distance = glm::normalize(m_pTarget->m_movementInfo.m_position - behaviour.m_position);
		//// scale vector by maxSpeed
		//distance = distance * behaviour.m_maxSpeed;
		//// calculate the acceleration required to move agent to target (distance minus current velocity)
		//glm::vec2 acceleration = distance - behaviour.m_velocity;

		// the above compacted
		glm::vec2 acceleration = (glm::normalize(m_pTarget->m_movementInfo.m_position - behaviour.m_position) * behaviour.m_maxSpeed) - behaviour.m_velocity;

		if (glm::length(acceleration) > behaviour.m_maxAcceleration)
		{
			acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
			behaviour.m_acceleration = acceleration;
		}

		// Apply accleration to agent
		behaviour.m_velocity += acceleration * deltaTime;
		behaviour.m_position += behaviour.m_velocity * deltaTime;

	}
	else if (m_spTarget != nullptr)
	{
		//// vector from agent to target
		//glm::vec2 distance = glm::normalize(m_pTarget->m_movementInfo.m_position - behaviour.m_position);
		//// scale vector by maxSpeed
		//distance = distance * behaviour.m_maxSpeed;
		//// calculate the acceleration required to move agent to target (distance minus current velocity)
		//glm::vec2 acceleration = distance - behaviour.m_velocity;

		// the above compacted
		glm::vec2 acceleration = (glm::normalize(m_spTarget->m_movementInfo.m_position - behaviour.m_position) * behaviour.m_maxSpeed) - behaviour.m_velocity;

		if (glm::length(acceleration) > behaviour.m_maxAcceleration)
		{
			acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
			behaviour.m_acceleration = acceleration;
		}

		// Apply accleration to agent
		behaviour.m_velocity += acceleration * deltaTime;
		behaviour.m_position += behaviour.m_velocity * deltaTime;
	}




}
