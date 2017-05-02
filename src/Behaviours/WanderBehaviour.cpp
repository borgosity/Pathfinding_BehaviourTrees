#include <glm\glm.hpp>
#include <glm\gtx\norm.hpp>
#include <GLFW/glfw3.h>
#include <math.h>
#include "SpriteBatch.h"
#include "WanderBehaviour.h"
#include "Agent.h"
#include "GameDef.h"


WanderBehaviour::WanderBehaviour()
{
	m_fRadius = WANDER_RADIUS;
	m_fJitter = WANDER_JITTER;
	m_fDistance = WANDER_DISTANCE;
	m_vTarget.x = (float)(rand() % SCREEN_W);
	m_vTarget.y = (float)(rand() % SCREEN_H);
	m_fWanderAngle = (float)(rand() % 360 + 1);
	m_eBehaviourName = BH_WANDER;
}

WanderBehaviour::WanderBehaviour(spAgent target, float radius, float jitter, float distance) : m_spTarget(target)
{
	m_fRadius = radius;
	m_fJitter = jitter;
	m_fDistance = distance;
	m_vTarget.x = (float)(rand() % SCREEN_W);
	m_vTarget.y = (float)(rand() % SCREEN_H);
	m_fWanderAngle = (float)(rand() % 360 + 1);
	m_eBehaviourName = BH_WANDER;
}

WanderBehaviour::~WanderBehaviour()
{
}

Status WanderBehaviour::execute(Agent * agent)
{
	if (agent->GetBehaviour() == this)
	{
		return BH_SUCCESS;
	}
	else
	{
		agent->SetBehaviour(this);
		return BH_SUCCESS;
	}
}

void WanderBehaviour::Update(float deltaTime, MovementInfo & behaviour)
{

	if ((glfwGetTime() - behaviour.m_prevTime) > behaviour.m_livelyness || (glfwGetTime() - behaviour.m_prevTime) < 0)
	{
		behaviour.m_prevTime = glfwGetTime();
		wander1(deltaTime, behaviour);
		//wander2(deltaTime, behaviour);
	}

	glm::vec2 acceleration = (glm::normalize(m_vTarget - behaviour.m_position) * behaviour.m_maxSpeed) - behaviour.m_velocity;;

	if (glm::length(acceleration) > behaviour.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
		behaviour.m_acceleration = acceleration;
	}

	// Apply accleration to agent
	behaviour.m_velocity += acceleration * deltaTime;
	behaviour.m_position += behaviour.m_velocity * deltaTime;

}

void WanderBehaviour::Draw(MovementInfo * behaviour)
{
	// line from original location to centre of circle
	behaviour->m_spriteBatch->drawLine(m_vPrevLoc.x, m_vPrevLoc.y, m_vCircleCentre.x, m_vCircleCentre.y, 1.0f);
	// line to edge of circle
	behaviour->m_spriteBatch->drawLine(m_vCircleCentre.x, m_vCircleCentre.y, m_vTarget.x, m_vTarget.y, 2.0f);
	// path agent should be heading along
	behaviour->m_spriteBatch->drawLine(behaviour->m_position.x, behaviour->m_position.y, m_vTarget.x, m_vTarget.y, 3.0f);

	// draw a cirle with lines
	double slice = 2 * M_PI / 360;
	glm::vec2 point1(0.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		double angle = slice * i;
		glm::vec2 point2(m_vCircleCentre.x + m_fRadius * cos(angle), m_vCircleCentre.y + m_fRadius * sin(angle));
		if (point1.x == 0 && point1.y == 0)
		{
			point1 = point2;
		}
		behaviour->m_spriteBatch->drawLine(point1.x, point1.y, point2.x, point2.y);
		point1 = point2;
	}

}

void WanderBehaviour::setAngle(glm::vec2 & vector2, float wanderAngle)
{
	float length = glm::length2(vector2);
	vector2.x = cos(wanderAngle) * length;
	vector2.y = sin(wanderAngle) * length;
}
/***********************************************************************************************************
    set random target
************************************************************************************************************/
void WanderBehaviour::randomTarget()
{
	m_vTarget.x = m_fRadius*cos(m_fWanderAngle) + m_vCircleCentre.x;
	m_vTarget.y = m_fRadius*sin(m_fWanderAngle) + m_vCircleCentre.y;
}

void WanderBehaviour::wander1(float deltaTime, MovementInfo & behaviour)
{
		// reset velocity
		behaviour.m_velocity.x = 0;
		behaviour.m_velocity.y = 0;

		// specify the location of the circle centre based on the agents current velocity
		// then normalise it and move(scale) it to the specified distance infront of the agent
		m_vCircleCentre.x = behaviour.m_position.x;
		m_vCircleCentre.y = behaviour.m_position.y;
		// record current position of agent
		m_vPrevLoc.x = behaviour.m_position.x;
		m_vPrevLoc.y = behaviour.m_position.y;
		//m_vCircleCentre = glm::normalize(m_vCircleCentre);

		// ** NEED TO GET THE DIRECTION THAT THE AGENT IS FACING **
		m_vCircleCentre.x = m_fDistance*cos(behaviour.m_rotation) + behaviour.m_position.x;
		m_vCircleCentre.y = m_fDistance*sin(behaviour.m_rotation) + behaviour.m_position.y;
		//m_vCircleCentre += m_fDistance; // moves circle ot in front of agent

		// find random spot on circle
		randomTarget();

		// change wanderAngle for next frame
		m_fWanderAngle += ((float)(rand() % 360 + 1) * m_fJitter) - (m_fJitter * 0.5f);

		// calcutate and return wander force
		glm::vec2 wanderForce(m_vCircleCentre + m_vTarget);

		// calculate the acceleration required to move agent to target (distance minus current velocity)
		//glm::vec2 acceleration(glm::distance(wanderForce, behaviour.m_velocity) - behaviour.m_velocity);

}

void WanderBehaviour::wander2(float deltaTime, MovementInfo & behaviour)
{
	//// pick a random target on the screen
	glm::vec2 target((float)(rand() % SCREEN_W + 0.5), (float)(rand() % SCREEN_H + 0.5));
	
	// vector from agent to target
	glm::vec2 distance = glm::normalize(target - behaviour.m_position);
	distance *= m_fRadius;
	// scale vector by maxSpeed
	distance = distance * behaviour.m_maxSpeed;
	// calculate the acceleration required to move agent to target (distance minus current velocity)
	glm::vec2 acceleration = distance - behaviour.m_velocity;

	if (glm::length(acceleration) > behaviour.m_maxAcceleration)
	{
		acceleration = glm::normalize(acceleration) * behaviour.m_maxAcceleration;
		behaviour.m_acceleration = acceleration;
	}

	// Apply accleration to agent
	behaviour.m_velocity += acceleration * deltaTime;
	behaviour.m_position += behaviour.m_velocity * deltaTime;
}
