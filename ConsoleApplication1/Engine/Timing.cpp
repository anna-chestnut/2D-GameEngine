#include "Timing.h"

#include <Windows.h>

#include <assert.h>
#include <limits.h>

namespace Engine {

	namespace Timing {

		unsigned int LastFrame_ms;

		LARGE_INTEGER PerformanceFrequency = { 0 };

		void Init() {
			BOOL bSuccess = QueryPerformanceFrequency(&PerformanceFrequency);
			assert(bSuccess);
		}

		tick_t GetCurrentTickCounter() {

			LARGE_INTEGER CurrentFrameCounter;

			BOOL success = QueryPerformanceCounter(&CurrentFrameCounter);
			assert(success);

			return CurrentFrameCounter.QuadPart;

		}

		float GetTimeDiff_ms(tick_t i_StartTick, tick_t i_EndTick) {
			assert(PerformanceFrequency.QuadPart != 0);
			return (1000.0f * static_cast<float>(i_StartTick - i_EndTick)) / PerformanceFrequency.QuadPart;
		}

		//Bootstrapper TimingBootstrapper(std::bind(Init), std::function<void()>());
	}
}