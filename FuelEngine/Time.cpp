#include "FuelEnginePCH.h"
#include "Time.h"
#include <thread>

void Time::IUpdate()
{
	m_DeltaTime = duration_cast<duration<float>>(m_StartTimeFrame - m_EndTimeFrame).count();

	const int sleepTimeUs{ m_TargetFpsUs - int(SecondsToUs(m_DeltaTime)) };
	std::this_thread::sleep_for(microseconds(sleepTimeUs));

	m_DeltaTime += UsToSeconds(float(sleepTimeUs));

	m_EndTimeFrame = m_StartTimeFrame;
}

void Time::ISetFrameStart(const std::chrono::steady_clock::time_point startTime)
{
	m_StartTimeFrame = startTime;
}

void Time::ISetFrameEnd(const std::chrono::steady_clock::time_point endTime)
{
	m_EndTimeFrame = endTime;
}

void Time::ISetFixedFPS(const int fps)
{
	m_TargetFpsUs = int(SecondsToUs(1.f / float(fps)));
}

void Time::ISetFixedFrameRate(bool isFrameRateFixed)
{
	m_bFixedFrameRate = isFrameRateFixed;
}
