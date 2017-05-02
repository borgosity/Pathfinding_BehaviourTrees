#include "ArrivalBehaviour.h"
#include <algorithm>
#include "Agent.h"
#include "GameDef.h"


ArrivalBehaviour::ArrivalBehaviour()
{
	m_spATarget = nullptr;
	m_spVTarget = nullptr;
	m_TargetPos = glm::vec2(0.0f, 0.0f);
	m_fWeight = 0;
	m_eBehaviourName = BH_ARRIVAL;
}

ArrivalBehaviour::ArrivalBehaviour(spVec2 target)
{
	m_spVTarget = target;
	m_TargetPos = (*target.get());
	m_fWeight = 0;
	m_eBehaviourName = BH_ARRIVAL;
}

ArrivalBehaviour::ArrivalBehaviour(spAgent target) : m_spATarget(target)
{
	m_TargetPos = target->m_movementInfo.m_position;
	m_fWeight = 0;
	m_eBehaviourName = BH_ARRIVAL;
}

ArrivalBehaviour::ArrivalBehaviour(spAgent target, float weight)
{
	m_spVTarget = nullptr;
	m_spATarget = target;
	m_TargetPos = target->m_movementInfo.m_position;
	m_fWeight = weight;
	m_eBehaviourName = BH_ARRIVAL;
}

ArrivalBehaviour::~ArrivalBehaviour()
{
}

Status ArrivalBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		float distance = glm::distance(agent->m_movementInfo.m_position, m_TargetPos);
		if (distance < 0.5)
		{
			agent->pathList()->clear();
		}
		else if (distance > 100)
		{
			agent->pathList()->clear();
			return BH_FAILURE;
		}
		return BH_SUCCESS;
	}
	else
	{
		m_TargetPos = agent->pathList()->front()->m_position;
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void ArrivalBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{
	
	float arriveRadius = PLAYER_ARRIVAL_DIS;
	
	// subtract agent postion from target position + targets velocity 
	glm::vec2 direction = glm::normalize(m_TargetPos - behaviour.m_position);
	float distance = glm::distance(behaviour.m_position, m_TargetPos);


	// scale resultant vector by maxSpeed
	// calculate the acceleration required to move agent away to targets estimated location
	glm::vec2 acceleration = glm::normalize(direction) * behaviour.m_maxSpeed;

	// distance scalar
	float scalar = std::min(distance / arriveRadius, 1.0f);

	// if within radius
	if (scalar < 1)
	{
		acceleration *= scalar;

		float d = glm::dot(direction, glm::normalize(behaviour.m_velocity));
		
		glm::vec2 resistance = -(glm::normalize(behaviour.m_velocity)) * glm::length(behaviour.m_velocity) * d * 2.0f;

		acceleration += resistance;

		behaviour.m_acceleration = acceleration;
	}
	acceleration -= behaviour.m_velocity;

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

spVec2 ArrivalBehaviour::targetPosition()
{
	return m_spVTarget;
}

spVec2 ArrivalBehaviour::targetPosition(spVec2 target)
{
	m_spVTarget = target;
	return m_spVTarget;
}
