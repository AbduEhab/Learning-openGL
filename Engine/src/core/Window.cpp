#include "core/Window.h"
#include "core/Input.h"

namespace Engine
{
	void Window::set_handlers()
	{
		if (_window != nullptr)
		{
			glfwSetKeyCallback(_window, Input::key_callback);
			glfwSetCursorPosCallback(_window, Input::curser_callback);
			glfwSetScrollCallback(_window, Input::mouse_scroll_callback);
			glfwSetMouseButtonCallback(_window, Input::mouse_button_callback);
		}
	}

	void Window::close()
	{
		if (_window != nullptr)
		{
			glfwSetWindowShouldClose(_window, GLFW_TRUE);
		}
	}
	Window *Window::create_window(int width, int height, const char *title, bool fullScreenMode)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		Window *res = new Window();

		GLFWmonitor *primaryMonitor = fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;

		res->_window = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);

		res->_is_fullscreen = fullScreenMode;

		if (res->_window == nullptr)
		{
			printf("Failed to create GLFW window\n");
			glfwTerminate();
			return nullptr;
		}

		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(res->_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		res->set_handlers();

		glfwMakeContextCurrent(res->_window);

		return res;
	}

	void Window::free_window(Window *window)
	{
		if (window)
		{
			glfwDestroyWindow(window->_window);
			delete window;
		}
	}
}
