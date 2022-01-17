#include "core/Input.h"

namespace TUNA
{
	namespace Input
	{
		bool keypress_data[GLFW_KEY_LAST] = {};
		bool mouse_button_data[GLFW_MOUSE_BUTTON_LAST] = {};
		float mouse_x = 0.0f;
		float mouse_y = 0.0f;
		float mouse_scroll_x = 0.0f;
		float mouse_scroll_y = 0.0f;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			if (key >= 0 && key < GLFW_KEY_LAST)
			{
				keypress_data[key] = action == GLFW_PRESS;
			}
		}

		void curser_callback(GLFWwindow *window, double xpos, double ypos)
		{
			mouse_x = (float)xpos;
			mouse_y = (float)ypos;
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
			{
				mouse_button_data[button] = action == GLFW_PRESS;
			}
		}

		void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
		{
			mouse_scroll_x = (float)xoffset;
			mouse_scroll_y = (float)yoffset;
		}

		bool is_key_down(int key)
		{
			if (key >= 0 && key < GLFW_KEY_LAST)
			{
				return keypress_data[key];
			}

			return false;
		}

		bool is_mouse_button_down(int mouseButton)
		{
			if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST)
			{
				return mouse_button_data[mouseButton];
			}

			return false;
		}
	}
}