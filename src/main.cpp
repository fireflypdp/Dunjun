#include <Dunjun/Common.h>

#include <GLFW/glfw3.h>

#include <iostream>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

using namespace Dunjun;

int main(int argc, char** argv)
{
	GLFWwindow * window;

	if (!glfwInit())
		return EXIT_FAILURE;

	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	bool isRunning = true;
	bool isFullscreen = false;
	while (isRunning)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
			isRunning = false;

		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			isFullscreen = !isFullscreen;

			GLFWwindow * newWindow = nullptr;
			if (isFullscreen)
			{
				s32 count;
				const GLFWvidmode * modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
				if (modes)
				{
					// count - 1 = highest resolution (fullscreen)
					newWindow = glfwCreateWindow(modes[count - 1].width, modes[count - 1].height, "Dunjun", glfwGetPrimaryMonitor(), window);
				}
			}
			else
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);

			if (newWindow)
			{
				glfwDestroyWindow(window);
				window = newWindow;
				glfwMakeContextCurrent(window);
			}
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
