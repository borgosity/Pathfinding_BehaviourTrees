#include "PathBehaviour.h"
#include "WaitingBehaviour.h"
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include "PlayerAgent.h"
#include "Application2D.h"

PathBehaviour::PathBehaviour()
{
	m_pathNodeList = {};
	m_liTarget = m_pathNodeList.end();
	m_eBehaviourName = BH_PATH;
	m_fWeight = 0;
}

PathBehaviour::~PathBehaviour()
{
}

Status PathBehaviour::execute(Agent * agent)
{
	// if already using this behaviour
	if (agent->GetBehaviour() == this)
	{
		m_liTarget = agent->pathList()->begin();
		// if there i still a path to folloow
		if (m_liTarget != agent->pathList()->end() && agent->pathList()->size() != 0)
		{
			float distance = glm::distance(agent->m_movementInfo.m_position, (*m_liTarget)->m_position);

			if ((distance < 30) && (agent->pathList()->size() > 1))
			{
				agent->pathList()->pop_front();
				m_liTarget = agent->pathList()->begin();
				return BH_SUCCESS;
			}
			else if (distance > 100)
			{
				m_liTarget = agent->pathList()->end();
				agent->pathList()->clear();
				return BH_FAILURE;
			}
			else
			{
				return BH_SUCCESS;
			}

		}
		else if (m_liTarget == agent->pathList()->end() && agent->pathList()->size() != 0)
		{
			agent->pathList()->clear();
			return BH_SUCCESS;
		}
	}
	else
	{
		agent->pathList()->pop_front();
		m_liTarget = agent->pathList()->begin();
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void PathBehaviour::Update(float deltaTime, MovementInfo & agentMI)
{
	//pursue(deltaTime, agentMI);
	seek(deltaTime, agentMI);
}

void PathBehaviour::seek(float deltaTime, MovementInfo & agentMI)
{
	//// vector from agent to target
	//glm::vec2 distance = glm::normalize(m_pTarget->m_movementInfo.m_position - agentMI.m_position);
	//// scale vector by maxSpeed
	//distance = distance * agentMI.m_maxSpeed;
	//// calculate the acceleration required to move agent to target (distance minus current velocity)
	//glm::vec2 acceleration = distance - agentMI.m_velocity;

	// the above compacted
	glm::vec2 acceleration = (glm::normalize((*m_liTarget)->m_position - agentMI.m_position) * agentMI.m_maxSpeed) - agentMI.m_velocity;

	if (glm::length(acceleration) > agentMI.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * agentMI.m_maxAcceleration;
		agentMI.m_acceleration = acceleration;
	}

	// Apply accleration to agent
	agentMI.m_velocity += acceleration * deltaTime;
	agentMI.m_position += agentMI.m_velocity * deltaTime;
}

void PathBehaviour::pursue(float deltaTime, MovementInfo & agentMI)
{
	if (pathNodeList().size() > 2)
	{
		m_liTarget++;
		glm::vec2 nextNodePos = (*m_liTarget)->m_position;
		m_liTarget--;
		m_velocity = glm::normalize(nextNodePos - (*m_liTarget)->m_position);
		// subtract agent postion from target position + targets velocity 
	}
	else
	{
		m_velocity = glm::vec2 (0.0f,0.0f);
	}

	// subtract agent postion from target position + targets velocity 
	glm::vec2 direction = ((*m_liTarget)->m_position + m_velocity) - agentMI.m_position;

	// scale resultant vector by maxSpeed
	// calculate the acceleration required to move agent away to targets estimated location
	glm::vec2 acceleration = (glm::normalize(direction) * agentMI.m_maxSpeed) - agentMI.m_velocity;

	if (glm::length(acceleration) > agentMI.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * agentMI.m_maxAcceleration;
		agentMI.m_acceleration = acceleration;
	}

	if (m_fWeight > 0)
	{
		// Apply accleration to agent
		agentMI.m_velocity += (acceleration * m_fWeight) * deltaTime;
	}
	else
	{
		// Apply accleration to agent
		agentMI.m_velocity += acceleration * deltaTime;
	}
	agentMI.m_position += agentMI.m_velocity * deltaTime;
}

std::list<Graph::Node*> PathBehaviour::pathNodeList()
{
	m_pathNodeList = (*Application2D::getInstance()->getPlayer()->pathList());
	return m_pathNodeList;
}
