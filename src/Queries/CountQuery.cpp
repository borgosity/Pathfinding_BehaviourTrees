#include "CountQuery.h"
#include "Agent.h"
#include "Application2D.h"
#include "GameDef.h"
#include "WandererAgent.h"

CountQuery::CountQuery()
{
}


CountQuery::~CountQuery()
{
}

Status CountQuery::execute(Agent * agent)
{
	std::vector<std::shared_ptr<WandererAgent>> wandererList = (*Application2D::getInstance()->getWanderers());
	int count = 0;
	// get distance between player and wanderers
	for (std::vector<std::shared_ptr<WandererAgent>>::iterator iter = wandererList.begin(); iter != wandererList.end(); iter++)
	{
		float distance = glm::distance((*iter)->m_movementInfo.m_position, agent->m_movementInfo.m_position);
		if (distance < WANDERER_FOLLOW_RANGE)
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
	if (count > WANDERER_GROUP)
	{
		agent->closetAgent(m_spClosestAgent);
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}
}
