#include "Obstacle.h"
#include "SpriteBatch.h"
#include <cmath>
#include <glm\glm.hpp>
// dependencies includes
#include <GLFW/glfw3.h>

typedef glm::vec2 Vector2;

#define M_PI       3.14159265358979323846

Obstacle::Obstacle()
{
	Init(0.0f, 0.0f, 10.0f);
}

Obstacle::Obstacle(float size)
{
	Init(0.0f, 0.0f, size);
}


Obstacle::Obstacle(float positionX, float positionY, float size)
{
	Init(positionX, positionY, size);
}

Obstacle::Obstacle(Vector2 position, float size)
{
	Init(position, size);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime)
{
	// TODO, not a whole lot
	// maybe update texture if it has been run into

}

void Obstacle::Draw(SpriteBatch * spriteBatch)
{
	// draw obstacle circle
	double slice = 2 * M_PI / 360;
	glm::vec2 point1(0.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		double angle = slice * i;
		Vector2 point2(m_configurationInfo.m_vPosition.x + m_configurationInfo.m_fRadius * cos(angle),
					   m_configurationInfo.m_vPosition.y + m_configurationInfo.m_fRadius * sin(angle));

		if (point1.x == 0 && point1.y == 0)
		{
			point1 = point2;
		}
		spriteBatch->drawLine(point1.x, point1.y, point2.x, point2.y);
		point1 = point2;
	}
}

float Obstacle::size()
{
	return m_configurationInfo.m_fSize;
}

float Obstacle::size(float newSize)
{
	m_configurationInfo.m_fSize = newSize;
	return m_configurationInfo.m_fSize;
}

float Obstacle::radius()
{
	return 0.0f;
}

float Obstacle::radius(float radius)
{
	return 0.0f;
}

float Obstacle::mass()
{
	return 0.0f;
}

float Obstacle::mass(float radius)
{
	return 0.0f;
}

spTexture Obstacle::texture()
{
	return m_configurationInfo.m_texture;
}

spTexture Obstacle::texture(spTexture texture)
{
	m_configurationInfo.m_texture = texture;

	return m_configurationInfo.m_texture;
}

void Obstacle::Init(float positionX, float positionY, float size)
{
	m_configurationInfo.m_vPosition.x = positionX;
	m_configurationInfo.m_vPosition.y = positionY;
	m_configurationInfo.m_fSize = size;
	m_configurationInfo.m_fRadius = (m_configurationInfo.m_fSize) / 2;
	m_configurationInfo.m_fMass = (m_configurationInfo.m_fSize) * 2;
	m_configurationInfo.m_fRotation = (float)(rand() % 360 + 1) * M_PI / 2;
}

void Obstacle::Init(Vector2 position, float size)
{
	m_configurationInfo.m_vPosition = position;
	m_configurationInfo.m_fSize = size;
	m_configurationInfo.m_fRadius = (m_configurationInfo.m_fSize) / 2;
	m_configurationInfo.m_fMass = (m_configurationInfo.m_fSize) * 2;
	m_configurationInfo.m_fRotation = (float)(rand() % 360 + 1) * M_PI / 2;
}

Vector2 Obstacle::position()
{
	return m_configurationInfo.m_vPosition;
}

Vector2 Obstacle::position(Vector2 position)
{
	m_configurationInfo.m_vPosition = position;
	return m_configurationInfo.m_vPosition;
}
