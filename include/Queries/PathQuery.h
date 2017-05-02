#pragma once
#include "IQuery.h"

class PathQuery :
	public IQuery
{
public:
	PathQuery();
	virtual ~PathQuery();

	virtual Status execute(Agent * agent);
};

