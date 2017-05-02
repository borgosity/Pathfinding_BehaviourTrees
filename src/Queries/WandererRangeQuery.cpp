#include "WandererRangeQuery.h"
#include "Agent.h"
#include "WandererAgent.h"
#include "Application2D.h"
#include "GameDef.h"
#include <memory>
#include <vector>
#include <GLFW\glfw3.h>

WandererRangeQuery::WandererRangeQuery()
{
	m_fClosestDistance = 0.0f;
	m_spClosestAgent = nullptr;
}


WandererRangeQuery::~WandererRangeQuery()
{
}

Status WandererRangeQuery::execute(Agent * agent)
{
	std::vector<std::shared_ptr<WandererAgent>> wandererList = (*Application2D::getInstance()->getWanderers());
	int count = 0;
	// get distance between player and wanderers
	for (std::vector<std::shared_ptr<WandererAgent>>::iterator iter = wandererList.begin(); iter != wandererList.end(); iter++ )
	{
		float distance = glm::distance((*iter)->m_movementInfo.m_position, agent->m_movementInfo.m_position);
		if (distance < PLAYER_EVADE_RANGE)
		{
			count++;
			if (m_fClosestDistance <= distance || m_fClosestDistance == 0.0f)
			{
				m_spClosestAgent = (*iter);
				m_fClosestDistance = distance;
			}
		}
	}

	// if distance between agents is less than 50 and not in flee state then flee
	if (count > 0)
	{
		agent->closetAgent(m_spClosestAgent);
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}
}
