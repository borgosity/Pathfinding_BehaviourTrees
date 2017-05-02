#pragma once
#include "IQuery.h"

class PlayerRangeQuery :
	public IQuery
{
public:
	PlayerRangeQuery();
	virtual ~PlayerRangeQuery();

	virtual Status execute(Agent * agent);
};

