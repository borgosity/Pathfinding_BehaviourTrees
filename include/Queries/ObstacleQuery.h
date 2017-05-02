#pragma once
#include "IQuery.h"

class ObstacleQuery :
	public IQuery
{
public:
	ObstacleQuery();
	virtual ~ObstacleQuery();

	virtual Status execute(Agent * agent);
};

