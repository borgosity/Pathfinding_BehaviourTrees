#pragma once
#include "IBehaviour.h"
#include <memory>

class Agent;

class DrunkenBehaviour :
	public IBehaviour
{
public:
	DrunkenBehaviour(Agent * target);
	DrunkenBehaviour(std::shared_ptr<Agent> target);
	~DrunkenBehaviour();
	void Update(float deltaTime, MovementInfo & behaviour);

private:
	float m_accumulatedTime;
	bool m_drunk = false;
	Agent * m_pTarget;
	std::shared_ptr<Agent>	m_spTarget;
};

