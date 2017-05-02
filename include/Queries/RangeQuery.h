#pragma once
#include "IQuery.h"

class RangeQuery :
	public IQuery
{
public:
	RangeQuery();
	virtual ~RangeQuery();

	virtual bool execute(Agent * agent);
};

