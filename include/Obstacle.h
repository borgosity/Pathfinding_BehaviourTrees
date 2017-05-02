#pragma once
#include <glm\glm.hpp>
#include <memory>

class Texture;
class SpriteBatch;
struct Node;

typedef glm::vec2 Vector2;
typedef std::shared_ptr<Texture> spTexture;

struct ConfigurationInfo
{

	Vector2	  m_vPosition;
	
	float	  m_fSize;
	float	  m_fRadius;
	float	  m_fMass;
	float	  m_fRotation;

	spTexture m_texture;
};

class Obstacle
{
public:
	Obstacle();
	Obstacle(float size = 10.0f);
	Obstacle(float positionX, float positionY, float size = 10.0f);
	Obstacle(Vector2 position, float size = 10.0f);
	virtual ~Obstacle();

	// get/set overloads
	Vector2 position();					// returns obstacle position
	Vector2 position(Vector2 position);	// sets and returns obstacle position

	float size();							// returns obstacle size
	float size(float newSize);				// sets and returns obstacle size
	
	float radius();							// returns obstacle radius
	float radius(float radius);				// sets and returns obstacle radius

	float mass();							// returns obstacle mass
	float mass(float radius);				// sets and returns obstacle mass

	spTexture texture();					// returns obstacle texture
	spTexture texture(spTexture	texture);	// sets and returns obstacle texture

	// update
	void Update(float deltaTime);
	void Draw(SpriteBatch * spriteBatch);

	ConfigurationInfo m_configurationInfo;

	int m_nodeLocation;

private:
	void Init(float positionX, float positionY, float size);
	void Init(Vector2 position, float size);

};

