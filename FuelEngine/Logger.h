#pragma once
#include "Singleton.h"
#include  "Tools.h"

namespace fuel
{
	class Logger final : public Singleton<Logger>
	{
	public:
		Logger() = default;
		~Logger() = default;

		Logger(const Logger& other) = delete;
		Logger(Logger&& other) = delete;
		Logger& operator=(const Logger& other) = delete;
		Logger& operator=(Logger&& other) = delete;

		static void Draw() { GetInstance().IDraw(); }


		static void LogInfo(const std::string& message) { GetInstance().ILogInfo(message); }
		static void LogWarning(const std::string& message) { GetInstance().ILogWarning(message); }
		static void LogError(const std::string& message) { GetInstance().ILogError(message); }
		
	private:
		// Internal functions
		void ILogInfo(const std::string& message);
		void ILogWarning(const std::string& message);
		void ILogError(const std::string& message);

		void IDraw();

		// Datamembers
		std::vector<ColoredText> m_AllLogs;
		bool m_RefreshWindow{ false };
	};

	inline void Logger::IDraw()
	{
		ImGui::Begin("Console Log");

		for (ColoredText log : m_AllLogs)
		{
			ImGui::TextColored({ log.color.r, log.color.g, log.color.b, log.color.a }, log.text.c_str());
		}

		if (m_RefreshWindow)
		{
			ImGui::SetScrollHereY(1.0f);
			m_RefreshWindow = false;
		}

		ImGui::End();
	}
	
	inline void Logger::ILogInfo(const std::string& message)
	{
		std::string logText{ "[FuelEngine] [INFO]: " };
		logText += message;
		
		const Color4 textColor{ 1.f, 1.f, 1.f, 1.f };
		
		m_AllLogs.push_back(ColoredText(textColor, logText));
		m_RefreshWindow = true;
	}

	inline void Logger::ILogWarning(const std::string& message)
	{
		std::string logText{ "[FuelEngine] [WARNING]: " };
		logText += message;

		const Color4 textColor{ 1.f, 1.f, 0.f, 1.f };

		m_AllLogs.push_back(ColoredText(textColor, logText));
		m_RefreshWindow = true;
	}

	inline void Logger::ILogError(const std::string& message)
	{
		std::string logText{ "[FuelEngine] [ERROR]: " };
		logText += message;

		const Color4 textColor{ 1.f, 0.f, 0.f, 1.f };

		m_AllLogs.push_back(ColoredText(textColor, logText));
		m_RefreshWindow = true;
	}
}

