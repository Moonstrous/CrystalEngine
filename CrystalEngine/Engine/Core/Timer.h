#pragma once
#include <chrono>

/*
	Reference Timer API design :
	Timer timer;
	timer.start();
	timer.now();
	timer.stop();
	timer.reset();
*/


namespace Crystal {
	namespace Core {
		class Timer
		{
			std::chrono::time_point<std::chrono::high_resolution_clock> start;
			std::chrono::time_point<std::chrono::high_resolution_clock> end;
		public:
			void Start();
			double Now();
			void Stop();
			void Reset();
		};
	}
}