#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <list>

#include "Graph.h"

class PathFinder
{

public:
	PathFinder();
	~PathFinder();

	void Dijkstras(Graph::Node * nodeStart, const std::list<Graph::Node*> &endNodes, std::list<Graph::Node*> &outPath);
	void Dijkstras(Graph::Node * pathStart, const std::list<Graph::Node*> &graphNodes, std::list<Graph::Node*> &outPath, std::list<Graph::Node*> &traversedNodes);
	void AStar(Graph::Node * pathStart, Graph::Node * pathEnd, std::list<Graph::Node*> &outPath);
	void AStar(Graph::Node * pathStart, Graph::Node * pathEnd, std::list<Graph::Node*> &outPath, std::list<Graph::Node*> &traversedNodes);

private:
		// pointer to the original nodein the graph
		Graph::Node * m_pNode;

		// information required for pathfinding
		Graph::Node *	m_pParent;
		float			m_gScore;
		float			m_hScore;
		float			m_fScore;
		std::vector< Graph::Edge > m_connections;

};

