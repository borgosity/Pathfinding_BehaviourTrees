#include "Action.h"
#include "Behaviours\IBehaviour.h"


Action::Action()
{
	m_behaviour = nullptr;
}

Action::Action(spBehaviour behaviour)
{
	m_behaviour = behaviour;
}

Action::~Action()
{
}

Status Action::execute(Agent * agent)
{
	Status result = m_behaviour.get()->execute(agent);
	return result;
}
