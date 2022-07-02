#pragma once

#include "window.hpp"
#include <glm/glm.hpp>

#define NUM_JOYSTICKS 8

struct Joystick
{
	int status;
	int num_axes;
	int num_buttons;
	
	const float* axes;
	const unsigned char* buttons;
	const char* name;
};

namespace Input
{
	static Joystick joystick[NUM_JOYSTICKS];

	// ---------------------------
	// Keyboard input
	// ---------------------------

	static inline bool key_pressed(int keyCode)
	{
		// NOTE: This is a pretty dumb way to do this, since it needs to have a window attached to every input, but it works.
		return glfwGetKey(window.handle, keyCode);
	}

	static inline bool mouse_pressed(int button)
	{
		return glfwGetMouseButton(window.handle, button);
	}

	template <typename A, typename B>
	static inline void axis(A& val, const B& amt, int incr, int decr)
	{
		val += (key_pressed(incr) - key_pressed(decr)) * amt;
	}

	template <typename A, typename B>
	static inline void set_axis(A& val, const B& amt, int incr, int decr)
	{
		val = (key_pressed(incr) - key_pressed(decr)) * amt;
	}

	// ---------------------------
	// Joystick input
	// ---------------------------
	
	/*static inline void set_joystick_status()
	{
		for(uint8_t i = 0; i < NUM_JOYSTICKS; i++)
		{
			joystick[i].status = glfwJoystickPresent(i);
		}
	}*/

	static inline void update_joysticks()
	{
		for (uint8_t i = 0; i < NUM_JOYSTICKS; i++)
		{
			joystick[i].status = glfwJoystickPresent(i);
			
			if (joystick[i].status == GLFW_TRUE)
			{
				joystick[i].axes = glfwGetJoystickAxes(i, &joystick[i].num_axes);
				joystick[i].buttons = glfwGetJoystickButtons(i, &joystick[i].num_buttons);
				joystick[i].name = glfwGetJoystickName(i);
			}
		}
	}
};
