#include <Dunjun/Common.h>
#include <Dunjun/Math.h>
#include <Dunjun/ShaderProgram.h>
#include <Dunjun/Texture.h>
#include <Dunjun/TickCounter.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace Dunjun;

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

// todo: ppascoal - config settings
GLOBAL const b08 CONFIG_VSYNC = true;

INTERNAL void glfwHints()
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

INTERNAL void Render()
{
	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0); // "vertPosition"
	glEnableVertexAttribArray(1); // "vertColor"
	glEnableVertexAttribArray(2); // "vertTexCoord"

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), (const GLvoid*)(2 * sizeof(f32)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), (const GLvoid*)(5 * sizeof(f32)));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0); // "vertPosition"
	glDisableVertexAttribArray(1); // "vertColor"
	glDisableVertexAttribArray(2); // "vertTexCoord"
}

INTERNAL void HandleInput(GLFWwindow * window, b08 & isRunning, b08 & isFullscreen)
{
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

struct Vertex
{
	Vector2 position;
	Vector3 color;
	Vector2 texCoord;
};

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
	if (CONFIG_VSYNC)
		glfwSwapInterval(1);

	glewInit();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Vertex vertices[] = {
		//	x		y			r		g		b		s		t
		{{-0.5f,	-0.5f},	 {1.0f,	 0.0f,	 0.0f},	{0.0f,	1.0f}}, // vertex 0
		{{+0.5f,	-0.5f},	 {0.0f,	 1.0f,	 0.0f},	{1.0f,	1.0f}}, // vertex 1
		{{-0.5f,	+0.5f},	 {0.0f,	 0.0f,	 1.0f},	{0.0f,	0.0f}}, // vertex 2
		{{+0.5f,	+0.5f},	 {1.0f,	 1.0f,	 1.0f},	{1.0f,	0.0f}}, // vertex 3
	};

	GLuint vbo; // vertex buffer object (puts vertices onto the graphics card memory)
	glGenBuffers(1, &vbo); // create 1 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	/* Draw type usage
	GL_STATIC_DRAW - vertex data will only be uploaded once (useful for world/background/etc)
	GL_DYNAMIC_DRAW - vertex data changed but drawn more often than changed
	GL_STREAM_DRAW - vertex data changed almost every frame (UI?  something constantly animating)
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderProgram shaderProgram;
	if (!shaderProgram.AttachShaderFromFile(ShaderType::Vertex, "data/shaders/default.vert.glsl"))
	{
		throw std::runtime_error(shaderProgram.GetErrorLog());
	}
	if (!shaderProgram.AttachShaderFromFile(ShaderType::Fragment, "data/shaders/default.frag.glsl"))
	{
		throw std::runtime_error(shaderProgram.GetErrorLog());
	}
	shaderProgram.BindAttributeLocation(0, "vertPosition");
	shaderProgram.BindAttributeLocation(1, "vertColor");
	shaderProgram.BindAttributeLocation(2, "vertTexCoord");
	if (!shaderProgram.Link())
	{
		throw std::runtime_error(shaderProgram.GetErrorLog());
	}
	shaderProgram.Use();

	Texture tex;
	tex.LoadFromFile("data/textures/peter_jpgAvatar.jpg");
	tex.Bind(0);
	shaderProgram.SetUniform("uniTex", 0);

	b08 isRunning = true;
	b08 isFullscreen = false;

	TickCounter tc;
	Clock frameClock;

	while (isRunning)
	{
		// reshape
		{
			s32 viewportWidth, viewportHeight;
			glfwGetWindowSize(window, &viewportWidth, &viewportHeight);
			glViewport(0, 0, viewportWidth, viewportHeight);
		}

		std::stringstream titleStream;
		if (tc.Update(0.5f))
		{
			titleStream.str("");
			titleStream.clear();
			titleStream << "Dunjun - " << 1000.0 / tc.GetTickRate() << " ms";
			glfwSetWindowTitle(window, titleStream.str().c_str());
		}

		Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		HandleInput(window, isRunning, isFullscreen);

		// throttle framerate
		while (frameClock.GetElapsedTime() < 1.0f / 240.0f) {}
		frameClock.Restart();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
