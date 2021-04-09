#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
//you can also use ifndef for the converting.
//cons of using #define MILLI_TO_SEC, this doesnt take up any place in memmory.
//Try to use this instead.
	constexpr float MILLI_TO_SEC = 1000.0f;

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator = (const Timer&) = delete;
	Timer& operator = (Timer&&) = delete;
	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;
private:
	//We use unsigned int for more time
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif