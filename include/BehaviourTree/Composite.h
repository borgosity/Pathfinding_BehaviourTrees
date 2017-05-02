#pragma once
#include "IBehaviourTree.h"
#include <list>
#include <memory>


class Composite : public IBehaviourTree
{
public:
	typedef std::shared_ptr<IBehaviourTree> spIBehaviourBT;
	typedef std::shared_ptr<IBehaviourTree> spPendingChild;
	
	void addChild(spIBehaviourBT child);
	void removeChild(spIBehaviourBT child);
	void clearChildren();

protected:
	typedef std::list<spIBehaviourBT> childBehaviourList;

	childBehaviourList m_childBehaviours;
	childBehaviourList::iterator m_pendingChild;
};

