#pragma once
#include "IBehaviourTree.h"
#include <memory>


class InverseDecorator : public IBehaviourTree
{
public:
	typedef std::shared_ptr<IBehaviourTree> spChild;

	InverseDecorator();
	InverseDecorator(spChild btChildNode);
	virtual ~InverseDecorator();

	void addChild(spChild btChildNode);
	virtual Status execute(Agent * agent);

protected:
	spChild m_child;
};


