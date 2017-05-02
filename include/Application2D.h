#pragma once

#include "BaseApplication.h"
#include <vector>
#include <memory>
#include "Graph.h"

class SpriteBatch;
class Texture;
class Font;
class PlayerAgent;
class WandererAgent;
class Obstacle;
class Agent;
class PathFinder;

typedef std::shared_ptr<PlayerAgent> spPlayerAgent;
typedef std::shared_ptr<WandererAgent> spWandererAgent;
typedef std::shared_ptr<Texture> spTexture;
typedef std::shared_ptr<Obstacle> spObstacle;

typedef std::vector<spWandererAgent> * pWandererVector;
typedef std::vector<spObstacle> * pObstacleVector;

class Application2D : public BaseApplication {
public:

	Application2D();
	virtual ~Application2D();

	static Application2D * getInstance() { return m_instance; }

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();
	void drawGraph();

	// input member functions
	bool keyPressed(int key);
	bool mouseClicked(int button);
	void cursorPosition(int& x, int& y);
	void userMouseInput();
	void userKeyboardInput();

	const spPlayerAgent getPlayer();
	const pWandererVector getWanderers();

	void CreateWandererAgents(int count);
	const pWandererVector WandererList();
	void DestroyWandererAgents();

	void CreateObstacles(int count);
	const pObstacleVector ObstacleList();
	void DestroyObstacles();

	// graph stuff
	// graph member functions
	void CreateGraph(bool randomEdgeWeights);
	Graph::Node * closetNode(glm::vec2 & position);
	void resetEdgeWeights();
	void adjustEgdeWeights();

	// path member functions
	void setStartPoint(Graph::Node * startNode);
	void setEndPoint(Graph::Node * endNode);
	void generatePath(); 
	void generatePath(Graph::Node * startNode, Graph::Node * endNode);
	std::list<Graph::Node*> getPath();
	void resetPath();

protected:

	SpriteBatch *	m_spriteBatch;
	spPlayerAgent	m_agent;
	Font*			m_font;
	Font*			m_winFont;
	spTexture		m_agentTexture;
	spTexture		m_obstacleTexture;
	spTexture		m_spGroundTexture;
	spTexture		m_spBaseTexture;
	spTexture		m_spRocketTexture;
	spTexture		m_spFlamesTexture;

	// agent member variables
	std::vector<spWandererAgent>	m_wandererAgents;
	std::vector<spObstacle>			m_obstacles;

	// graph stuff
	Texture *				m_pTextureHighlight;
	Texture *				m_pTextureTraversed;
	Graph *					m_pGraph = nullptr;

	Graph::Node *			m_pStart;
	Graph::Node *			m_pEnd;

	std::list<Graph::Node*>	m_endNodes;
	std::list<Graph::Node*>	m_path;
	std::list<Graph::Node*>	m_traversed;

	int						m_step;
	bool					m_astar = true;
	bool					m_pathFound = false;

	PathFinder *			m_pPathfinder;


private:
	static Application2D * m_instance;
	bool m_random;
	float m_time;
	bool m_debug;
	bool m_finished;

};