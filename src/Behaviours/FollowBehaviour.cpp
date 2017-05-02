#include "FollowBehaviour.h"
#include <glm\glm.hpp>
#include "Agent.h"
#include "PlayerAgent.h"
#include "Application2D.h"


FollowBehaviour::FollowBehaviour()
{
	m_pTarget = nullptr;
	m_spTarget = nullptr;
	m_eBehaviourName = BH_FOLLOW;
}

FollowBehaviour::FollowBehaviour(Agent * target) : m_pTarget(target)
{
	m_spTarget = nullptr;
	m_eBehaviourName = BH_FOLLOW;
}

FollowBehaviour::FollowBehaviour(std::shared_ptr<Agent> target) : m_spTarget(target)
{
	m_pTarget = nullptr;
	m_eBehaviourName = BH_FOLLOW;
}

FollowBehaviour::~FollowBehaviour()
{
}

Status FollowBehaviour::execute(Agent * agent)
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

void FollowBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{
	if (m_pTarget != nullptr)
	{
		glm::vec2 target(m_pTarget->m_movementInfo.m_position.x, m_pTarget->m_movementInfo.m_position.y);
		glm::vec2 position(behaviour.m_position.x, behaviour.m_position.y);
	
		glm::vec2 direction = target - position;
		direction = glm::normalize(direction);

		behaviour.m_acceleration.x = direction.x * behaviour.m_maxSpeed;
		behaviour.m_acceleration.y = direction.y * behaviour.m_maxSpeed;

		glm::vec2 accel(behaviour.m_acceleration.x, behaviour.m_acceleration.y);
		if (glm::length(accel) > behaviour.m_maxForce)
		{
			accel = glm::normalize(accel) * behaviour.m_maxForce;
			behaviour.m_acceleration.x = accel.x;
			behaviour.m_acceleration.y = accel.y;
		}
	}
	else if (m_spTarget != nullptr)
	{
		glm::vec2 target(m_spTarget->m_movementInfo.m_position.x, m_spTarget->m_movementInfo.m_position.y);
		glm::vec2 position(behaviour.m_position.x, behaviour.m_position.y);

		glm::vec2 direction = target - position;
		direction = glm::normalize(direction);

		behaviour.m_acceleration.x = direction.x * behaviour.m_maxSpeed;
		behaviour.m_acceleration.y = direction.y * behaviour.m_maxSpeed;

		glm::vec2 accel(behaviour.m_acceleration.x, behaviour.m_acceleration.y);
		if (glm::length(accel) > behaviour.m_maxForce)
		{
			accel = glm::normalize(accel) * behaviour.m_maxForce;
			behaviour.m_acceleration.x = accel.x;
			behaviour.m_acceleration.y = accel.y;
		}
	}




}
