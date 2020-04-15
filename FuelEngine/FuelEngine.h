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
		EngineSettings* m_Settings{};
		SDL_Window* m_Window{};
	};
}