#include "window.hpp"
#include <iostream>
#include "time.h"
#include "../rendering/stb_image.h"

// Callback functions
void resize_callback(GLFWwindow* win, int width, int height)
{
	glViewport(0,0,width,height);
}

Window::Window(uint32_t width, uint32_t height, const char* title, bool fullscreen)
{
	create(width, height, title, fullscreen);
}

void Window::create(uint32_t width, uint32_t height, const char* title, bool fullscreen)
{
	size.x = width;
	size.y = height;
	aspect_ratio = (float)size.x/size.y;

	if(!glfwInit())
	{
		std::cerr << "Error: Failed to initialize GLFW!\n";
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	handle = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

	if(!handle)
	{
		std::cerr << "Error: Failed to initialize GLFW window!\n";
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(handle);
	glfwSetFramebufferSizeCallback(handle, resize_callback);

	//if(glewInit() != GLEW_OK)
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error: GLEW failed to initialize!\n";
		glfwDestroyWindow(handle);
		glfwTerminate();
		exit(1);
	}

	// Alpha channel color blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Backface culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwDestroyWindow(handle);
	glfwTerminate();
}

void Window::set_callbacks(void (*procInputs)(void), void (*upd)(void))
{
	m_processInputsCallback = procInputs;
	m_updateCallback = upd;
}

void Window::loop()
{
	// Error check. If we don't exit, we might get some "segmentation fault" errors on Linux
	if(m_processInputsCallback == nullptr)
	{
		std::cerr << "Error: Process inputs function is invalid!\n";
		exit(1);
	}

	if(m_updateCallback == nullptr)
	{
		std::cerr << "Error: Update function is invalid!\n";
		exit(1);
	}

	while(!glfwWindowShouldClose(handle))
	{
		m_processInputsCallback();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_updateCallback();

		glfwGetWindowSize(handle, &size.x, &size.y);
		aspect_ratio = (float)size.x/size.y;

		glfwSwapBuffers(handle);
		glfwPollEvents();
	}
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(handle);
}

void Window::set_icon(const char* filePath)
{
	GLFWimage icon[1];
	icon[0].pixels = stbi_load(filePath, &icon[0].width, &icon[0].height, 0, 0);
	glfwSetWindowIcon(handle, 1, icon);
	stbi_image_free(icon[0].pixels);
}
