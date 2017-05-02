#include "BaseApplication.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

bool BaseApplication::createWindow(const char* title, int width, int height) {

	if (glfwInit() == GL_FALSE)
		return false;

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow*, int w, int h){ glViewport(0, 0, w, h); });

	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	return true;
}

void BaseApplication::destroyWindow() {

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void BaseApplication::run() {

	double prevTime = glfwGetTime();
	double currTime = 0;

	while (currTime = glfwGetTime(),
		update((float)(currTime - prevTime))) {

		glfwPollEvents();
		draw();
		glfwSwapBuffers(m_window);

		prevTime = currTime;
	}
}

bool BaseApplication::isKeyPressed(int key) {
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool BaseApplication::isMouseButtonPressed(int button) {
	return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

void BaseApplication::getCursorPosition(int& x, int& y) {
	double dx = 0, dy = 0;
	glfwGetCursorPos(m_window, &dx, &dy);
	x = (int)dx; y = (int)dy;
}

bool BaseApplication::hasWindowClosed() {
	return glfwWindowShouldClose(m_window) == GL_TRUE;
}

void BaseApplication::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void BaseApplication::setBackgroundColour(float r, float g, float b) {
	glClearColor(r, g, b, 1);
}