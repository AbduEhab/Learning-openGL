#pragma once

#include "Constants.h"

namespace TUNA
{
	namespace Input
	{
		extern bool keypress_data[GLFW_KEY_LAST];
		extern bool mouse_button_data[GLFW_MOUSE_BUTTON_LAST];
		extern float mouse_x;
		extern float mouse_y;
		extern float mouse_scroll_x;
		extern float mouse_scroll_y;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void curser_callback(GLFWwindow *window, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

		bool is_key_down(int key);
		bool is_mouse_button_down(int mouseButton);
	}
}
