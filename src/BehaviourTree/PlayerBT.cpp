#include "PlayerBT.h"
// behaviourTree includes
#include "BehaviourTree\Selector.h"
#include "BehaviourTree\Sequence.h"
#include "BehaviourTree\IBehaviourTree.h"
#include "BehaviourTree\Condition.h"
#include "BehaviourTree\Action.h"
#include "BehaviourTree\ActionNewPath.h"

PlayerBT::PlayerBT()
{
	Init();
}


PlayerBT::~PlayerBT()
{
}

void PlayerBT::Init()
{
	// add conditions and actions to sequences
	// Waiting sequence
	m_spWaitingSequence.get()->addChild(m_spWaitingAction);

	// arrival sequence
	m_spPlayerArrivalSequence.get()->addChild(m_spPlayerArrivalCondition);
	m_spPlayerArrivalSequence.get()->addChild(m_spPlayerArrivalAction);

	// path sequence
	m_spPathSequence.get()->addChild(m_spPathCondition);
	m_spPathSequence.get()->addChild(m_spPathAction);

	// new path sequence
	m_spNewPathSequence.get()->addChild(m_spNewPathCondition);
	m_spNewPathSequence.get()->addChild(m_spNewPathAction);
	m_spNewPathSequence.get()->addChild(m_spPathCondition);
	m_spNewPathSequence.get()->addChild(m_spPathAction);

	// Evade sequence
	m_spEvadeSequence.get()->addChild(m_spWandererRangeCondition);
	m_spEvadeSequence.get()->addChild(m_spEvadeAction);

	// add sequences to behaviour tree root selector
	m_spBTroot.get()->addChild(m_spEvadeSequence);			// 1- evade wanderers
	m_spBTroot.get()->addChild(m_spPlayerArrivalSequence);	// 2- arrive at destination
	m_spBTroot.get()->addChild(m_spPathSequence);			// 3- follow path
	m_spBTroot.get()->addChild(m_spNewPathSequence);		// 4- new path
	m_spBTroot.get()->addChild(m_spWaitingSequence);		// 5- wait 

}

Status PlayerBT::execute(Agent * agent)
{
	
	return m_spBTroot.get()->execute(agent);
	
}
