#include "Timer.h"

namespace Utilities {

	// Create a Timer singleton pointer and set it to null
	Timer* Timer::sInstance = nullptr;

	// If the singleton Timer pointer is null, create a new Timer
	Timer* Timer::Instance() {
		if (sInstance == nullptr) {
			sInstance = new Timer();
		}
		return sInstance;
	}

	// Function to delete timer
	void Timer::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	Timer::Timer() {
		Reset();
		mTimeScale = 1.0f;
		mDeltaTime = std::chrono::duration<float>(0.0f);
	}

	// default destructor
	Timer::~Timer() {};

	// Reset the clock's 'start' timer
	void Timer::Reset() {
		mStartTime = std::chrono::system_clock::now();
	}

	// return delta time
	float Timer::DeltaTime() {
		return mDeltaTime.count();
	}

	// set the time scale
	void Timer::TimeScale(float t) {
		mTimeScale = t;
	}

	// return the timescale
	float Timer::TimeScale() {
		return mTimeScale;
	}


	void Timer::Tick() {
		mDeltaTime = std::chrono::system_clock::now() - mStartTime;
	}
}

