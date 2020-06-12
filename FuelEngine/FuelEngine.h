#pragma once

class Game;

struct SDL_Window;
struct EngineSettings;

namespace fuel
{
	class FuelEngine
	{
	public:
		FuelEngine(Game* pGame);
		~FuelEngine();
		
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		
	private:
		bool IsUpdateFinished() const { return m_IsUpdateDone; }

		EngineSettings* m_Settings{};
		SDL_Window* m_Window{};
		Game* m_pGame{ nullptr };
		bool m_IsUpdateDone{ false };
		bool m_IsRenderStarted{ true };
		bool m_IsGameRunning{ true };

	};
}