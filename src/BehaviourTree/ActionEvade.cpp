#include "ActionEvade.h"
#include "Behaviours\IBehaviour.h"


ActionEvade::ActionEvade()
{
	m_behaviour = nullptr;
}

ActionEvade::ActionEvade(spBehaviour behaviour)
{
	m_behaviour = behaviour;
}

ActionEvade::~ActionEvade()
{
}

Status ActionEvade::execute(Agent * agent)
{
	 Status result = m_behaviour.get()->execute(agent);
	 return result;
}
