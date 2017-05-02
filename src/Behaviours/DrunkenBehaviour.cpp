#include "DrunkenBehaviour.h"
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include "Agent.h"
#include "Application2D.h"


#define M_PI       3.14159265358979323846

DrunkenBehaviour::DrunkenBehaviour(Agent * target) : m_pTarget(target)
{
	m_spTarget = nullptr;
}

DrunkenBehaviour::DrunkenBehaviour(std::shared_ptr<Agent> target) : m_spTarget(target)
{
	m_pTarget = nullptr;
}

DrunkenBehaviour::~DrunkenBehaviour()
{
}

void DrunkenBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{

	m_accumulatedTime += deltaTime;
	
	if (m_pTarget != nullptr)
	{
		glm::vec2 target(m_pTarget->m_movementInfo.m_positionX, m_pTarget->m_movementInfo.m_positionY);
		glm::vec2 position(behaviour.m_positionX, behaviour.m_positionY);

		glm::vec2 direction = target - position;
		direction = glm::normalize(direction);

		behaviour.m_accelerationX = direction.x * behaviour.m_maxSpeed * m_accumulatedTime;
		behaviour.m_accelerationY = direction.y * behaviour.m_maxSpeed * m_accumulatedTime;

		glm::vec2 accel(behaviour.m_accelerationX, behaviour.m_accelerationY);
		if (glm::length(accel) > behaviour.m_maxForce)
		{
			accel = glm::normalize(accel) * behaviour.m_maxForce;
			behaviour.m_accelerationX = accel.x;
			behaviour.m_accelerationY = accel.y;
		}
	}
	else if (m_spTarget != nullptr)
	{
		glm::vec2 target(m_spTarget->m_movementInfo.m_positionX, m_spTarget->m_movementInfo.m_positionY);
		glm::vec2 position(behaviour.m_positionX, behaviour.m_positionY);

		glm::vec2 direction = target - position;
		direction = glm::normalize(direction);

		behaviour.m_accelerationX = direction.x * behaviour.m_maxSpeed;
		behaviour.m_accelerationY = direction.y * behaviour.m_maxSpeed;

		glm::vec2 accel(behaviour.m_accelerationX, behaviour.m_accelerationY);
		if (glm::length(accel) > behaviour.m_maxForce)
		{
			accel = glm::normalize(accel) * behaviour.m_maxForce;
			behaviour.m_accelerationX = accel.x;
			behaviour.m_accelerationY = accel.y;
		}
	}

}
