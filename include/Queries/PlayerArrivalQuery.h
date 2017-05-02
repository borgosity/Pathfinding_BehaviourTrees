#pragma once
#include "IQuery.h"

class PlayerArrivalQuery :
	public IQuery
{
public:
	PlayerArrivalQuery();
	virtual ~PlayerArrivalQuery();

	virtual Status execute(Agent * agent);
};

