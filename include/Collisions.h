#pragma once
#include <memory>

class Agent;

bool IsColliding(std::shared_ptr<Agent> agentA, std::shared_ptr<Agent> agentB);
bool IsColliding(Agent * agentA, Agent * agentB);
