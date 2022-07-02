#pragma once

#include <GLFW/glfw3.h>
#include "../common/types.hpp"
#include <thread>
#include <chrono>

namespace Time
{
	static float now, last, delta;
	static u64 ticks;
	static u32 fps_limit;

	// NOTE: Initialized to 0 to mark there is not a limit
	// Initialize time
	static inline void init(u32 fps = 0)
	{
		fps_limit = fps;
		last = 0;
		ticks = 0;
	}

	// Updates all the time variables
	static inline void update()
	{
		now = static_cast<float>(glfwGetTime());
		delta = now - last;
	
		// If there is an fps limit, make stuff happen
		if(fps_limit != 0)
		{
			// TODO: This is pretty dumb, calculate how long to sleep thread instead.
			while(glfwGetTime() < last + 1.0f/fps_limit)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	
		last = now;
		ticks++;
	}

	// Returns the FPS
	static inline float get_fps()
	{
		return 1.0f / delta;
	}
};
