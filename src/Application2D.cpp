// std lib include
#include <string>
#include <iostream>

// dependencies includes
#include <GLFW/glfw3.h>

// engine includes
#include "Application2D.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"

// my code includes
#include "PlayerAgent.h"
#include "WandererAgent.h"
#include "Obstacle.h"
#include "GameDef.h"
// behaviour includes
#include "KeyboardBehaviour.h"

#include "PathFinder.h"

Application2D * Application2D::m_instance = nullptr;

Application2D::Application2D() {
	if (m_instance == nullptr) {
		m_instance = this;
	}
}

Application2D::~Application2D() {

}
/*******************************************************************************************************
********************************************************************************************************/
bool Application2D::startup() {
	
	createWindow("A.I. Project", SCREEN_W, SCREEN_H);

	m_spriteBatch = new SpriteBatch();

	// world textures
	m_agentTexture = std::make_shared<Texture>("./bin/textures/agent.png");
	m_obstacleTexture = std::make_shared<Texture>("./bin/textures/obstacle.png");
	m_spGroundTexture = std::make_shared<Texture>("./bin/textures/ground.png");
	m_spBaseTexture = std::make_shared<Texture>("./bin/textures/base.png");
	m_spRocketTexture = std::make_shared<Texture>("./bin/textures/rocket.png");
	m_spFlamesTexture = std::make_shared<Texture>("./bin/textures/flames.png");

	// player initiation
	m_agent = std::make_shared<PlayerAgent>(glm::vec2(PLAYER_START_X, PLAYER_START_Y));
	m_agent->SetBehaviour(new KeyboardBehaviour());
	m_agent->state(4); // 4 == keyboard behaviour
	m_agent->texture(m_agentTexture.get());

	m_finished = false;

	// world objects
	CreateWandererAgents(WANDERER_COUNT);
	CreateObstacles(OBSTACLE_COUNT);

	// fonts
	m_font = new Font("./bin/font/consolas.ttf", 15);
	m_winFont = new Font("./bin/font/consolas.ttf", 32);
	m_time = 0.0f;

	// graph related
	m_debug = true;
	m_pTextureHighlight = new Texture("./bin/textures/path.png");
	m_pTextureTraversed = new Texture("./bin/textures/agent1.png");
	// create graph nodes with default edge weights (m_pGraph instanciated in member function)
	CreateGraph(false);
	m_random = false;

	// start node contains path start point
	m_pStart = nullptr;

	// path end point
	m_pEnd = nullptr;

	m_step = 0;
	m_time = 0;

	// pathfinding information
	PathFinder * m_pPathfinder = new PathFinder();

	return true;
}
/*******************************************************************************************************
********************************************************************************************************/
void Application2D::shutdown() {

	delete m_font;
	delete m_winFont;
	delete m_pTextureHighlight;
	delete m_pTextureTraversed;
	delete m_spriteBatch;

	destroyWindow();
}
/*******************************************************************************************************
  Update
********************************************************************************************************/
bool Application2D::update(float deltaTime) {
	
	// close the application if the window closes or we press escape
	if (hasWindowClosed() || isKeyPressed(GLFW_KEY_ESCAPE))
		return false;

	// distance to finish
	float finishDis = glm::distance(m_agent->m_movementInfo.m_position, glm::vec2(ROCKET_POS_X, ROCKET_POS_Y));
	if (finishDis < 0.5 && m_agent->endPoint() != nullptr)
	{
		m_finished = true;
	}

	// check for user inputs
	userKeyboardInput();
	userMouseInput();

	if (!m_finished)
	{
		// update player agent
		m_agent->Update(deltaTime);
	}
	else
	{
		m_time += (deltaTime * 20);
	}

	// update seekers if there are any
	if (!(m_wandererAgents.empty()))
	{	
		for (size_t i = 0; i < m_wandererAgents.size(); i++)
		{
			m_wandererAgents[i]->Update(deltaTime);
		}
	}

	// generate a path if nodes selected
	if (m_pStart != nullptr && m_pEnd != nullptr && !m_pathFound)
	{
		// reset edge weights
		resetEdgeWeights();
		// adjust weights
		adjustEgdeWeights();
		// generate path
		generatePath();
	}

	// the applciation closes if we return false
	return true;
}
/*******************************************************************************************************
   Main draw function
********************************************************************************************************/
void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_spriteBatch->begin();

	// winner text
	if (m_finished)
	{
		m_spriteBatch->drawText(m_winFont, "WINNER...!", (float)HALF_SW - 150, (float)HALF_SH);
	}

	// draw base
	m_spriteBatch->drawSprite(m_spBaseTexture.get(), BASE_POS_X, BASE_POS_Y, BASE_SIZE, BASE_SIZE);


	if (m_finished)
	{
		if (m_time < 200)
		{
			// draw rocket
			m_spriteBatch->drawSprite(m_spRocketTexture.get(), ROCKET_POS_X, ROCKET_POS_Y, ROCKET_SIZE + m_time, ROCKET_SIZE + m_time);
			if (m_time < 150)
			{
				// draw flames
				m_spriteBatch->drawSprite(m_spFlamesTexture.get(), ROCKET_POS_X, ROCKET_POS_Y, ROCKET_SIZE - (m_time -5), ROCKET_SIZE - (m_time -5));
			}
		}
	}
	else
	{
		// draw rocket
		m_spriteBatch->drawSprite(m_spRocketTexture.get(), ROCKET_POS_X, ROCKET_POS_Y, ROCKET_SIZE, ROCKET_SIZE);
		// draw player agent
		m_spriteBatch->drawSprite(m_agent->texture(), m_agent->m_movementInfo.m_position.x,
									m_agent->m_movementInfo.m_position.y,
									0, 0, m_agent->m_movementInfo.m_rotation);
	}



	// draw objects
	// -- draw wanderer agents
	if (!(m_wandererAgents.empty()))
	{
		for (size_t i = 0; i < m_wandererAgents.size(); ++i)
		{
			m_spriteBatch->drawSprite(m_wandererAgents[i]->texture(), m_wandererAgents[i]->m_movementInfo.m_position.x,
													     m_wandererAgents[i]->m_movementInfo.m_position.y,
												   0, 0, m_wandererAgents[i]->m_movementInfo.m_rotation);
			// debug wander
			if (m_debug)
			{
				//m_wandererAgents[i]->Draw(m_spriteBatch);
			}
		}
	}

	// -- draw obstacles and ground textures under them
	if (!(m_obstacles.empty()))
	{
		// draw obstacles
		for (size_t i = 0; i < m_obstacles.size(); ++i)
		{
			m_spriteBatch->drawSprite(m_obstacles[i]->texture().get(), 
										m_obstacles[i]->m_configurationInfo.m_vPosition.x,
										m_obstacles[i]->m_configurationInfo.m_vPosition.y,
										m_obstacles[i]->m_configurationInfo.m_fSize, 
										m_obstacles[i]->m_configurationInfo.m_fSize, 
										m_obstacles[i]->m_configurationInfo.m_fRotation);
			// debug wander
			if (m_debug)
			{
				m_obstacles[i]->Draw(m_spriteBatch);
			}
		}
		// draw ground textures under obstacles
		for (size_t i = 0; i < m_obstacles.size(); ++i)
		{
			m_spriteBatch->drawSprite(m_spGroundTexture.get(),
										m_obstacles[i]->m_configurationInfo.m_vPosition.x,
										m_obstacles[i]->m_configurationInfo.m_vPosition.y);
		}
	}

	// draw graph if debug selected
	if (m_debug)
	{
		drawGraph();
	}
	else
	{
		m_pGraph->Draw(m_spriteBatch);
	}
	
	// done drawing sprites
	m_spriteBatch->end();	
}
/*******************************************************************************************************
	Graph Draw function
********************************************************************************************************/
void Application2D::drawGraph()
{
	m_spriteBatch->drawText(m_font, "A = A*, D = Dijkstra, R = Toggle random weights ", 20.0f, 705.0f);

	// draw any text that need to be drawn
	//--------------------------------------
	// let user know what algorithm is in use
	if (m_astar)
	{
		m_spriteBatch->drawText(m_font, "AStar in Use", 20.0f, 5.0f);
	}
	else if (!m_astar)
	{
		m_spriteBatch->drawText(m_font, "Dijkstra in Use", 20.0f, 5.0f);
	}
	// let user know what edge weights are in use
	if (m_random)
	{
		m_spriteBatch->drawText(m_font, " - with RANDOM edge weights", 150.0f, 5.0f);
	}
	else if (!m_random)
	{
		m_spriteBatch->drawText(m_font, " - with DEFAULT edge weights", 150.0f, 5.0f);
	}

	std::string traversed = "Number of nodes traversed = " + std::to_string(m_traversed.size());
	m_spriteBatch->drawText(m_font, traversed.c_str(), 500.0f, 5.0f);

	std::list<Graph::Node*> pPathList = (*m_agent->pathList());
	// draw path if one available
	if (!pPathList.empty() && (pPathList.size() > 1))
	{
		for (auto nit = pPathList.begin(); nit != pPathList.end(); nit++)
		{
			Graph::Node * n2 = *nit;
			m_spriteBatch->drawSprite(m_pTextureHighlight, n2->m_position.x, n2->m_position.y);
		}
	}

	// draw traversed nodes if available
	if (!m_traversed.empty() && (m_traversed.size() > 1))
	{
		for (auto nit = m_traversed.begin(); nit != m_traversed.end(); nit++)
		{
			Graph::Node * n2 = *nit;
			if (n2 != m_pStart)
				m_spriteBatch->drawSprite(m_pTextureTraversed, n2->m_position.x, n2->m_position.y);
		}
	}

	m_pGraph->DrawDebug(m_spriteBatch);
}
/*******************************************************************************************************
	keypressed
********************************************************************************************************/
bool Application2D::keyPressed(int key)
{
	bool keyDown = false;
	bool rtest = false;
	if (isKeyPressed(key))
	{
		if (keyDown)//key down
		{
			rtest = true;
		}
		keyDown = false;
	}
	else
	{
		if (!keyDown)//key up
		{
			rtest = false;
		}
		keyDown = true;
	}
	return keyDown;
}
/*******************************************************************************************************
	mouse clicked
********************************************************************************************************/
bool Application2D::mouseClicked(int button)
{
	return isMouseButtonPressed(button);
}

/*******************************************************************************************************
	cursor position
********************************************************************************************************/
void Application2D::cursorPosition(int& x, int& y)
{
	getCursorPosition(x, y);
}

/*******************************************************************************************************
	user mouse input
********************************************************************************************************/
void Application2D::userMouseInput()
{
	// half distance between nodes
	int nodeGap = NODE_DISTANCE / 2;

	std::list<Graph::Node*> nodeList = m_pGraph->graphNodelist();

	if (mouseClicked(GLFW_MOUSE_BUTTON_1))
	{
		// reset
		m_pGraph->ResetNodes();
		setStartPoint(nullptr);
		setEndPoint(nullptr);
		resetPath();
		// cursor position
		int cursorX = 0;
		int cursorY = 0;
		cursorPosition(cursorX, cursorY);
		// correct Y co-ordinate
		cursorY = SCREEN_H - cursorY;

		std::cout << "X = " << cursorX << " Y = " << cursorY << std::endl;

		// need to find where the player is
		glm::vec2 playerPos = m_agent.get()->m_movementInfo.m_position;

		// **-- STARTNODE
		// check if there is a node at these co-ordinates
		//   loop through list of nodes to find one at those co-ordinates
		for (auto nit = nodeList.begin(); nit != nodeList.end(); nit++)
		{
			Graph::Node * n = *nit;

			// player node pos check
			if (((playerPos.x <= n->m_position.x + nodeGap) && (playerPos.x >= n->m_position.x - nodeGap)) &&
				((playerPos.y <= n->m_position.y + nodeGap) && (playerPos.y >= n->m_position.y - nodeGap)))
			{
				setStartPoint(n);
				n->m_startNode = true;
				m_pGraph->startSelected(true);
				std::cout << "--- set start" << std::endl;
				break;
			}
		}
		// **-- ENDNODE
		// check if there is a node at these co-ordinates
		//   loop through list of nodes to find one at those co-ordinates
		for (auto nit = nodeList.begin(); nit != nodeList.end(); nit++)
		{
			Graph::Node * n = *nit;

			// check if cursor position is within 5 pixels radious of the node
			if (((cursorX <= n->m_position.x + nodeGap) && (cursorX >= n->m_position.x - nodeGap)) &&
				((cursorY <= n->m_position.y + nodeGap) && (cursorY >= n->m_position.y - nodeGap)))
			{
				setEndPoint(n);
				n->m_endNode = true;
				m_pGraph->endSelected(true);
				std::cout << "--- set end" << std::endl;
				break;
			}
		}

	}

	if (mouseClicked(GLFW_MOUSE_BUTTON_2))
	{
		m_pGraph->ResetNodes();
		setStartPoint(nullptr);
		setEndPoint(nullptr);
		resetPath();
		std::cout << "--- reset" << std::endl;
	}
}
/*******************************************************************************************************
	user keyboard input
********************************************************************************************************/
void Application2D::userKeyboardInput()
{
	// randomise edge weights if R is pressed
	if (isKeyPressed(GLFW_KEY_R) && !m_random)
	{
		m_pGraph->ResetNodes(this);
		resetPath();
		CreateGraph(true);
		m_random = true;
		std::cout << "** random edges set **" << std::endl;
	}
	// if R has already been pressed set edges to default weights
	else if (isKeyPressed(GLFW_KEY_R) && m_random)
	{
		m_pGraph->ResetNodes(this);
		resetPath();
		CreateGraph(false);
		m_random = false;
		std::cout << "** edges set to default **" << std::endl;
	}
	// if D pressed use Dijkstras algorithm
	if (isKeyPressed(GLFW_KEY_D))
	{
		m_astar = false;
		std::cout << "## Dijkstra set ##" << std::endl;
	}
	// if A pressed uses AStar algorithm
	if (isKeyPressed(GLFW_KEY_A))
	{
		m_astar = true;
		std::cout << "## ASTAR set ##" << std::endl;
	}
	// if B pressed toggle debug
	if (isKeyPressed(GLFW_KEY_B))
	{
		if (m_debug)
		{
			m_debug = false;
			std::cout << ">> DEBUG ON <<" << std::endl;
			return;
		}
		if (!m_debug)
		{
			m_debug = true;
			std::cout << ">> DEBUG OFF <<" << std::endl;
			return;
		}
	}

}

/*******************************************************************************************************
********************************************************************************************************/
const spPlayerAgent Application2D::getPlayer()
{
	return m_agent;
}

/*******************************************************************************************************
********************************************************************************************************/
const pWandererVector Application2D::getWanderers()
{
	return &m_wandererAgents;
}

/*****************************************************************************************************************
Create Wanderer Objects
******************************************************************************************************************/
void Application2D::CreateWandererAgents(int count)
{
	// add agents to vector
	for (int i = 0; i < count; i++)
	{	
		// push new agent on to the vector, with a random location on the screen
		m_wandererAgents.push_back(std::make_shared<WandererAgent>(glm::vec2((float)(rand() % SCREEN_W), (float)(rand() % SCREEN_H))));
	}
	// set behaviour
	for (size_t i = 0; i < m_wandererAgents.size(); i++)
	{
		m_wandererAgents[i]->m_movementInfo.m_maxSpeed = (float)(rand() % 2 + 0.5);
		m_wandererAgents[i]->m_movementInfo.m_maxAcceleration = (float)(rand() % 4 + 0.5);
		m_wandererAgents[i]->m_movementInfo.m_maxForce = (float)(rand() % 4 + 0.5);
		m_wandererAgents[i]->m_movementInfo.m_livelyness = (float)(rand() % 5 + 1);
		m_wandererAgents[i]->m_movementInfo.m_prevTime = (float)glfwGetTime();
		m_wandererAgents[i]->spriteBatch(m_spriteBatch);
	}
}

/*******************************************************************************************************
********************************************************************************************************/
const pWandererVector Application2D::WandererList()
{
	const  pWandererVector result = &m_wandererAgents;
	return result;
}

/*****************************************************************************************************************
Destroy  Wanderer Objects
******************************************************************************************************************/
void Application2D::DestroyWandererAgents()
{
	m_wandererAgents.clear();
}

/*****************************************************************************************************************
Create Obstacle Objects
******************************************************************************************************************/
void Application2D::CreateObstacles(int count)
{
	// add agents to vector
	for (int i = 0; i < count; i++)
	{
		// push new agent on to the vector, with a random location on the screen
		float obsSize = (float)(rand() % 40 + 20);
		m_obstacles.push_back(std::make_shared<Obstacle>(obsSize));
	}
	// set behaviour
	for (size_t i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->texture(m_obstacleTexture);
	}
}

/*******************************************************************************************************
********************************************************************************************************/
const pObstacleVector Application2D::ObstacleList()
{
	const  pObstacleVector result = &m_obstacles;
	return result;
}

/*****************************************************************************************************************
Destroy Obstacle Objects
******************************************************************************************************************/
void Application2D::DestroyObstacles()
{
	m_obstacles.clear();
}

/*******************************************************************************************************************************
	Create Graph
********************************************************************************************************************************/
void Application2D::CreateGraph(bool randomEdgeWeights)
{
	// delete old Graph if one exists
	if (m_pGraph != nullptr)
	{
		delete m_pGraph;
		m_pGraph = nullptr;
	}

	// instanciate new Graph
	m_pGraph = new Graph();

	const int width = (SCREEN_W / 40);
	const int height = (SCREEN_H / 40);

	// set graph nodes list to a height by width grid
	Graph::Node * nodes[height * width];

	// loop through the height rows
	for (int y = 0; y < height; y++)
	{
		// loop through the width columns
		for (int x = 0; x < width; x++)
		{
			nodes[y * width + x] = m_pGraph->AddNode(glm::vec2(20 + x * NODE_DISTANCE, 20 + y * NODE_DISTANCE));
		}
	}

	// setup grid node connections
	// loop through the height rows
	for (int y = 0; y < height; y++)
	{
		// loop through the width columns
		for (int x = 0; x < width; x++)
		{
			Graph::Node** n = &nodes[y * width + x];

			if (randomEdgeWeights)
			{
				if (x < (width - 1))			m_pGraph->AddConnection(*n, *(n + 1), (float)(rand() % 3) + 1);				// east node
				if (x > 0)						m_pGraph->AddConnection(*n, *(n - 1), (float)(rand() % 3) + 1);				// west node
				// north nodes
				if (y < (height - 1))						m_pGraph->AddConnection(*n, *(n + width), (float)(rand() % 3) + 1);		// north node
				if (y < (height - 1) && x > 0)				m_pGraph->AddConnection(*n, *(n + width - 1), (float)(rand() % 3) + 1);	// north west node
				if (y < (height - 1) && x < (width - 1))	m_pGraph->AddConnection(*n, *(n + width + 1), (float)(rand() % 3) + 1);	// north east node
				// south nodes
				if (y > 0)						m_pGraph->AddConnection(*n, *(n - width), (float)(rand() % 3) + 1);			// south node	
				if (y > 0 && x > 0)				m_pGraph->AddConnection(*n, *(n - width - 1), (float)(rand() % 3) + 1);		// south west node
				if (y > 0 && x < (width - 1))	m_pGraph->AddConnection(*n, *(n - width + 1), (float)(rand() % 3) + 1);		// south east node
			}
			else
			{
				if (x < (width - 1))			m_pGraph->AddConnection(*n, *(n + 1));				// east node
				if (x > 0)						m_pGraph->AddConnection(*n, *(n - 1));				// west node
				// north nodes
				if (y < (height - 1))						m_pGraph->AddConnection(*n, *(n + width));		// north node
				if (y < (height - 1) && x > 0)				m_pGraph->AddConnection(*n, *(n + width - 1));	// north west node
				if (y < (height - 1) && x < (width - 1))	m_pGraph->AddConnection(*n, *(n + width + 1));	// north east node
				// south nodes
				if (y > 0)						m_pGraph->AddConnection(*n, *(n - width));			// south node	
				if (y > 0 && x > 0)				m_pGraph->AddConnection(*n, *(n - width - 1));		// south west node
				if (y > 0 && x < (width - 1))	m_pGraph->AddConnection(*n, *(n - width + 1));		// south east node
			}

		}
	}
	std::list<Graph::Node*> gNodeList = m_pGraph->graphNodelist();
	// set obstacle locations
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		// pick a random node
		int node = (int)(rand() % m_pGraph->graphNodelist().size()) + 1;
		int count = 0;
		// find node and set obstacles position to the same
		for (std::list<Graph::Node*>::iterator iter = gNodeList.begin(); iter != gNodeList.end(); iter++)
		{
			count++;
			if (node == count)
			{
				m_obstacles[i].get()->position((*iter)->m_position);
				m_pGraph->RemoveNode((*iter));
			}
			
		}
	}

}

/*******************************************************************************************************
	retunr closet node to position
********************************************************************************************************/
Graph::Node * Application2D::closetNode(glm::vec2 & position)
{
	// result graph node
	Graph::Node * result = nullptr;

	// half distance between nodes
	int nodeGap = NODE_DISTANCE / 2;
	
	std::list<Graph::Node*> nodeList = m_pGraph->graphNodelist();

	for (auto nit = nodeList.begin(); nit != nodeList.end(); nit++)
	{
		Graph::Node * n = *nit;

		// player node pos check
		if (((position.x <= n->m_position.x + nodeGap) && (position.x >= n->m_position.x - nodeGap)) &&
			((position.y <= n->m_position.y + nodeGap) && (position.y >= n->m_position.y - nodeGap)))
		{
			result = n;
			return result;
		}
	}
	// nullptr check incase agent if off grid
	if (result == nullptr)
	{
		// increase search range
		int nodeGap2 = NODE_DISTANCE;

		for (auto nit = nodeList.begin(); nit != nodeList.end(); nit++)
		{
			Graph::Node * n = *nit;

			// player node pos check
			if (((position.x <= n->m_position.x + nodeGap2) && (position.x >= n->m_position.x - nodeGap2)) &&
				((position.y <= n->m_position.y + nodeGap2) && (position.y >= n->m_position.y - nodeGap2)))
			{
				result = n;
				return result;
			}
		}
	}
}

void Application2D::resetEdgeWeights()
{
	// list of graph nodes
	std::list<Graph::Node*> nodeList = m_pGraph->graphNodelist();
	// reset edge weights
	for (auto i = nodeList.begin(); i != nodeList.end(); i++)
	{
		for (auto e = (*i)->m_connections.begin(); e != (*i)->m_connections.end(); e++)
		{
			(*e).m_cost = 1;
		}
	}
}

void Application2D::adjustEgdeWeights()
{
	// list of graph nodes
	std::list<Graph::Node*> nodeList = m_pGraph->graphNodelist();

	// half distance between nodes
	int nodeGap = NODE_DISTANCE / 2;

	for (auto i = nodeList.begin(); i != nodeList.end(); i++)
	{
		for (auto w = m_wandererAgents.begin(); w != m_wandererAgents.end(); w++)
		{
			float distance = glm::distance((*i)->m_position, (*w)->m_movementInfo.m_position);
			if (distance < nodeGap)
			{
				for (auto e = (*i)->m_connections.begin(); e != (*i)->m_connections.end(); e++)
				{
					(*e).m_cost += NODE_COST_WND;
				}
			}
		}
	}
}

/*******************************************************************************************************
********************************************************************************************************/
void Application2D::setStartPoint(Graph::Node * startNode)
{
	m_pStart = startNode;
}

/*******************************************************************************************************
********************************************************************************************************/
void Application2D::setEndPoint(Graph::Node * endNode)
{
	m_pEnd = endNode;
	m_endNodes.clear();
	m_endNodes.push_back(m_pEnd);
}

/*******************************************************************************************************
	generate path
********************************************************************************************************/
void Application2D::generatePath()
{
	// function assumes path point have already been set, however has protection if not

	if (m_pStart != nullptr && m_pEnd != nullptr && !m_pathFound)
	{
		// if D pressed use Dijkstras algorithm
		if (!m_astar)
		{
			//m_pPathfinder->Dijkstras(m_pStart, m_endNodes, m_path);
			m_pPathfinder->Dijkstras(m_pStart, m_endNodes, m_path, m_traversed);
			m_pathFound = true;
			m_path.reverse();
			m_agent.get()->pathList(m_path);
			m_agent.get()->startPoint(m_pStart);
			m_agent.get()->endPoint(m_pEnd);
			m_path.clear();
		}
		// if A pressed use AStar algorithm
		if (m_astar)
		{
			//m_pPathfinder->AStar(m_pStart, m_pEnd, m_path);
			m_pPathfinder->AStar(m_pStart, m_pEnd, m_path, m_traversed);
			m_pathFound = true;
			m_path.reverse();
			m_agent.get()->pathList(m_path);
			m_agent.get()->startPoint(m_pStart);
			m_agent.get()->endPoint(m_pEnd);
			m_path.clear();
		}
	}
}

/*******************************************************************************************************
	generate path, given points
********************************************************************************************************/
void Application2D::generatePath(Graph::Node * startNode, Graph::Node * endNode)
{
	// clear existing path
	setStartPoint(nullptr);
	setEndPoint(nullptr);
	resetPath();
	m_pGraph->ResetNodes();
	
	// set path points
	setStartPoint(startNode);
	setEndPoint(endNode);

	// if D pressed use Dijkstras algorithm
	if (!m_astar)
	{
		//m_pPathfinder->Dijkstras(m_pStart, m_endNodes, m_path);
		m_pPathfinder->Dijkstras(m_pStart, m_endNodes, m_path, m_traversed);
		m_pathFound = true;
		m_path.reverse();
		m_agent.get()->pathList(m_path);
		m_agent.get()->startPoint(m_pStart);
		m_agent.get()->endPoint(m_pEnd);
		m_path.clear();
	}
	// if A pressed use AStar algorithm
	if (m_astar)
	{
		//m_pPathfinder->AStar(m_pStart, m_pEnd, m_path);
		m_pPathfinder->AStar(m_pStart, m_pEnd, m_path, m_traversed);
		m_pathFound = true;
		m_path.reverse();
		m_agent.get()->pathList(m_path);
		m_agent.get()->startPoint(m_pStart);
		m_agent.get()->endPoint(m_pEnd);
		m_path.clear();
	}
}

/*******************************************************************************************************
********************************************************************************************************/
void Application2D::resetPath()
{
	m_endNodes.clear();
	m_path.clear();
	m_traversed.clear();
	m_pathFound = false;
}

/*******************************************************************************************************
********************************************************************************************************/
std::list<Graph::Node*> Application2D::getPath()
{
	return m_path;
}
