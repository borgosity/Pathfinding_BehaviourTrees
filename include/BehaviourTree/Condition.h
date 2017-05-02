#pragma once
#include "BhtLeaf.h"
#include <memory>

class IQuery;

class Condition :
	public BhtLeaf
{
public:
	typedef std::shared_ptr<IQuery> spQuery;

	Condition(spQuery query);
	virtual ~Condition();

	virtual Status execute(Agent * agent);

protected:
	spQuery m_query;
};

