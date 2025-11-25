#pragma once
#include <string>
#include <SDL3/SDL_audio.h>
#include <unordered_map>
#include <SDL3/SDL_stdinc.h>

struct SoundData {
	SDL_AudioStream* stream = nullptr;
	Uint8* wav;
	Uint32 wav_len;
};

class SoundManager
{
private:
	inline static bool isInit;
	inline static std::unordered_map<std::string, SoundData*> loaded_sounds;

	inline static std::string baseSoundsPath = "/assets/sounds/";

	static bool LoadWAV(std::string);

public:
	~SoundManager();
	static SoundData* GetSound(std::string);
	static bool PlaySound(std::string, float gain = 1.0);
	static void StopAll();
	void LoadAllSounds();

	bool IsInit() { return isInit; }
};

