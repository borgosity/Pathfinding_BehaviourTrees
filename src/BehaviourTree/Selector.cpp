#include "Selector.h"

Selector::Selector()
{
	m_pendingChild = m_childBehaviours.end();
}

Selector::~Selector()
{
	clearChildren();
}

Status Selector::execute(Agent * agent)
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
			return BH_SUCCESS;
		}
		if (result == BH_FAILURE)
		{
			child++;
		}
		if (result == BH_PENDING)
		{
			m_pendingChild = child;
			return BH_PENDING;
		}
	}
	return BH_FAILURE;
}

