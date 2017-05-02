#include "PathNewQuery.h"
#include "Application2D.h"
#include "Agent.h"

PathNewQuery::PathNewQuery()
{
}


PathNewQuery::~PathNewQuery()
{
}

Status PathNewQuery::execute(Agent * agent)
{
	if (agent->pathList()->empty() && agent->endPoint() != nullptr)
	{
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}

}
