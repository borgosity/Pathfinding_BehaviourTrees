#pragma once
#include "BehaviourTree\IBehaviourTree.h"
#include "BehaviourTree\InverseDecorator.h"
// behaviour includes
#include "Behaviours\WaitingBehaviour.h"
#include "Behaviours\PathBehaviour.h"
#include "Behaviours\EvadeBehaviour.h"
#include "Behaviours\ArrivalBehaviour.h"
// query includes
#include "Queries\PathQuery.h"
#include "Queries\PathNewQuery.h"
#include "Queries\WandererRangeQuery.h"
#include "Queries\PlayerArrivalQuery.h"



class Selector;
class Sequence;
class Condition;
class Action;
class ActionNewPath;

class PlayerBT : public IBehaviourTree
{
public:
	typedef std::shared_ptr<Selector> spSelector;
	typedef std::shared_ptr<Sequence> spSequence;
	typedef std::shared_ptr<Condition> spCondition;
	typedef std::shared_ptr<Action> spAction;
	typedef std::shared_ptr<InverseDecorator> spInverseDecorator;

	PlayerBT();
	~PlayerBT();

	void Init();
	virtual Status execute(Agent * agent);

	// behaviour and query member variables
	// behaviours
	std::shared_ptr<PathBehaviour> m_spPathBehaviour		= std::make_shared<PathBehaviour>();
	std::shared_ptr<ArrivalBehaviour> m_spArrivalBehaviour	= std::make_shared<ArrivalBehaviour>();
	std::shared_ptr<EvadeBehaviour> m_spEvadeBehaviour		= std::make_shared<EvadeBehaviour>();
	std::shared_ptr<WaitingBehaviour> m_spWaitingBehaviour	= std::make_shared<WaitingBehaviour>();
	
	// queries
	std::shared_ptr<PathQuery> m_spPathQuery					= std::make_shared<PathQuery>();
	std::shared_ptr<PathNewQuery> m_spNewPathQuery				= std::make_shared<PathNewQuery>();
	std::shared_ptr<PlayerArrivalQuery> m_spArrivalQuery		= std::make_shared<PlayerArrivalQuery>();
	std::shared_ptr<WandererRangeQuery> m_spWandererRangeQuery	= std::make_shared<WandererRangeQuery>();

	// behaviour tree root
	spSelector	m_spBTroot = std::make_shared<Selector>();

	// Path member variables
	// sequence
	spSequence m_spPathSequence = std::make_shared<Sequence>();
	// conditions
	spCondition m_spPathCondition = std::make_shared<Condition>(m_spPathQuery);
	// action
	spAction m_spPathAction = std::make_shared<Action>(m_spPathBehaviour);

	// New Path member variables
	// sequence
	spSequence m_spNewPathSequence = std::make_shared<Sequence>();
	// conditions
	spCondition m_spNewPathCondition = std::make_shared<Condition>(m_spNewPathQuery);
	// new path action
	std::shared_ptr<ActionNewPath> m_spNewPathAction = std::make_shared<ActionNewPath>();
	// path action
	// -- uses existing defined path action

	// Arrival member variables
	// sequence
	spSequence m_spPlayerArrivalSequence = std::make_shared<Sequence>();
	// conditions
	spCondition m_spPlayerArrivalCondition = std::make_shared<Condition>(m_spArrivalQuery);
	// action
	spAction m_spPlayerArrivalAction = std::make_shared<Action>(m_spArrivalBehaviour);

	// Evade member variables
	// sequence
	spSequence	m_spEvadeSequence = std::make_shared<Sequence>();
	// conditions
	spCondition m_spWandererRangeCondition = std::make_shared<Condition>(m_spWandererRangeQuery);
	// action
	spAction m_spEvadeAction = std::make_shared<Action>(m_spEvadeBehaviour);

	// Waiting member variables
	// sequence
	spSequence m_spWaitingSequence = std::make_shared<Sequence>();
	// conditions
	// -- no contition, just action if everything else fails
	// action
	spAction m_spWaitingAction = std::make_shared<Action>(m_spWaitingBehaviour);


};

