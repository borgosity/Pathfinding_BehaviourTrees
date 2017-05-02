#include "Composite.h"
#include <algorithm>

void Composite::addChild(spIBehaviourBT child)
{
	m_childBehaviours.push_back(child);
}

void Composite::removeChild(spIBehaviourBT child)
{
	m_childBehaviours.erase(std::remove(m_childBehaviours.begin(), m_childBehaviours.end(), child), m_childBehaviours.end());
}

void Composite::clearChildren()
{
	for(childBehaviourList::iterator it = m_childBehaviours.begin(); it != m_childBehaviours.end(); it++) {
		//delete it;
	}
	m_childBehaviours.clear();
}
