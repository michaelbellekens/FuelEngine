#pragma once

struct SDL_Window;
struct EngineSettings;
namespace fuel
{
	class FuelEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		
	private:
		bool IsUpdateFinished() const { return m_IsUpdateDone; }

		EngineSettings* m_Settings{};
		SDL_Window* m_Window{};
		bool m_IsUpdateDone{ false };
		bool m_IsRenderStarted{ true };
		bool m_IsGameRunning{ true };

	};
}