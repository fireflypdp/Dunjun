#include <Dunjun/Common.h>
#include <Dunjun/Image.h>
#include <Dunjun/ShaderProgram.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <string>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	f32 vertices[] = {
		//	x		y		r		g		b		s		t
		-0.5f,	-0.5f,	 1.0f,	 0.0f,	 0.0f,	0.0f,	0.0f, // vertex 0
		+0.5f,	-0.5f,	 0.0f,	 1.0f,	 0.0f,	1.0f,	0.0f, // vertex 1
		-0.5f,	+0.5f,	 0.0f,	 0.0f,	 1.0f,	0.0f,	1.0f, // vertex 2
		+0.5f,	+0.5f,	 1.0f,	 1.0f,	 1.0f,	1.0f,	1.0f, // vertex 3
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
	shaderProgram.AttachShaderFromFile(ShaderType::Vertex, "data/shaders/default.vert.glsl");
	shaderProgram.AttachShaderFromFile(ShaderType::Fragment, "data/shaders/default.frag.glsl");
	shaderProgram.BindAttributeLocation(0, "vertPosition");
	shaderProgram.BindAttributeLocation(1, "vertColor");
	shaderProgram.BindAttributeLocation(2, "vertTexCoord");
	shaderProgram.Link();
	shaderProgram.Use();

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Image image;
	image.LoadFromFile("data/textures/peter_jpgAvatar.jpg");

	// checkerboard pattern
	f32 pixels[] = {
		0, 0, 1,	1, 0, 0,
		0, 1, 0,	1, 1, 0,
	};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.GetWidth(), image.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetPixelPtr());

	glActiveTexture(GL_TEXTURE0);
	shaderProgram.SetUniform("uniTex", 0);

	bool isRunning = true;
	bool isFullscreen = false;
	while (isRunning)
	{
		{
			s32 viewportWidth, viewportHeight;
			glfwGetWindowSize(window, &viewportWidth, &viewportHeight);
			glViewport(0, 0, viewportWidth, viewportHeight);
		}

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw things
		{
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
