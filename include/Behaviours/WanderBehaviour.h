#pragma once
#include "IBehaviour.h"
#include <glm\glm.hpp>
#include <memory>

class Agent;
typedef std::shared_ptr<Agent> spAgent;

class WanderBehaviour :
	public IBehaviour
{
public:
	WanderBehaviour();
	WanderBehaviour(spAgent target, float radius, float jitter, float distance);
	~WanderBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour);
	virtual BehaviourName behaviourType() { return BH_WANDER; }

private:
	// agent member variables
	spAgent	m_spTarget;
	
	// wander member variables
	glm::vec2	m_vTarget;			// target vector
	glm::vec2	m_vCircleCentre;	// wander circle
	glm::vec2	m_vPrevLoc;			// previous location
	float		m_fRadius;			// circle radious
	float		m_fDistance;		// circle distance from player	
	float		m_fJitter;			// wander jitter
	float		m_fWanderAngle;		// wander angle

	// private member functions
	void setAngle(glm::vec2 & vector2, float wanderAngle);
	void randomTarget();  // uses private meber variable to produce the target
	void wander1(float deltaTime, MovementInfo & behaviour);
	void wander2(float deltaTime, MovementInfo & behaviour);

};

