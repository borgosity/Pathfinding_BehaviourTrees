#pragma once
#include <glm\glm.hpp>
#include "Agent.h"


class PlayerBT;
typedef std::shared_ptr<Texture> spTexture;

class PlayerAgent :
	public Agent
{
public:
	typedef std::shared_ptr<IBehaviour> spBehaviour;
	typedef std::shared_ptr<PlayerBT> spPlayerBT;

	PlayerAgent();
	PlayerAgent(float positionX, float positionY, float size = 10.0f);
	PlayerAgent(glm::vec2 position, float size = 10.0f);
	virtual ~PlayerAgent();

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
	float size();							// returns PlayerAgent size
	float size(float newSize);				// sets and returns PlayerAgent size
	
	int state();							// returns PlayerAgent state
	int state(int newState);				// sets and returns PlayerAgent state

	SpriteBatch * spriteBatch();							// returns spritebactch
	SpriteBatch * spriteBatch(SpriteBatch * spriteBatch); // sets and returns spritebactch

	Texture * texture();					// returns PlayerAgent texture
	Texture * texture(Texture *	texture);	// sets and returns PlayerAgent texture

	// update
	virtual void Update(float deltaTime);
	virtual void Draw(SpriteBatch * spriteBatch);

protected:
	spPlayerBT		m_spPlayerBT = std::make_shared<PlayerBT>();
	spBehaviour		m_spCurrentBehaviour;
	Texture *		m_texture;
	spTexture		m_pathTexture;
	spTexture		m_waitTexture;
	spTexture		m_evadeTexture;

private:
	void Init(glm::vec2 position, float size);



	

};

