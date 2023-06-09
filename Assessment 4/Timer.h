#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

// credit to Ather Omar's YouTube channel for the implementation of this timer. I spent hours, hours and more hours tryign to find an understandable C++ timer on the internet, and couldn't, they were simply too complicated for me to understand. This timer was a good learning opportunity for me to develop my understanding by commenting through the code to see if I could follow what was happening, but I did not design this from the ground up. I tried to understand the chrono library but it was more than I could follow.
// https://www.youtube.com/watch?v=Vyt-dM8gTRQ

namespace Utilities {

	class Timer {

	private:
		// define a Timer singleton instance
		static Timer* sInstance;

		std::chrono::system_clock::time_point mStartTime;
		std::chrono::duration<float> mDeltaTime;
		float mTimeScale;

	public:
		static Timer* Instance();	// Create a new pointer to a new timer
		static void Release();		// Function to delete timer pointer
		void Reset();				// Function to set 'start' time
		float DeltaTime();			// Function to return the delta time
		void TimeScale(float t);	// set time scale
		float GetTimeScale();		// return the timescale
		void Tick();				// move the timer forward

	private:
		Timer();
		~Timer();
	};
}

#endif