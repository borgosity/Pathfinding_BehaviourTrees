#pragma once
#include "IBehaviour.h"

#include <memory>

class Agent;

class FollowBehaviour :
	public IBehaviour
{
public:
	FollowBehaviour();
	FollowBehaviour(Agent * target);
	FollowBehaviour(std::shared_ptr<Agent> target);
	~FollowBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) {}
	virtual BehaviourName behaviourType() { return BH_FOLLOW; }

private:
	Agent * m_pTarget;
	std::shared_ptr<Agent>	m_spTarget;
};

