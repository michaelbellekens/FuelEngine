#include "FuelEnginePCH.h"
#include "SoundManager.h"

#include "Logger.h"

SoundManager::SoundManager()
{
	Initialize();
}

SoundManager::~SoundManager()
{
	for (const std::pair<std::string, SoundData>& sound : m_pSounds)
	{
		sound.second.SoundSample->release();
	}
	
	if (m_pFmodSystem)
	{
		m_pFmodSystem->close();
		m_pFmodSystem->release();
	}
}

void SoundManager::AddSound(const std::string& soundName, const std::string& assetFile, const bool canPlayOnCreation, const bool canLoop)
{
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		m_pSounds.emplace_back(soundName, SoundData());

		const int soundMode = canLoop ? FMOD_LOOP_NORMAL | FMOD_2D : FMOD_DEFAULT;
		FMOD_RESULT result = m_pFmodSystem->createSound(assetFile.c_str(), soundMode, nullptr, &m_pSounds.back().second.SoundSample);

		if (!ErrorCheck(result))
			m_pSounds.erase(m_pSounds.end() - 1);

		if (canPlayOnCreation)
		{
			result = m_pFmodSystem->playSound(m_pSounds.back().second.SoundSample, nullptr, false, &m_pSounds.back().second.Channel);
			ErrorCheck(result);
		}
	}
}

void SoundManager::StartSound(const std::string& soundName, const bool checkIfPlaying)
{
	if (m_IsMuted)
		return;
	
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		fuel::Logger::LogWarning("Can't find sound with name \"" + soundName + "\" in SoundManager!");
		return;
	}

	if (checkIfPlaying)
	{
		bool isPlaying;
		(*it).second.Channel->isPlaying(&isPlaying);
		if (isPlaying)
			return;
	}
	
	const FMOD_RESULT result = m_pFmodSystem->playSound((*it).second.SoundSample, nullptr, false, &(*it).second.Channel);
	ErrorCheck(result);
	SetVolumeSound(soundName, (*it).second.Volume);
}

void SoundManager::StopSound(const std::string& soundName)
{
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		fuel::Logger::LogWarning("Can't find sound with name \"" + soundName + "\" in SoundManager!");
		return;
	}

	if (PauseSound((*it).second.Channel))
	{
		(*it).second.Channel->setPosition(0, FMOD_TIMEUNIT_MS);
		(*it).second.Channel->stop();
	}
}

void SoundManager::PauseSound(const std::string& soundName)
{
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		fuel::Logger::LogWarning("Can't find sound with name \"" + soundName + "\" in SoundManager!");
		return;
	}

	const FMOD_RESULT result = (*it).second.Channel->setPaused(true);
	ErrorCheck(result);
}

bool SoundManager::PauseSound(FMOD::Channel* channel)
{
	if (channel == nullptr)
		return false;

	channel->setPaused(true);
	return true;
}

void SoundManager::StopAllSounds()
{
	for (const std::pair<std::string, SoundData>& sound : m_pSounds)
	{
		StopSound(sound.first);
	}
}

void SoundManager::SetVolumeSound(const std::string& soundName, const float volume)
{
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		fuel::Logger::LogWarning("Can't find sound with name \"" + soundName + "\" in SoundManager!");
		return;
	}

	(*it).second.Volume = volume;
	(*it).second.Channel->setVolume(volume);
}

void SoundManager::SetMute(const bool isMuted)
{
	m_IsMuted = isMuted;
	for (const std::pair<std::string, SoundData>& sound : m_pSounds)
	{
		sound.second.Channel->setMute(isMuted);
	}
}

void SoundManager::ToggleMute()
{
	SetMute(!m_IsMuted);
}

#pragma warning(push)
#pragma warning(disable: 26812)
bool SoundManager::ErrorCheck(FMOD_RESULT res)
{
	if (res != FMOD_OK)
	{
		std::stringstream strstr;
		strstr << "FMOD error! \n[" << res << "] " << FMOD_ErrorString(res) << std::endl;
		fuel::Logger::LogError(strstr.str());
		return false;
	}

	return true;
}
#pragma warning(pop)

void SoundManager::Initialize()
{
	unsigned int version;
	int numdrivers;

	/*
	Create a System object and initialize.
	*/
	FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
	ErrorCheck(result);
	result = m_pFmodSystem->getVersion(&version);
	ErrorCheck(result);

	if (version < FMOD_VERSION)
	{
		fuel::Logger::LogWarning("SoundManager Initialization Failed!\n\nYou are using an old version of FMOD %08x. This program requires %08x\n");
		return;
	}

	result = m_pFmodSystem->getNumDrivers(&numdrivers);
	ErrorCheck(result);
	if (numdrivers == 0)
	{
		result = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ErrorCheck(result);
	}
	else
	{
		result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		ErrorCheck(result);
	}

}

bool SoundManager::CheckIfSoundExists(const std::string& soundName, std::pair<std::string, SoundData>& soundData) const
{
	const auto it = std::find_if(m_pSounds.begin(), m_pSounds.end(), [soundName](const std::pair<std::string, SoundData>& soundData) { return soundData.first == soundName; });

	if (it == m_pSounds.end())
	{
		fuel::Logger::LogWarning("Can't find sound with name \"" + soundName + "\" in SoundManager!");
		soundData = std::pair<std::string, SoundData>();
		return false;
	}

	soundData = *it;
	return true;
}
