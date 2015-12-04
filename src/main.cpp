#include <Dunjun/Common.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

void glfwHints()
{
	// OpenGL 2.0 - GLSL 1.10 (OpenGL Shading Language)
	// OpenGL 2.1 - GLSL 1.20
	// OpenGL 3.0 - GLSL 1.30
	// OpenGL 3.1 - GLSL 1.40
	// OpenGL 3.2 - GLSL 1.50
	// OpenGL 3.3 - GLSL 3.30

	// OpenGL v2.1
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

using namespace Dunjun;

int main(int argc, char** argv)
{
	GLFWwindow * window;

	if (!glfwInit())
		return EXIT_FAILURE;

	glfwHints();
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	f32 vertices[] = {
		+0.0f, +0.5f, // vertex 1
		-0.5f, -0.5f, // vertex 2
		+0.5f, -0.5f, // vertex 3
	};

	GLuint vbo; // vertex buffer object (puts vertices onto the graphics card memory)
	glGenBuffers(1, &vbo); // create 1 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Draw type usage
	GL_STATIC_DRAW - vertex data will only be uploaded once (useful for world/background/etc)
	GL_DYNAMIC_DRAW - vertex data changed but drawn more often than changed
	GL_STREAM_DRAW - vertex data changed almost every frame (UI?  something constantly animating)
	*/

	const char * vertexShaderText = {
		"#version 120\n"
		"\n"
		"attribute vec2 position;"
		"void main()"
		"{"
		"	gl_Position = vec4(position, 0.0, 1.0);"
		"}"
	};

	const char * fragmentShaderText = {
		"#version 120\n"
		"\n"
		"void main()"
		"{"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"}"
	};

	// vertex shader passes in vertex data during rendering
	// OpenGL handles shape assembly from vertex data and rasterization (pixellation of data)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	// fragment shader colors rasterized data during rendering
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	// create a shader program to link vertex and fragment shaders together
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// set up attribute locations so we can bind it later
	glBindAttribLocation(shaderProgram, 0, "position");

	// link all shaders together into this program
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	bool isRunning = true;
	bool isFullscreen = false;
	while (isRunning)
	{
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw things
		{
			glEnableVertexAttribArray(0); // "position"

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr); // define "position"

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0); // "position"
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
			isRunning = false;

		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			isFullscreen = !isFullscreen;

			GLFWwindow * newWindow = nullptr;
			glfwHints();

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
