#include "SoundManager.h"
#include <iostream>
#include <SDL3/SDL_oldnames.h>

bool SoundManager::LoadWAV(std::string soundName)
{
	SDL_AudioSpec spec;
	SoundData* data = new SoundData();
	std::string sound_path;
#ifdef __EMSCRIPTEN__
	sound_path = baseSoundsPath + soundName + ".wav";
#else
	sound_path = "." + baseSoundsPath + soundName + ".wav"; // Desktop path
#endif

	if (!SDL_LoadWAV(sound_path.c_str(), &spec, &data->wav, &data->wav_len)) {
		std::cout << "Error loading wav : " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_AudioStream* stream;
	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
	if (!stream) {
		std::cout << "Error creating the audio stream : " << SDL_GetError() << std::endl;
		return false;
	}
	data->stream = stream;

	loaded_sounds.insert({ soundName, data });
	return true;
}

SoundManager::~SoundManager()
{
	for (auto& sound : loaded_sounds) {
		SDL_free(sound.second->wav);
		delete sound.second;
	}
}

SoundData* SoundManager::GetSound(std::string soundName)
{
	if (!isInit) {
		std::cout << "Sound Manager not yet initialized" << std::endl;
		return nullptr;
	}

	auto sound = loaded_sounds.find(soundName);
	if (sound != loaded_sounds.end())
		return sound->second;

	if (LoadWAV(soundName)) {
		return GetSound(soundName);
	}

	return nullptr;
}

bool SoundManager::PlaySound(std::string soundName, float gain)
{
	auto soundData = GetSound(soundName);
	if (!soundData) {
		std::cout << "No data found for : " + soundName << std::endl;
		return false;
	}
	SDL_ClearAudioStream(soundData->stream);
	SDL_SetAudioStreamGain(soundData->stream, gain);
	SDL_PutAudioStreamData(soundData->stream, soundData->wav, soundData->wav_len);
	return SDL_ResumeAudioStreamDevice(soundData->stream);
}

void SoundManager::StopAll()
{
	for (auto& sound : loaded_sounds) {
		SDL_ClearAudioStream(sound.second->stream);
	}
}

void SoundManager::LoadAllSounds()
{
	LoadWAV("clap");
	LoadWAV("step_1");
	LoadWAV("step_2");
	LoadWAV("step_3");
	LoadWAV("pick_up_key");

	isInit = true;
}
