#include "Condition.h"
#include "Queries\IQuery.h"



Condition::Condition(spQuery query)
{
	m_query = query;
}

Condition::~Condition()
{
}

Status Condition::execute(Agent * agent)
{
	Status result = m_query.get()->execute(agent);
	return result;
}
