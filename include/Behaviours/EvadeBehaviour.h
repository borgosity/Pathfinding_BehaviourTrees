#pragma once
#include "IBehaviour.h"

#include <memory>

class Agent;
typedef std::shared_ptr<Agent> spAgent;

class EvadeBehaviour :
	public IBehaviour
{
public:
	EvadeBehaviour();
	EvadeBehaviour(spAgent target);
	EvadeBehaviour(spAgent target, float weight);
	~EvadeBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_EVADE; }

private:
	spAgent	m_spTarget;
	float	m_fWeight;
};

