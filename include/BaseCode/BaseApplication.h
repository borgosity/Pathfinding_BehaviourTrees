#pragma once

struct GLFWwindow;

class BaseApplication {
public:

	BaseApplication() {}
	virtual ~BaseApplication() {}

	void run();
	
	virtual bool startup() = 0;
	virtual void shutdown() = 0;

	virtual bool update(float deltaTime) = 0;
	virtual void draw() = 0;

protected:

	virtual bool createWindow(const char* title, int width, int height);
	virtual void destroyWindow();

	bool isKeyPressed(int key);

	bool isMouseButtonPressed(int button);
	void getCursorPosition(int& x, int& y);

	bool hasWindowClosed();

	void clearScreen();
	void setBackgroundColour(float r, float g, float b);

	GLFWwindow*	m_window;
};