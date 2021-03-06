#include "FuelEnginePCH.h"
#include "FuelEngine.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "EngineSettings.h"
#include "EngineComponents.h"
#include "SoundManager.h"
#include "Game.h"
#include "Time.h"
#include "Button.h"

using namespace std;

fuel::FuelEngine::FuelEngine(Game* pGame)
{
	m_pGame = pGame;
}

fuel::FuelEngine::~FuelEngine()
{
	SafeDelete(m_pGame);
}

void fuel::FuelEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

#ifdef RunEditor
	m_Window = SDL_CreateWindow(
		"FuelEngine: 'Bubble Bubble Editor'",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		EngineSettings::GetWindowWidth(),
		EngineSettings::GetWindowHeight(),
		SDL_WINDOW_OPENGL
	);
#else
	m_Window = SDL_CreateWindow(
		"FuelEngine: 'Bubble Bubble'",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		EngineSettings::GetGameWidth(),
		EngineSettings::GetGameHeight(),
		SDL_WINDOW_OPENGL
	);
#endif
	
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void fuel::FuelEngine::LoadGame() const
{
	SoundManager::GetInstance().AddSound("Landing", "../Data/SoundFX/Landing.wav");
	SoundManager::GetInstance().AddSound("BubblePop", "../Data/SoundFX/Bubble_Pop.wav");
	SoundManager::GetInstance().AddSound("BubbleShoot", "../Data/SoundFX/bubble_shoot.wav");
	SoundManager::GetInstance().AddSound("EnemyCaptured", "../Data/SoundFX/enemies_rolling_away.wav");
	SoundManager::GetInstance().AddSound("GameOver", "../Data/SoundFX/game_over.wav");
	SoundManager::GetInstance().AddSound("Jump", "../Data/SoundFX/jump.wav");
	SoundManager::GetInstance().AddSound("LoseLife", "../Data/SoundFX/lose_life.wav");
	SoundManager::GetInstance().AddSound("UISound", "../Data/SoundFX/menu_navigate.wav");
	SoundManager::GetInstance().AddSound("NextLevel", "../Data/SoundFX/next_level.wav");
	SoundManager::GetInstance().AddSound("ScoreUp", "../Data/SoundFX/score.wav");
	
	//FileManager::SaveScene(&scene, "LevelThree");
	//FileManager::LoadScene(&scene, "MainMenu");
}

void fuel::FuelEngine::Cleanup()
{
	Renderer::Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void fuel::FuelEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::Init("../Data/");
	InputManager::Initialize();
	Time::SetFixedFrameRate(EngineSettings::GetDefaultFrameRateMode());
	Time::SetFixedFPS(EngineSettings::GetDefaultFrameRate());
	
	m_pGame->Initialize();
	LoadGame();

	// Start scenes
	SceneManager::Initialize();
	SceneManager::Start();

	// Threading test ------------------------------------------------------- //
	/*std::mutex m_Mutex;
	auto updateFunct = [this, &m_Mutex]()
	{
		Time::SetEndFrame(std::chrono::high_resolution_clock::now());
		float lag{ 0 };
		while (m_IsGameRunning)
		{
			std::lock_guard<std::mutex> guard(m_Mutex);
			Time::SetStartFrame(std::chrono::high_resolution_clock::now());
			Time::Update();
			lag += Time::GetDeltaTime();

			while (lag >= Time::GetFixedDeltaTime())
			{
				SceneManager::FixedUpdate();
				m_pGame->FixedUpdate();
				lag -= Time::GetFixedDeltaTime();
			}

			SceneManager::Update();
			m_pGame->Update();
			Renderer::Render();
			m_pGame->Draw();
		}
	};

	std::thread updateThread(updateFunct);

	while (m_IsGameRunning)
	{
		//std::cout << "input" << std::endl;
		m_IsGameRunning = InputManager::ProcessInput();
	}*/
	// ------------------------------------------------------------------- //

	Time::SetEndFrame(std::chrono::high_resolution_clock::now());
	float lag{ 0 };
	while (m_IsGameRunning)
	{
		Time::SetStartFrame(std::chrono::high_resolution_clock::now());
		Time::Update();
		lag += Time::GetDeltaTime();

		m_IsGameRunning = InputManager::ProcessInput();
		
		while (lag >= Time::GetFixedDeltaTime())
		{
			SceneManager::FixedUpdate();
			m_pGame->FixedUpdate();
			lag -= Time::GetFixedDeltaTime();
		}

		SceneManager::Update();
		m_pGame->Update();
		Renderer::Render();
		m_pGame->Draw();
	}
	
	//updateThread.join();
	Cleanup();
}