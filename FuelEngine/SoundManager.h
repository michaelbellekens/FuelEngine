#pragma once
#include "Singleton.h"

class SoundManager: public fuel::Singleton<SoundManager>
{
	struct SoundData
	{
		SoundData()
			: SoundSample(nullptr)
			, Channel(nullptr)
			, Volume(1.f)
		{}
		
		FMOD::Sound* SoundSample;
		FMOD::Channel* Channel;
		float Volume;
	};
	
public:
	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) noexcept = delete;
	SoundManager();
	virtual ~SoundManager();

	void AddSound(const std::string& soundName, const std::string& assetFile, const bool canPlayOnCreation = false, const bool canLoop = false);
	void StartSound(const std::string& soundName, const bool checkIfPlaying = false);
	void StopSound(const std::string& soundName);
	void PauseSound(const std::string& soundName);
	bool PauseSound(FMOD::Channel* channel);

	void StopAllSounds();

	void SetVolumeSound(const std::string& soundName, const float volume);
	void ToggleMute();
	void SetMute(const bool isMuted);

	static bool ErrorCheck(FMOD_RESULT res);
	FMOD::System* GetSystem() const { return m_pFmodSystem; }

private:
	void Initialize();
	bool CheckIfSoundExists(const std::string& soundName, std::pair<std::string, SoundData>& soundData) const;
	
	FMOD::System* m_pFmodSystem = nullptr;
	std::vector<std::pair<std::string, SoundData>> m_pSounds{};
	bool m_IsMuted{ false };
};

