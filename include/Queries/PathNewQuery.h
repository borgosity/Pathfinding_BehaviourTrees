#pragma once
#include "IQuery.h"

class PathNewQuery :
	public IQuery
{
public:
	PathNewQuery();
	virtual ~PathNewQuery();

	virtual Status execute(Agent * agent);
};

