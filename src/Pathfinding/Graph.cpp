#include "PathFinding\Graph.h"
#include <algorithm>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "PlayerAgent.h"
#include "GameDef.h"
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
Graph::Graph()
{
	m_pGroundTexture = new Texture("./bin/textures/ground.png");
	m_pStartTexture = new Texture("./bin/textures/start.png");
	m_pEndTexture = new Texture("./bin/textures/end.png");
	m_pPathTexture = new Texture("./bin/textures/path.png");
	m_pFont = new Font("./bin/font/consolas.ttf", 15);
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
Graph::~Graph()
{
	// delete all nodes added to graph
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		delete (*iter);
	}

	m_nodes.clear();

	delete  m_pGroundTexture;
	delete 	m_pStartTexture;
	delete 	m_pEndTexture;
	delete 	m_pPathTexture;

	delete m_pFont;
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
Graph::Node * Graph::AddNode(glm::vec2 position)
{
	m_nodes.push_back(new Node(position));
	return m_nodes.back();
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::AddConnection(Node * nodeA, Node * nodeB, float cost)
{
	nodeA->m_connections.push_back(Edge(nodeB, cost));
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::FindNodes(std::list<Node*>& list, glm::vec2 position, float distance)
{
	for (auto it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		Node * node = *it;
		float mag = glm::length(node->m_position - position);

		if (mag < distance)
		{
			list.push_back(node);
		}
	}
}
/*------------------------------------------------------------------------------------
 
------------------------------------------------------------------------------------*/
void Graph::RemoveNode(Node * pNode)
{
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		if (n == pNode)
		{
			continue;
		}

		for (auto eit = n->m_connections.begin(); eit != n->m_connections.end(); eit++)
		{
			Edge* e = &(*eit);
			if (e->m_pConnection == pNode)
			{
				n->m_connections.erase(eit);
				break;
			}
		}
	}
	m_nodes.remove(pNode);
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::ResetNodes()
{
	// reset all nodes
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		n->m_startNode = false;
		n->m_endNode = false;
		n->m_path = false;
		n->m_pParent = nullptr;
		m_startSelected = false;
		m_endSelected = false;
		for (auto it = n->m_connections.begin(); it != n->m_connections.end(); it++)
		{
			(*it).m_checked = false;
		}
	}
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::ResetNodes(Application2D * app)
{
	// clear start and end points
	app->setStartPoint(nullptr);
	app->setEndPoint(nullptr);
	app->resetPath();
	
	// reset all nodes
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		n->m_startNode = false;
		n->m_endNode = false;
		n->m_path = false;
		n->m_pParent = nullptr;
		m_startSelected = false;
		m_endSelected = false;
		for (auto it = n->m_connections.begin(); it != n->m_connections.end(); it++)
		{
			(*it).m_checked = false;
		}
	}
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::Update(float deltaTime)
{

}
void Graph::Draw(SpriteBatch * spriteBatch)
{
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		spriteBatch->drawSprite(m_pGroundTexture, n->m_position.x, n->m_position.y);
	}
}
/*------------------------------------------------------------------------------------

------------------------------------------------------------------------------------*/
void Graph::DrawDebug(SpriteBatch * spriteBatch)
{
	//char szBuffer[32];

	// draw points first or else the connection will get drawn over the top
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		// if node is a start node then draw using start node texture
		if (n->m_startNode && !n->m_endNode)
		{
			spriteBatch->drawSprite(m_pStartTexture, n->m_position.x, n->m_position.y);
		}
		// if node is an end node then draw using end node texture
		else if (n->m_endNode && !n->m_startNode)
		{
			spriteBatch->drawSprite(m_pEndTexture, n->m_position.x, n->m_position.y);
		}
		// if node has not been selected draw using the default node texture
		else
		{
			//spriteBatch->drawSprite(m_pDefaultTexture, n->m_position.x, n->m_position.y);
		}

	}

	// now draw connections
	int count = 0;
	for (auto nit = m_nodes.begin(); nit != m_nodes.end(); nit++)
	{
		Node * n = *nit;
		// loop through connections and draw grid
		for (auto eit = n->m_connections.begin(); eit != n->m_connections.end(); eit++)
		{
			Edge* e = &(*eit);
			if (e->m_checked)
			{
				count++;
				spriteBatch->setSpriteColor(255, 255, 255, 1);
				spriteBatch->drawLine(n->m_position.x, n->m_position.y, e->m_pConnection->m_position.x, e->m_pConnection->m_position.y);
			}
			else
			{
				spriteBatch->setSpriteColor(255, 255, 255, 1);
				spriteBatch->drawLine(n->m_position.x, n->m_position.y, e->m_pConnection->m_position.x, e->m_pConnection->m_position.y);
			}
		}
		
	}
	std::string traversed = "Number of edges traversed = " + std::to_string(count);
	spriteBatch->drawText(m_pFont, traversed.c_str(), 500.0f, 5.0f);

}

std::list<Graph::Node*> Graph::graphNodelist()
{
	return m_nodes;
}

void Graph::startSelected(bool flag)
{
	m_startSelected = flag;
}

void Graph::endSelected(bool flag)
{
	m_endSelected = flag;
}
