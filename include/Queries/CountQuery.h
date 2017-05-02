#pragma once
#include "IQuery.h"
#include <memory>

class Agent;

class CountQuery :
	public IQuery
{
public:
	CountQuery();
	virtual ~CountQuery();

	virtual Status execute(Agent * agent);

private:
	std::shared_ptr<Agent> m_spClosestAgent;
	float					m_fClosestDistance;
};

