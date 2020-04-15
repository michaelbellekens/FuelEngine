#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

typedef enum
{
	FUEL_UPDATE_RATE_EXTREME = 144,
	FUEL_UPDATE_RATE_HIGH = 120,
	FUEL_UPDATE_RATE_NORMAL = 60,
	FUEL_UPDATE_RATE_LOW = 30,
	FUEL_UPDATE_RATE_POTATO = 10
} FUEL_UpdateRate;

class Time : public fuel::Singleton<Time>
{
public:
	static void Update() { GetInstance().IUpdate(); }
	
	static void SetStartFrame(const steady_clock::time_point startTime) { GetInstance().ISetFrameStart(startTime); }
	static void SetEndFrame(const steady_clock::time_point endTime) { GetInstance().ISetFrameEnd(endTime); }
	static void SetFixedFPS(const int fps) { GetInstance().ISetFixedFPS(fps); }
	static void SetFixedFrameRate(bool isFrameRateFixed) { GetInstance().ISetFixedFrameRate(isFrameRateFixed); }

	static float GetDeltaTime() { return GetInstance().m_DeltaTime; }
	static float GetFixedDeltaTime() { return GetInstance().m_FixedDeltaTime; }
	static int GetFPS() { return GetInstance().m_FPS; }
	
private:
	void IUpdate();
	
	void ISetFrameStart(const steady_clock::time_point startTime);
	void ISetFrameEnd(const steady_clock::time_point endTime);
	void ISetFixedFPS(const int fps);
	void ISetFixedFrameRate(bool isFrameRateFixed);

	// Helper functions
	static float SecondsToUs(const float sec) { return std::roundf(sec * 1000000); }
	static float UsToSeconds(const float us) { return us / 1000000; }

	steady_clock::time_point m_StartTimeFrame{milliseconds(0) };
	steady_clock::time_point m_EndTimeFrame{milliseconds(0) };
	
	int m_FPS{};
	float m_DeltaTime{};
	const float m_FixedDeltaTime{ 0.02f };
	int m_TargetFpsUs{};
	bool m_bFixedFrameRate{ true };
};
