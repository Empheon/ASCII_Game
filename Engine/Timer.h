#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();

	void start(void);
	float getElapsedSeconds(bool restart = false);
	unsigned long getElapsedMs(bool restart = false);

private:
	LARGE_INTEGER lastUpdateTime;
	LONGLONG freq;
};