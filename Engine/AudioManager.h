#pragma once

#include <iostream>
#include <sstream>
#include <Windows.h>

class AudioManager
{
public:
	static AudioManager& Instance();
	void Play(std::wstring file, bool loop = false);
	void Stop(std::wstring file);

private:
	bool audioEnabled = true;
	AudioManager() {};
};

