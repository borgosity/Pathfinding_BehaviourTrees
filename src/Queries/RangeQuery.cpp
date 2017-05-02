#include "RangeQuery.h"
#include "Agent.h"


RangeQuery::RangeQuery()
{
}


RangeQuery::~RangeQuery()
{
}

bool RangeQuery::execute(Agent * agent)
{

	//	// check agent if in proximity of player
	//	for (size_t i = 0; i < m_wandererAgents.size(); i++)
	//	{

	//		float distance = glm::distance(m_agent->m_movementInfo.m_position, m_wandererAgents[i]->m_movementInfo.m_position);
	//		// if distance between agents is less than 50 and not in flee state then flee
	//		if (distance < 50.0f && m_wandererAgents[i]->state() != 1)
	//		{
	//			m_wandererAgents[i]->texture(m_fleeTexture.get());
	//			m_wandererAgents[i]->state(1); // 1 == arrival state
	//			m_wandererAgents[i]->SetBehaviour(new ArrivalBehaviour(m_agent));
	//			m_wandererAgents[i]->spriteBatch(nullptr);
	//		}
	//		// if distance between agents is greater than 50 but less than 150 and not in seek state
	//		else if (distance > 50.0f && distance < 150.0f	&& m_wandererAgents[i]->state() != 2)
	//		{
	//			m_wandererAgents[i]->texture(m_seekTexture.get());
	//			m_wandererAgents[i]->state(2); // 2 == seek state
	//			m_wandererAgents[i]->SetBehaviour(new PursueBehaviour(m_agent));
	//			m_wandererAgents[i]->spriteBatch(nullptr);
	//		}
	//		// if distance between agents is greater than 50 but less than 150 and not in seek state
	//		else if (distance > 150.0f	&& m_wandererAgents[i]->state() != 0)
	//		{
	//			m_wandererAgents[i]->texture(m_wanderTexture.get());
	//			m_wandererAgents[i]->state(0); // 0 == wander state
	//			m_wandererAgents[i]->SetBehaviour(new WanderBehaviour(m_agent, WANDER_RADIUS, WANDER_JITTER, WANDER_DISTANCE));
	//			m_wandererAgents[i]->spriteBatch(m_spriteBatch);
	//			m_wandererAgents[i]->m_movementInfo.m_prevTime = glfwGetTime();
	//		}

	//	}
	
	return true;
}
