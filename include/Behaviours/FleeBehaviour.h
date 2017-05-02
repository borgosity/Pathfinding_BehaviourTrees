#pragma once
#include "IBehaviour.h"

#include <memory>

class Agent;

class FleeBehaviour :
	public IBehaviour
{
public:
	FleeBehaviour(std::shared_ptr<Agent> target);
	~FleeBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_FLEE; }

private:
	std::shared_ptr<Agent>	m_spTarget;
};

