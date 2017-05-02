#include "PathFinder.h"



/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
bool sortGAscending(Graph::Node * a, Graph::Node * b)
{
	return a->m_gScore < b->m_gScore;
}

bool sortFAscending(Graph::Node * a, Graph::Node * b)
{
	return a->m_fScore < b->m_fScore;
}

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void PathFinder::Dijkstras(Graph::Node * nodeStart, const std::list<Graph::Node*>& endNodes, std::list<Graph::Node*>& outPath)
{
	if (nodeStart == nullptr)
		return;

	int currentStep = 0;
	std::list<Graph::Node*> priorityList;	// priority queue
	std::list<Graph::Node*> traversedList;  // traversed list

	Graph::Node * endNode = nullptr;

	nodeStart->m_gScore = 0;
	nodeStart->m_pParent = nullptr;

	// put selected start node on open list
	priorityList.push_back(nodeStart);

	//  
	while (priorityList.empty() == false)
	{
		// push lowest to the front of the queue
		priorityList.sort(sortGAscending);

		// get the first node off the front of queue 
		Graph::Node * node = priorityList.front();
		// remove node from front of queue
		priorityList.pop_front();

		// loop through list of end nodes until node of top of queue is found
		for (auto it = endNodes.begin(); it != endNodes.end(); it++)
		{
			// if node matches end node set it as end node 
			if (node == *it)
			{
				endNode = node;
				//break;
			}
		}

		// push node onto closed queue
		traversedList.push_back(node);

		// loop through node connections(edges)
		for (auto it = node->m_connections.begin(); it != node->m_connections.end(); it++)
		{
			Graph::Node * connection = (*it).m_pConnection;
			if (connection == nullptr)
			{
				continue;
			}

			bool inTraversed = std::find(traversedList.begin(), traversedList.end(), connection) != traversedList.end();
			bool inPriority = std::find(priorityList.begin(), priorityList.end(), connection) != priorityList.end();

			float gScore = node->m_gScore + (*it).m_cost;

			// if not traversed already, set score
			if (!inTraversed)
			{
				connection->m_gScore = gScore;
				if (connection->m_pParent == nullptr)
				{
					connection->m_pParent = node;
				}
				(*it).m_checked = true;

			}
			// if already travesed check if the score is lower
			else
			{
				if (gScore < connection->m_gScore)
				{
					connection->m_gScore = gScore;
					if (connection->m_pParent == nullptr)
					{
						connection->m_pParent = node;
					}
				}
			}

			// add to open list if not already there
			if (!inPriority && !inTraversed)
			{
				priorityList.push_back(connection);
			}
		}
	}

	// calculate the path
	Graph::Node * current = endNode;
	while (current != nullptr)
	{
		outPath.push_back(current);
		current = current->m_pParent;
	}
}

void  PathFinder::Dijkstras(Graph::Node * pathStart, const std::list<Graph::Node*> &graphNodes, std::list<Graph::Node*>& outPath, std::list<Graph::Node*> &traversedNodes)
{
	if (pathStart == nullptr)
		return;

	int currentStep = 0;
	std::list<Graph::Node*> priorityList;	// priority queue
	std::list<Graph::Node*> traversedList;  // traversed list

	Graph::Node * endNode = nullptr;

	pathStart->m_gScore = 0;
	pathStart->m_pParent = nullptr;

	// put selected start node on open list
	priorityList.push_back(pathStart);

	//  
	while (priorityList.empty() == false)
	{
		// push lowest to the front of the queue
		priorityList.sort(sortGAscending);

		// get the first node off the front of queue 
		Graph::Node * node = priorityList.front();
		// remove node from front of queue
		priorityList.pop_front();

		// loop through list of end nodes until node of top of queue is found
		for (auto it = graphNodes.begin(); it != graphNodes.end(); it++)
		{
			// if node matches end node set it as end node 
			if (node == *it)
			{
				endNode = node;
				//break;
			}
		}

		// push node onto closed queue
		traversedList.push_back(node);

		// loop through node connections(edges)
		for (auto it = node->m_connections.begin(); it != node->m_connections.end(); it++)
		{
			Graph::Node * connection = (*it).m_pConnection;
			if (connection == nullptr)
			{
				continue;
			}

			// set true if connection(edge) found in travered list
			bool inTraversed = std::find(traversedList.begin(), traversedList.end(), connection) != traversedList.end();
			// set true if connection(edge) found in priority list
			bool inPriority = std::find(priorityList.begin(), priorityList.end(), connection) != priorityList.end();

			// set nodes new G score
			float gScore = node->m_gScore + (*it).m_cost;

			// if not traversed already, set score
			if (!inTraversed)
			{
				connection->m_gScore = gScore;
				if (connection->m_pParent == nullptr)
				{
					connection->m_pParent = node;
				}
				(*it).m_checked = true;

			}
			// if already travesed check if the score is lower
			else
			{
				if (gScore < connection->m_gScore)
				{
					connection->m_gScore = gScore;
					if (connection->m_pParent == nullptr)
					{
						connection->m_pParent = node;
					}
				}
			}

			// add to open list if not already there
			if (!inPriority && !inTraversed)
			{
				priorityList.push_back(connection);
			}
		}
	}
	traversedNodes = traversedList;
	// calculate the path
	Graph::Node * current = endNode;
	while (current != nullptr)
	{
		outPath.push_back(current);
		current = current->m_pParent;
	}
}

void PathFinder::AStar(Graph::Node * pathStart, Graph::Node * pathEnd, std::list<Graph::Node*>& outPath)
{
	if (pathStart == nullptr)
		if (pathStart == nullptr)
			return;

	int currentStep = 0;
	std::list<Graph::Node*> priorityList;	// priority queue
	std::list<Graph::Node*> traversedList;  // traversed list

	pathStart->m_gScore = 0;
	pathStart->m_pParent = nullptr;
	pathEnd->m_pParent = nullptr;

	// put selected start node on open list
	priorityList.push_back(pathStart);

	//  
	while (priorityList.empty() == false)
	{
		// push lowest to the front of the queue
		priorityList.sort(sortFAscending);

		// get the first node off the front of queue 
		Graph::Node * node = priorityList.front();
		// remove node from front of queue
		priorityList.pop_front();

		// if node matches end node set it as end node 
		if (node == pathEnd)
		{
			break;
		}

		// push node onto closed queue
		traversedList.push_back(node);

		// loop through node connections(edges)
		for (auto it = node->m_connections.begin(); it != node->m_connections.end(); it++)
		{
			Graph::Node * connection = (*it).m_pConnection;
			if (connection == nullptr)
			{
				continue;
			}

			// set nodes new G score
			float gScore = node->m_gScore + (*it).m_cost;
			// set nodes H score == distance from connection to pathEnd
			float hScore = glm::distance(connection->m_position, pathEnd->m_position);

			// set nodes F score 
			//float fScore = gScore + (hScore * 1.75f);
			float fScore = gScore + hScore;

			// set true if connection(edge) found in travered list
			bool inTraversed = std::find(traversedList.begin(), traversedList.end(), connection) != traversedList.end();
			// set true if connection(edge) found in priority list
			bool inPriority = std::find(priorityList.begin(), priorityList.end(), connection) != priorityList.end();

			// if not traversed already, set score
			if (!inTraversed)
			{
				connection->m_gScore = gScore;
				connection->m_hScore = hScore;
				connection->m_fScore = fScore;
				if (connection->m_pParent == nullptr)
				{
					connection->m_pParent = node;
				}
				(*it).m_checked = true;

			}
			// if already travesed check if the score is lower
			else
			{
				if (fScore < connection->m_fScore)
				{
					connection->m_gScore = gScore;
					connection->m_hScore = hScore;
					connection->m_fScore = fScore;
					if (connection->m_pParent == nullptr)
					{
						connection->m_pParent = node;
					}
				}
			}

			// add to priority list if not already there
			if (!inPriority && !inTraversed)
			{
				priorityList.push_back(connection);
			}

			//reset scores
			gScore = 0;
			hScore = 0;
			fScore = 0;
		}
	}

	// calculate the path
	Graph::Node * current = pathEnd;
	while (current != nullptr)
	{
		outPath.push_back(current);
		if (current->m_pParent == nullptr)
		{
			current = current->m_pParent;
		}
		// avoid the 'my parents parent is myself' loop
		else if (current->m_pParent != nullptr && current->m_pParent->m_pParent != current)
		{
			current = current->m_pParent;
		}
		else
		{
			break;
		}
	}
}

void PathFinder::AStar(Graph::Node * pathStart, Graph::Node * pathEnd, std::list<Graph::Node*>& outPath, std::list<Graph::Node*>& traversedNodes)
{
	if (pathStart == nullptr)
		return;

	int currentStep = 0;
	std::list<Graph::Node*> priorityList;	// priority queue
	std::list<Graph::Node*> traversedList;  // traversed list

	pathStart->m_gScore = 0;
	pathStart->m_pParent = nullptr;
	pathEnd->m_pParent = nullptr;

	// work out start nodes distance from the ned node
	float snHScore = glm::distance(pathStart->m_position, pathEnd->m_position);

	// put selected start node on open list
	priorityList.push_back(pathStart);

	//  
	while (priorityList.empty() == false)
	{
		// push lowest to the front of the queue
		priorityList.sort(sortFAscending);

		// get the first node off the front of queue 
		Graph::Node * node = priorityList.front();
		// remove node from front of queue
		priorityList.pop_front();

		// if node matches end node set it as end node 
		if (node == pathEnd)
		{
			break;
		}


		// push node onto closed queue
		traversedList.push_back(node);

		// loop through node connections(edges)
		for (auto it = node->m_connections.begin(); it != node->m_connections.end(); it++)
		{
			Graph::Node * connection = (*it).m_pConnection;
			if (connection == nullptr)
			{
				continue;
			}

			// set nodes new G score
			float gScore = node->m_gScore + (*it).m_cost;
			// set nodes H score == distance from connection to pathEnd
			float hScore = glm::distance(connection->m_position, pathEnd->m_position);

			//if (hScore > (snHScore + 50))
			//	break;

			//if (connection->m_pParent != nullptr)
			//{
			//	if (hScore > (connection->m_pParent->m_hScore + 50))
			//		break;

			//	//if (connection->m_pParent->m_pParent != nullptr)
			//	//	if (glm::distance(connection->m_position, connection->m_pParent->m_pParent->m_position) > 100)
			//	//		break;
			//}

			// set nodes F score 
			//float fScore = gScore + (hScore * 1.75f);
			float fScore = gScore + hScore;

			// set true if connection(edge) found in travered list
			bool inTraversed = std::find(traversedList.begin(), traversedList.end(), connection) != traversedList.end();
			// set true if connection(edge) found in priority list
			bool inPriority = std::find(priorityList.begin(), priorityList.end(), connection) != priorityList.end();

			// if not traversed already, set score
			if (!inTraversed)
			{
				connection->m_gScore = gScore;
				connection->m_hScore = hScore;
				connection->m_fScore = fScore;
				if (connection->m_pParent == nullptr)
				{
					connection->m_pParent = node;
				}
				(*it).m_checked = true;

			}
			// if already travesed check if the score is lower
			else
			{
				if (fScore < connection->m_fScore)
				{
					connection->m_gScore = gScore;
					connection->m_hScore = hScore;
					connection->m_fScore = fScore;
					if (connection->m_pParent == nullptr)
					{
						connection->m_pParent = node;
					}
				}
			}

			// add to priority list if not already there
			if (!inPriority && !inTraversed)
			{
				priorityList.push_back(connection);
			}

			//reset scores
			gScore = 0;
			hScore = 0;
			fScore = 0;
		}
	}
	// copy list of traversed nodes
	traversedNodes = traversedList;

	// calculate the path
	Graph::Node * current = pathEnd;
	while (current != nullptr)
	{
		outPath.push_back(current);
		if (current->m_pParent == nullptr)
		{
			current = current->m_pParent;
		}
		// avoid the 'my parents parent is myself' loop
		else if (current->m_pParent != nullptr && current->m_pParent->m_pParent != current)
		{
			current = current->m_pParent;
		}
		else
		{
			break;
		}
	}
}
