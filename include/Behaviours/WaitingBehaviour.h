#pragma once

#include "IBehaviour.h"
#include <glm\glm.hpp>

class WaitingBehaviour : 
	public IBehaviour
{
public:
	WaitingBehaviour();
	~WaitingBehaviour();

	Status execute(Agent * agent);
	void Update(float deltaTime, MovementInfo & agentMI);
	virtual void Draw(MovementInfo * agentMI) { return; }
	virtual BehaviourName behaviourType() { return BH_WAITING; }

	void arrivalTarget(MovementInfo & agentMI);

private:
	glm::vec2	m_vTargetPos;
	float		m_fDistance;
	float		m_fWeight;
};

