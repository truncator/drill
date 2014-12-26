#include "input.hpp"

void Input::Initialize(GLFWwindow* window)
{
	assert(window != nullptr);
	g_window = window;
}

bool Input::IsKeyDown(int key)
{
	return glfwGetKey(g_window, key) == GLFW_PRESS;
}
