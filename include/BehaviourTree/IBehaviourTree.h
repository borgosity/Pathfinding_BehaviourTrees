#pragma once

class SpriteBatch;
class Agent;

enum Status
{
	BH_INVALID,
	BH_SUCCESS,
	BH_FAILURE,
	BH_PENDING,
	BH_ABORTED
};

class IBehaviourTree
{
public:
	IBehaviourTree() : m_eStatus(BH_INVALID) {};
	virtual ~IBehaviourTree() = 0 {};

	virtual Status execute(Agent * agent) = 0;

private:
	Status m_eStatus;
};

