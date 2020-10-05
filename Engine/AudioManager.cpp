#include "AudioManager.h"

AudioManager& AudioManager::Instance() {
	static AudioManager instance;
	return instance;
}

void AudioManager::Play(std::wstring file, bool loop) {
	if (!audioEnabled)
		return;

	Stop(file);

	std::wstringstream command;
	command << "play " << file;
	if (loop) {
		command << " repeat";
	}
	mciSendString(command.str().c_str(), nullptr, 0, nullptr);
}

void AudioManager::Stop(std::wstring file) {
	if (!audioEnabled)
		return;
	
	std::wstringstream command;
	command << "stop " << file;
	mciSendString(command.str().c_str(), nullptr, 0, nullptr);
}