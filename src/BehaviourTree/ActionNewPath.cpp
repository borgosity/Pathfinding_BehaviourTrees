#include "ActionNewPath.h"
#include "Behaviours\IBehaviour.h"
#include "Agent.h"
#include "Application2D.h"
#include "Graph.h"


ActionNewPath::ActionNewPath()
{
	m_behaviour = nullptr;
}

ActionNewPath::ActionNewPath(spBehaviour behaviour)
{
	m_behaviour = behaviour;
}

ActionNewPath::~ActionNewPath()
{
}

Status ActionNewPath::execute(Agent * agent)
{
	Application2D * app = Application2D::getInstance();
	// reset edge weights
	app->resetEdgeWeights();
	// add weights to graph for wanderers
	// for every node on map check if there is a wander within radius
	//	if there is add 5 to the cost of it's edges/connections
	app->adjustEgdeWeights();
	// get player position
	// get closest node from application for new start point
	Graph::Node * startPoint = app->closetNode(agent->m_movementInfo.m_position);
	// generate new path from application (auto sets players start and end points)
	app->generatePath(startPoint, agent->endPoint());

	if (agent->pathList()->empty())
	{
		return BH_FAILURE;
	}
	else
	{
		return BH_SUCCESS;
	}
}
