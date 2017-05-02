#pragma once
#include "IQuery.h"
#include <memory>

class Agent;

class WandererRangeQuery :
	public IQuery
{
public:
	typedef std::shared_ptr<Agent>		spAgent;

	WandererRangeQuery();
	virtual ~WandererRangeQuery();

	virtual Status execute(Agent * agent);

private:
	spAgent		m_spClosestAgent;
	float		m_fClosestDistance;
};

