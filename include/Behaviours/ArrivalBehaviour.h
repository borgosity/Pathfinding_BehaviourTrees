#pragma once
#include "IBehaviour.h"
#include <glm\glm.hpp>
#include <memory>

class Agent;
typedef std::shared_ptr<Agent> spAgent;
typedef std::shared_ptr<glm::vec2> spVec2;

class ArrivalBehaviour :
	public IBehaviour
{
public:
	ArrivalBehaviour();
	ArrivalBehaviour(spVec2 target);
	ArrivalBehaviour(spAgent target);
	ArrivalBehaviour(spAgent target, float weight);
	~ArrivalBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_ARRIVAL; }
	spVec2 targetPosition();
	spVec2 targetPosition(spVec2 target);

private:
	spAgent	m_spATarget;
	spVec2	m_spVTarget;
	glm::vec2 m_TargetPos;
	float	m_fWeight;

};

