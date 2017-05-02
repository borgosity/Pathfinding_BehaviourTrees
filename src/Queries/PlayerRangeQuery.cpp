#include "PlayerRangeQuery.h"
#include "Agent.h"
#include "PlayerAgent.h"
#include "Application2D.h"
#include <memory>
#include <GLFW\glfw3.h>

PlayerRangeQuery::PlayerRangeQuery()
{
}


PlayerRangeQuery::~PlayerRangeQuery()
{
}

Status PlayerRangeQuery::execute(Agent * agent)
{
	std::shared_ptr<PlayerAgent> player = Application2D::getInstance()->getPlayer();
	// check agent if in proximity of player

	float distance = glm::distance(player->m_movementInfo.m_position, agent->m_movementInfo.m_position);
	// if distance between agents is less than 50 and not in flee state then flee
	if (distance < 100.0f)
	{
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}
}
