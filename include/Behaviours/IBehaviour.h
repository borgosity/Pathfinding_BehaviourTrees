#pragma once
#include "IBehaviourTree.h"
struct MovementInfo;
class Agent;

enum BehaviourName
{
	BH_ARRIVAL,
	BH_AVOID,
	BH_EVADE,
	BH_FLEE,
	BH_FOLLOW,
	BH_KEYBOARD,
	BH_PATH,
	BH_PURSUE,
	BH_SEEK,
	BH_WAITING,
	BH_WANDER
};

class IBehaviour
{
public:
	virtual ~IBehaviour() = 0 {};

	virtual Status execute(Agent * agent) = 0;
	virtual void Update(float deltaTime, MovementInfo & behaviour) = 0;
	virtual void Draw(MovementInfo * behaviour) = 0;
	virtual BehaviourName behaviourType() = 0;
protected:
	BehaviourName m_eBehaviourName;
};

