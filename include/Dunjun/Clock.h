#ifndef DUNJUN_CLOCK_H
#define DUNJUN_CLOCK_H

#include <GLFW/glfw3.h>

#include <Dunjun/Types.h>

namespace Dunjun
{
	class Clock
	{
	public:
		Clock()
			: m_startTime(glfwGetTime())
		{
		}

		f64 GetElapsedTime() const
		{
			return glfwGetTime() - m_startTime;
		}

		f64 Restart()
		{
			f64 now = glfwGetTime();
			f64 elapsed = GetElapsedTime();
			m_startTime = now;
			return elapsed;
		}

	private:
		f64 m_startTime;
	};
} // namespace Dunjun

#endif//DUNJUN_CLOCK_H