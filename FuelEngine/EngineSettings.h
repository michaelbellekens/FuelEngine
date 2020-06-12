#pragma once
#include "Singleton.h"
//#include "Time.h"

namespace fuel
{
	class EngineSettings : public Singleton<EngineSettings>
	{
	public:
		static int GetWindowWidth() { return GetInstance().IGetWindowWidth(); }
		static int GetWindowHeight() { return GetInstance().IGetWindowHeight(); }
		static int GetGameWidth() { return GetInstance().IGetGameWidth(); }
		static int GetGameHeight() { return GetInstance().IGetGameHeight(); }
		static int GetDefaultFrameRate() { return GetInstance().IGetDefaultFrameRate(); }
		static bool GetDefaultFrameRateMode() { return GetInstance().IGetDefaultFrameRateMode(); }

	private:
		int IGetWindowWidth() const { return m_WindowWidth; }
		int IGetWindowHeight() const { return m_WindowHeight; }
		int IGetGameWidth() const { return m_GameWidth; }
		int IGetGameHeight() const { return m_GameHeigth; }
		int IGetDefaultFrameRate() const { return m_FPS; }
		bool IGetDefaultFrameRateMode() const { return m_UseFixedFrameRate; }
		
		// Default engine settings
		static const int m_WindowWidth{ 1820 };
		static const int m_WindowHeight{ 980 };
		static const int m_GameWidth{ 640 };
		static const int m_GameHeigth{ 480 };
		static const bool m_UseFixedFrameRate{ true };
		static const int m_FPS{ 144 };
		static float m_Gravity;
	};
}