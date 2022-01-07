#pragma once

#include "Constants.h"

namespace Engine
{
	class Window
	{
	public:
		GLFWwindow *_window;
		int _width;
		int _height;
		bool _is_fullscreen;

		static Window *create_window(int width = 1280, int height = 720, const char *title = "Untitled", bool fullScreenMode = false);
		static void free_window(Window *window);
		void set_handlers();
		void close();
	};
}