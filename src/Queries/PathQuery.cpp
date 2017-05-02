#include "PathQuery.h"
#include "Application2D.h"
#include "PlayerAgent.h"

PathQuery::PathQuery()
{
}


PathQuery::~PathQuery()
{
}

Status PathQuery::execute(Agent * agent)
{
	if (agent->pathList()->empty() || agent->pathList()->size() == 1)
	{
		return BH_FAILURE;
	}
	else
	{
		return BH_SUCCESS;
	}

}
