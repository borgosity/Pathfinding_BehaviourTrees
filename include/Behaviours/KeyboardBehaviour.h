#pragma once

#include "IBehaviour.h"

class KeyboardBehaviour : 
	public IBehaviour
{
public:
	KeyboardBehaviour();
	~KeyboardBehaviour();

	Status execute(Agent * agent);
	void Update(float deltaTime, MovementInfo & movementInfo);
	virtual void Draw(MovementInfo * behaviour) { return; }
	virtual BehaviourName behaviourType() { return BH_KEYBOARD; }

private:

};

