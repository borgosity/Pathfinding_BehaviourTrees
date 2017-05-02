#include "WandererBT.h"
// behaviourTree includes
#include "BehaviourTree\Selector.h"
#include "BehaviourTree\Sequence.h"
#include "BehaviourTree\IBehaviourTree.h"
#include "BehaviourTree\Condition.h"
#include "BehaviourTree\Action.h"


WandererBT::WandererBT()
{
	Init();
}


WandererBT::~WandererBT()
{
}

void WandererBT::Init()
{
	// instaciate a selector node for the top of the tree
	// add children to the selector
	// - add a squence node for wander
	// add conditions and actions to wander sequence node
	// - add condition, with is player in range query
	// - add condition, with is group following player query
	// - add condition, with is agent near obstacle query
	// - add action, wander behaviour
	// - add a sequence node for follow
	// add conditions and actions to follow sequence node
	// - add condition, is player in range
	// - add condition, are there > than 5 wanderers following
	// - add action, follow behaviour

	// add conditions and actions to sequences
	// obstacle sequence
	m_spObstacleSequence.get()->addChild(m_spObstacleCondition);
	m_spObstacleSequence.get()->addChild(m_spObstacleAction);

	// seek sequence
	m_spSeekSequence.get()->addChild(m_spPlayerRangeCondition);
	m_spSeekSequence.get()->addChild(m_spSeekAction);

	// follow wesqence
	m_spFollowSequence.get()->addChild(m_spGroupCondition);
	m_spFollowSequence.get()->addChild(m_spFollowAction);

	// wander sequence
	m_spWanderSequence.get()->addChild(m_spInvertPlayerRange);	// inverted player range
	m_spInvertPlayerRange.get()->addChild(m_spPlayerRangeCondition);
	m_spWanderSequence.get()->addChild(m_spInvertObstacle);		// inverted obstacle
	m_spInvertObstacle.get()->addChild(m_spObstacleCondition);
	m_spWanderSequence.get()->addChild(m_spInvertGroup);		// inverted group
	m_spInvertGroup.get()->addChild(m_spGroupCondition);
	m_spWanderSequence.get()->addChild(m_spWanderAction);		// normal wanderer action

	// add sequences to behaviour tree root selector
	m_spBTroot.get()->addChild(m_spWanderSequence);
	m_spBTroot.get()->addChild(m_spSeekSequence);
	m_spBTroot.get()->addChild(m_spFollowSequence);
	m_spBTroot.get()->addChild(m_spObstacleSequence);

}

Status WandererBT::execute(Agent * agent)
{
	
	return m_spBTroot.get()->execute(agent);
	
}
