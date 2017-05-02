#pragma once

class Texture {
public:

	Texture(const char * filename);
	Texture(unsigned int width, unsigned int height, unsigned int * pixels = 0);
	virtual ~Texture();

	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }

	unsigned int getHandle() const { return m_glHandle; }

protected:

	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glHandle;
};