#pragma once
#include "IBehaviour.h"
#include "Graph.h"
#include <memory>
#include <list>

class SeekBehaviour;

class PathBehaviour :
	public IBehaviour
{
public:
	PathBehaviour();
	~PathBehaviour();

	virtual Status execute(Agent * agent);
	virtual void Update(float deltaTime, MovementInfo & agentMI);
	void seek(float deltaTime, MovementInfo & agentMI);
	void pursue(float deltaTime, MovementInfo & agentMI);
	virtual void Draw(MovementInfo * agentMI) { return; }
	virtual BehaviourName behaviourType() { return BH_PATH; }

	std::list<Graph::Node*> pathNodeList();

private:
	std::list<Graph::Node*>::iterator m_liTarget;
	std::list<Graph::Node*> m_pathNodeList;
	std::shared_ptr<SeekBehaviour> m_spSeekBehaviour;
	float	m_fWeight;
	glm::vec2 m_velocity;
	glm::vec2 m_distance;
};

