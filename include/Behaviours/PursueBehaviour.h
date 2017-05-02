#pragma once
#include "IBehaviour.h"

#include <memory>

class Agent;
typedef std::shared_ptr<Agent> spAgent;

class PursueBehaviour :
	public IBehaviour
{
public:
	PursueBehaviour();
	PursueBehaviour(spAgent target);
	PursueBehaviour(spAgent target, float weight);
	~PursueBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_PURSUE; }

private:
	spAgent	m_spTarget;
	float	m_fWeight;
};

