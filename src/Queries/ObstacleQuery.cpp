#include "ObstacleQuery.h"
#include "Agent.h"
#include "Application2D.h"
#include "Obstacle.h"
#include <memory>
#include <vector>
#include <GLFW\glfw3.h>

ObstacleQuery::ObstacleQuery()
{
}


ObstacleQuery::~ObstacleQuery()
{
}

Status ObstacleQuery::execute(Agent * agent)
{
	std::vector<std::shared_ptr<Obstacle>> * obstacleList = Application2D::getInstance()->ObstacleList();

	// check agent if in proximity of obstacle
	for (auto i = obstacleList->begin(); i != obstacleList->end(); i++)
	{
		spObstacle spOb = (*i);
		//float distance2 = glm::distance(spOb->m_configurationInfo.m_vPosition, (agent->m_movementInfo.m_position + agent->m_movementInfo.m_sight));
		float distance2 = glm::distance(spOb->m_configurationInfo.m_vPosition, agent->m_movementInfo.m_position);
		// if distance between agents is less than 50 and not in flee state then flee
		if (distance2 < (spOb->m_configurationInfo.m_fRadius + 15.0f))
		{
			agent->closetObstacle(spOb);
			return BH_SUCCESS;
		}
	}
	agent->closetObstacle(nullptr);
	return BH_FAILURE;
}
