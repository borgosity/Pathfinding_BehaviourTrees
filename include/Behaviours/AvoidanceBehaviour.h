#pragma once
#include "IBehaviour.h"

#include <memory>

class Obstacle;
typedef std::shared_ptr<Obstacle> spObstacle;

class AvoidanceBehaviour :
	public IBehaviour
{
public:
	AvoidanceBehaviour();
	AvoidanceBehaviour(spObstacle target);
	AvoidanceBehaviour(spObstacle target, float weight);
	~AvoidanceBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & behaviour);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_AVOID; }

private:
	spObstacle	m_spTarget;
	float		m_fWeight;
};

