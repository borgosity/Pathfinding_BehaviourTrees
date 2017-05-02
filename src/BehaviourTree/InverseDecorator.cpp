#include "BehaviourTree\InverseDecorator.h"

InverseDecorator::InverseDecorator()
{
	m_child = nullptr;
}

InverseDecorator::InverseDecorator(spChild btChildNode)
{
	m_child = btChildNode;
}

InverseDecorator::~InverseDecorator()
{
}

void InverseDecorator::addChild(spChild btChildNode)
{
	m_child = btChildNode;
}

Status InverseDecorator::execute(Agent * agent)
{
	Status result = m_child.get()->execute(agent);
	switch (result)
	{
	case BH_INVALID:
		return BH_INVALID;
	case BH_SUCCESS:
		return BH_FAILURE;
	case BH_FAILURE:
		return BH_SUCCESS;
	case BH_PENDING:
		return BH_PENDING;
	case BH_ABORTED:
		return BH_ABORTED;
	default:
		break;
	}
}
