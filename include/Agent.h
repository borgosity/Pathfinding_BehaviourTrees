#pragma once
#include <glm\glm.hpp>
#include <memory>
#include <list>
#include "Graph.h"

class IBehaviour;
class IBehaviourTree;
class Texture;
class SpriteBatch;
class Obstacle;
class Agent;

typedef std::shared_ptr<Obstacle> spObstacle;
typedef std::shared_ptr<Agent> spAgent;

struct MovementInfo
{

	glm::vec2 m_position;
	glm::vec2 m_sensor;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	glm::vec2 m_heading;
	
	float m_maxSpeed;
	float m_maxAcceleration;
	float m_maxForce;
	float m_livelyness; // used to determine delay between wander updates
	float m_prevTime; //used in wander delay

	float m_sight;
	
	float m_rotation;
	float m_rotationDampening;

	SpriteBatch * m_spriteBatch; //used if needed to draw some stuff
};

class Agent
{
public:
	virtual ~Agent();

	// gets
	inline float GetPostionX() { return m_movementInfo.m_position.x; }
	inline float GetPostionY() { return m_movementInfo.m_position.y; }
	inline IBehaviour * GetBehaviour() { return m_currentBehaviour; }

	// sets
	inline void SetBehaviour(IBehaviour * behaviour)
	{
		m_currentBehaviour = behaviour;
	}
	// get/set overloads
	float size();							// returns agent size
	float size(float newSize);				// sets and returns agent size
	
	int state();							// returns agent state
	int state(int newState);				// sets and returns agent state

	SpriteBatch * spriteBatch();							// returns spritebactch
	SpriteBatch * spriteBatch(SpriteBatch * spriteBatch); // sets and returns spritebactch

	Texture * texture();					// returns agent texture
	Texture * texture(Texture *	texture);	// sets and returns agent texture

	Graph::Node * startPoint();
	Graph::Node * startPoint(Graph::Node * startPoint);

	Graph::Node * endPoint();
	Graph::Node * endPoint(Graph::Node * endPoint);

	std::list<Graph::Node*> * pathList();
	std::list<Graph::Node*> * pathList(std::list<Graph::Node*> pathList);

	spObstacle closetObstacle();							// returns agent obstac;e
	spObstacle closetObstacle(spObstacle closestObstacle);	// sets and returns agent obstacle 

	spAgent closetAgent();							// returns agent obstac;e
	spAgent closetAgent(spAgent closestAgent);	// sets and returns agent Agent 

	void offScreen();

	// update
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteBatch * spriteBatch) = 0;
	MovementInfo m_movementInfo;

protected:
	IBehaviour * m_BehaviourTree;
	Texture *	 m_texture;

	IBehaviour * m_currentBehaviour;
	spObstacle	 m_spClosestObstacle;
	spAgent		 m_spClosetAgent;
	float		 m_size;
	int			 m_state;

	Graph::Node * m_startPoint;
	Graph::Node * m_endPoint;
	std::list<Graph::Node*> m_pathList;
	

};

