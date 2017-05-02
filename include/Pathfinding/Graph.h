#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <list>

#include "SpriteBatch.h"

class Application2D;

class Graph
{
public:
	struct Node;

	struct Edge
	{
		Node *	m_pConnection;
		float	m_cost;
		bool	m_checked = false;

		// default constructor
		Edge() : m_pConnection(nullptr), m_cost(0) {}

		// overloaded constructor
		Edge( Node * pNode) : m_pConnection(pNode), m_cost(0) {}

		// overloaded constructor
		Edge( Node * pNode, float fCost) : m_pConnection(pNode), m_cost(fCost) {}

	};

	struct Node
	{
		Node *		m_pParent;
		glm::vec2	m_position;
		float		m_gScore;
		float		m_hScore;
		float		m_fScore;
		bool		m_startNode = false;
		bool		m_endNode = false;
		bool		m_path = false;

		std::vector< Graph::Edge > m_connections;

		// default constructor
		Node() : m_gScore(0), m_position(0, 0), m_pParent(nullptr) {}

		//overloaded constructor
		Node(glm::vec2 pos) : m_gScore(0), m_position(pos), m_pParent(nullptr) {}

		//overloaded constructor
		Node(glm::vec2 pos, Node * pParent) : m_gScore(0), m_position(pos), m_pParent(pParent) {}
	};

public:
	
	Graph();
	virtual ~Graph();

	Node * AddNode(glm::vec2 position);
	void AddConnection(Node * nodeA, Node * NodeB, float cost = 1.0f);

	void FindNodes(std::list<Node*> &list, glm::vec2 position, float distance);
	void RemoveNode(Node * pNode);

	void ResetNodes();
	void ResetNodes(Application2D * app);

	void Update(float deltaTime);
	void Draw(SpriteBatch * spriteBatch);
	void DrawDebug(SpriteBatch * spriteBatch);

	std::list<Node*> graphNodelist();

	void startSelected(bool flag);
	void endSelected(bool flag);

protected:
	std::list<Node*>  m_nodes;
	Texture * m_pGroundTexture;
	Texture * m_pStartTexture;
	Texture * m_pEndTexture;
	Texture * m_pPathTexture;
	Font	* m_pFont;

	bool m_startSelected = false;
	bool m_endSelected = false;

};

