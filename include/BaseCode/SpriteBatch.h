#pragma once

class Texture;
class Font;

class SpriteBatch {
public:

	SpriteBatch();
	virtual ~SpriteBatch();

	// all draw calls must occur between a begin / end pair
	virtual void begin();
	virtual void end();

	// if texture is null then it renders a coloured sprite
	// depth is in the range [0,100] with lower being closer
	virtual void drawSprite(Texture * texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual void drawSpriteTransformed3x3(Texture * texture, float * transformMat3x3, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual void drawSpriteTransformed4x4(Texture * texture, float * transformMat4x4, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);

	// draws a simple coloured line with a given thickness
	// depth is in the range [0,100] with lower being closer
	virtual void drawLine( float x1, float y1, float x2, float y2, float thickness = 1.0f, float depth = 0.0f );

	// draws simple text on the screen horizontally
	// depth is in the range [0,100] with lower being closer
	virtual void drawText(Font * font, const char* text, float xPos, float yPos, float depth = 0.0f);

	// sets the colour of sprites for all subsequent draw calls
	void setSpriteColor(float r, float g, float b, float a);

	// can be used to set the texture coordinates of sprites using textures
	// for all subsequent drawSprite calls
	void setUVRect(float uvX, float uvY, float uvW, float uvH);

protected:

	// helper methods used during drawing
	bool shouldFlush();
	void flushBatch();
	unsigned int pushTexture(Texture* texture);

	// indicates in the middle of a begin/end pair
	bool				m_renderBegun;

	// texture handling
	enum { TEXTURE_STACK_SIZE = 16 };
	Texture*			m_nullTexture;
	Texture*			m_textureStack[TEXTURE_STACK_SIZE];
	int					m_fontTexture[TEXTURE_STACK_SIZE];
	unsigned int		m_currentTexture;

	// texture coordinate information
	float				m_uvX, m_uvY, m_uvW, m_uvH;

	// sprite colour
	float				m_r, m_g, m_b, m_a;

	// sprite handling
	enum { MAX_SPRITES = 512 };
	struct SBVertex {
		float pos[4];
		float color[4];
		float texcoord[2];
	};

	SBVertex			m_vertices[MAX_SPRITES*4];
	unsigned short		m_indices[MAX_SPRITES*6];
	int					m_currentVertex, m_currentIndex;
	unsigned int		m_vao, m_vbo, m_ibo;

	// shader used to render sprites
	unsigned int		m_shader;

	// helper method used to rotate sprites around a pivot
	void	rotateAround(float inX, float inY, float& outX, float& outY, float sin, float cos);
};