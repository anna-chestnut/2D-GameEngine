#pragma once

#include <stdint.h>

namespace Engine {
	namespace Timing {
		typedef uint64_t tick_t;

		void Init();

		tick_t GetCurrentTickCounter();
		float GetTimeDiff_ms(tick_t i_StartTick, tick_t i_EndTick = GetCurrentTickCounter());

		//inline float CvtSecondsToMilliseconds(float i_Seconds);
		//inline float CvtPerSecondToMillisecond(float i_PerSecond);
	}
}