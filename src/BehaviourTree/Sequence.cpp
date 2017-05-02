#include "Sequence.h"

Sequence::Sequence()
{
	m_pendingChild = m_childBehaviours.end();
}

Sequence::~Sequence()
{
	clearChildren();
}

Status Sequence::execute(Agent * agent)
{
	childBehaviourList::iterator child = m_pendingChild;
	m_pendingChild = m_childBehaviours.end();

	if (child == m_childBehaviours.end())
	{
		child = m_childBehaviours.begin();
	}

	// Keep going until a child behavior says its running.
	while (child != m_childBehaviours.end())
	{
		Status result = child->get()->execute(agent);
		if (result == BH_SUCCESS)
		{
			child++;
		}
		if (result == BH_FAILURE)
		{
			return BH_FAILURE;
		}
		if (result == BH_PENDING)
		{
			m_pendingChild = child;
			return BH_PENDING;
		}
	}
	return BH_SUCCESS;
}

