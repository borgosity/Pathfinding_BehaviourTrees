#pragma once
#include "BehaviourTree\IBehaviourTree.h"
#include "BehaviourTree\InverseDecorator.h"
// behaviour includes
#include "Behaviours\WanderBehaviour.h"
#include "Behaviours\SeekBehaviour.h"
#include "Behaviours\FollowBehaviour.h"
#include "Behaviours\AvoidanceBehaviour.h"
// query includes
#include "Queries\CountQuery.h"
#include "Queries\ObstacleQuery.h"
#include "Queries\PlayerRangeQuery.h"
#include "Queries\WandererRangeQuery.h"
#include "Queries\StatusQuery.h"


class Selector;
class Sequence;
class Condition;
class Action;

class WandererBT : public IBehaviourTree
{
public:
	typedef std::shared_ptr<Selector> spSelector;
	typedef std::shared_ptr<Sequence> spSequence;
	typedef std::shared_ptr<Condition> spCondition;
	typedef std::shared_ptr<Action> spAction;
	typedef std::shared_ptr<InverseDecorator> spInverseDecorator;

	WandererBT();
	~WandererBT();

	void Init();
	virtual Status execute(Agent * agent);

	// behaviour and query member variables
	// behaviours
	std::shared_ptr<SeekBehaviour> m_spSeekBehaviour = std::make_shared<SeekBehaviour>();
	std::shared_ptr<FollowBehaviour> m_spFollowBehaviour = std::make_shared<FollowBehaviour>();
	std::shared_ptr<WanderBehaviour> m_spWanderBehaviour = std::make_shared<WanderBehaviour>();
	std::shared_ptr<AvoidanceBehaviour> m_spAvoidBehaviour = std::make_shared<AvoidanceBehaviour>();
	// queries
	std::shared_ptr<CountQuery> m_spCountQuery = std::make_shared<CountQuery>();
	std::shared_ptr<ObstacleQuery> m_spObstacleQuery = std::make_shared<ObstacleQuery>();
	std::shared_ptr<PlayerRangeQuery> m_spPlayerRangeQuery = std::make_shared<PlayerRangeQuery>();
	std::shared_ptr<StatusQuery> m_spStatusQuery = std::make_shared<StatusQuery>();

	// behaviour tree root
	spSelector	m_spBTroot = std::make_shared<Selector>();

	// Wander member variables
	// sequence
	spSequence	m_spWanderSequence = std::make_shared<Sequence>();
	// conditions
	spCondition m_spPlayerRangeCondition	 = std::make_shared<Condition>(m_spPlayerRangeQuery);
	spInverseDecorator m_spInvertPlayerRange = std::make_shared<InverseDecorator>();
	spCondition m_spObstacleCondition		 = std::make_shared<Condition>(m_spObstacleQuery);
	spInverseDecorator m_spInvertObstacle	 = std::make_shared<InverseDecorator>();
	spCondition m_spGroupCondition			 = std::make_shared<Condition>(m_spCountQuery);
	spInverseDecorator m_spInvertGroup		 = std::make_shared<InverseDecorator>();
	// action
	spAction m_spWanderAction = std::make_shared<Action>(m_spWanderBehaviour);

	// Seek member variables
	// sequence
	spSequence m_spSeekSequence = std::make_shared<Sequence>();
	// conditions
	// -- reuse player in range condition
	// action
	spAction m_spSeekAction = std::make_shared<Action>(m_spSeekBehaviour);

	// Follow member variables
	// sequence
	spSequence m_spFollowSequence = std::make_shared<Sequence>();
	// conditions
	// -- reuse group condition
	// action
	spAction m_spFollowAction = std::make_shared<Action>(m_spFollowBehaviour);

	// Obstacle member variables
	// sequence
	spSequence m_spObstacleSequence = std::make_shared<Sequence>();
	// conditions
	// -- uses already defined m_spObstacleCondition
	// action
	spAction m_spObstacleAction = std::make_shared<Action>(m_spAvoidBehaviour);
};

