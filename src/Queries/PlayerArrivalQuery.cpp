#include "PlayerArrivalQuery.h"
#include "Application2D.h"
#include "PlayerAgent.h"
#include "PathBehaviour.h"

PlayerArrivalQuery::PlayerArrivalQuery()
{
}


PlayerArrivalQuery::~PlayerArrivalQuery()
{
}

Status PlayerArrivalQuery::execute(Agent * agent)
{	
	if (agent->pathList()->size() == 1)
	{
		return BH_SUCCESS;
	}
	else
	{
		return BH_FAILURE;
	}

}
