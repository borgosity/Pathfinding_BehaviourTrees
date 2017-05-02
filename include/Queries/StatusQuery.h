#pragma once
#include "IQuery.h"

class StatusQuery :
	public IQuery
{
public:
	StatusQuery();
	virtual ~StatusQuery();

	virtual Status execute(Agent * agent);
};

