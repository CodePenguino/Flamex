#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window() = default;
	Window(uint32_t width, uint32_t height, const char* title, bool fullscreen = false);
	void create(uint32_t width, uint32_t height, const char* title, bool fullscreen = false);
	~Window();

	void update();
	void loop();
	void set_callbacks(void (*procInputs)(void), void (*upd)(void));
	void set_icon(const char* filePath);

	inline bool is_closed() const { return glfwWindowShouldClose(handle); }
	inline void set_background_color(float r, float g, float b) const { glClearColor(r, g, b, 1.0f); }
	inline void set_background_color(float r, float g, float b, float a) const { glClearColor(r, g, b, a); }
	inline void set_attrib(int attrib, int value) const { glfwSetWindowAttrib(handle, attrib, value); };
	inline void close() const { glfwSetWindowShouldClose(handle, true); }

	glm::ivec2 size;
	float aspect_ratio;
	GLFWwindow* handle;

private:
	void (*m_processInputsCallback)(void);
	void (*m_updateCallback)(void);
};

static Window window;
