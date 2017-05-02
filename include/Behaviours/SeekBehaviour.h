#pragma once
#include "IBehaviour.h"
#include <memory>

class Agent;

class SeekBehaviour :
	public IBehaviour
{
public:
	SeekBehaviour();
	SeekBehaviour(Agent * target);
	SeekBehaviour(std::shared_ptr<Agent> target);
	~SeekBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_SEEK; }

private:
	Agent * m_pTarget;
	std::shared_ptr<Agent>	m_spTarget;
};

