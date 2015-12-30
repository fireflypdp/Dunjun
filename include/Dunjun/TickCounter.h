#ifndef DUNJUN_TICKCOUNTER_H
#define DUNJUN_TICKCOUNTER_H

#include <Dunjun/Clock.h>

namespace Dunjun
{
	class TickCounter
	{
	public:
		b08 Update(f64 frequency)
		{
			b08 reset = false;
			if (m_clock.GetElapsedTime() >= frequency)
			{
				m_tickRate = static_cast<usize>(m_tick / frequency);
				m_tick = 0;
				reset = true;
				m_clock.Restart();
			}

			++m_tick;
			return reset;
		}

		inline usize GetTickRate() const { return m_tickRate; }

	private:
		usize m_tick = 0;
		usize m_tickRate = 0;
		Clock m_clock;
	};
} // namespace Dunjun

#endif//DUNJUN_TICKCOUNTER_H