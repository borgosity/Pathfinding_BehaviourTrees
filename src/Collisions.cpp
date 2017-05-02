#include "Collisions.h"
#include "Agent.h"

/*****************************************************************************************************************
Is Object Coliding With Other Objects(shared_ptr)
******************************************************************************************************************/
bool IsColliding(std::shared_ptr<Agent> agentA, std::shared_ptr<Agent> agentB)
{
	// sum of both radius
	float radSum = (agentA->size() / 2) + (agentB->size() / 2);

	// vector sum of object position minus player position
	glm::vec2 vecSum = agentA->m_movementInfo.m_position;
	vecSum -= agentB->m_movementInfo.m_position;

	// vector magnitude of vector sum
	float vecMag = (float)vecSum.length();

	// return true if colliding and false if they aren't
	return ((vecMag * vecMag) <= (radSum * radSum));
}
/*****************************************************************************************************************
Is Object Coliding With Other Objects(Object*)
******************************************************************************************************************/
bool IsColliding(Agent * agentA, Agent * agentB)
{
	// sum of both radius
	// sum of both radius
	float radSum = (agentA->size() / 2) + (agentB->size() / 2);

	// vector sum of object position minus player position
	glm::vec2 vecSum = agentA->m_movementInfo.m_position;
	vecSum -= agentB->m_movementInfo.m_position;

	// vector magnitude of vector sum
	float vecMag = (float)vecSum.length();

	// return true if colliding and false if they aren't
	return ((vecMag * vecMag) <= (radSum * radSum));
}