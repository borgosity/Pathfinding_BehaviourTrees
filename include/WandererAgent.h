#pragma once
#include "Agent.h"
#include <memory>
#include <list>

class WandererBT;
typedef std::shared_ptr<Texture> spTexture;

class WandererAgent : 
	public Agent
{
public:
	typedef std::shared_ptr<IBehaviour> spBehaviour;
	typedef std::shared_ptr<WandererBT> spWandererBT;

	WandererAgent();
	WandererAgent(float positionX, float positionY, float size = 10.0f);
	WandererAgent(glm::vec2 position, float size = 10.0f);
	~WandererAgent();

	// gets
	inline float GetPostionX() { return m_movementInfo.m_position.x; }
	inline float GetPostionY() { return m_movementInfo.m_position.y; }
	inline IBehaviour * GetBehaviour() { return m_currentBehaviour; }

	// sets
	inline void SetBehaviour(IBehaviour * behaviour)
	{
		m_currentBehaviour = behaviour;
	}
	// get/set overloads
	float size();							// returns WandererAgent size
	float size(float newSize);				// sets and returns WandererAgent size
	
	int state();							// returns WandererAgent state
	int state(int newState);				// sets and returns WandererAgent state

	SpriteBatch * spriteBatch();							// returns spritebactch
	SpriteBatch * spriteBatch(SpriteBatch * spriteBatch); // sets and returns spritebactch

	Texture * texture();					// returns WandererAgent texture
	Texture * texture(Texture *	texture);	// sets and returns WandererAgent texture

	// update
	virtual void Update(float deltaTime);
	virtual void Draw(SpriteBatch * spriteBatch);

protected:
	spWandererBT	m_spWandererBT = std::make_shared<WandererBT>();
	spBehaviour		m_spCurrentBehaviour;
	Texture *		m_texture;
	spTexture		m_wanderTexture;
	spTexture		m_seekTexture;
	spTexture		m_fleeTexture;


private:
	void Init(glm::vec2 position, float size);


	

};

