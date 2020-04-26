#include "FuelEnginePCH.h"
#include "FuelEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "BoxCollider.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "EngineSettings.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "PlayerController.h"
#include "SphereCollider.h"
#include "VibrationComponent.h"

using namespace std;
using namespace std::chrono;

void fuel::FuelEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"FuelEngine: 'Bubble Bubble'",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		EngineSettings::GetWindowWidth(),
		EngineSettings::GetWindowHeight(),
		SDL_WINDOW_OPENGL
	);
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
	auto& scene = SceneManager::CreateScene("StartScene");

	auto go = std::make_shared<GameObject>();
	go->SetName("Background Holder");
	scene.AddToScene(go);
	RenderComponent* renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture("background.jpg");
	go->AddComponent<Transform>();

	go = std::make_shared<GameObject>();
	go->SetName("Logo Holder 1");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	RenderComponent* renderCompLogo = go->AddComponent<RenderComponent>();
	renderCompLogo->SetTexture("logo.png");
	go->GetTransform()->SetPosition(216, 180);
	
	go = std::make_shared<GameObject>();
	go->SetName("Logo Holder 2");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	RenderComponent* renderCompLogo2 = go->AddComponent<RenderComponent>();
	renderCompLogo2->SetTexture("logo.png");
	go->AddComponent<BoxCollider>();
	go->GetTransform()->SetPosition(0, 0);

	go = std::make_shared<GameObject>();
	go->SetName("Assignment Name");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	TextComponent* textComp = go->AddComponent<TextComponent>();
	textComp->SetFont(ResourceManager::LoadFont("Lingua.otf", 36));
	textComp->SetText("Programming 4 Assignment");
	go->GetTransform()->SetPosition(80, 20);

	go = std::make_shared<GameObject>();
	go->SetName("Assignment Name 2");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	TextComponent* textComp2 = go->AddComponent<TextComponent>();
	textComp2->SetFont(ResourceManager::LoadFont("Lingua.otf", 36));
	textComp2->SetText("Programming 4 Assignment");
	go->GetTransform()->SetPosition(150, 100);

	go = std::make_shared<GameObject>();
	go->SetName("FPS Counter");
	scene.AddToScene(go);
	Transform* trans = go->AddComponent<Transform>();
	trans->SetPosition(10.f, 120.f);
	go->AddComponent<TextComponent>();
	FPSComponent* fpsComp = go->AddComponent<FPSComponent>();
	fpsComp->Initialize();

	go = std::make_shared<GameObject>();
	go->SetName("PlayerController example");
	scene.AddToScene(go);
	Transform* trans2 = go->AddComponent<Transform>();
	trans2->SetPosition(20.f, 400.f);
	PlayerController* playerController1 = go->AddComponent<PlayerController>();
	playerController1->SetPlayerID(PlayerID::PlayerOne);
	go->AddComponent<TextComponent>();
	go->AddComponent<VibrationComponent>();
	
	//go = std::make_shared<GameObject>();
	//scene.AddToScene(go);
	//go->AddComponent<Transform>();
	//PlayerController* playerController2 = go->AddComponent<PlayerController>();
	//playerController2->SetPlayerID(PlayerID::PlayerTwo);

	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Fart, ButtonState::pressed, SDLK_f);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Fire, ButtonState::hold, SDLK_k);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Jump, ButtonState::released, SDLK_j);

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
	
	LoadGame();

	// Start scenes
	SceneManager::Initialize();
	SceneManager::Start();
	float lag{ 0 };
	Time::SetEndFrame(high_resolution_clock::now());
	
	{
		bool isGameRunning = true;
		while (isGameRunning)
		{
			Time::SetStartFrame(high_resolution_clock::now());
			Time::Update();
			lag += Time::GetDeltaTime();
			
			isGameRunning = InputManager::ProcessInput();

			while (lag >= Time::GetFixedDeltaTime())
			{
				SceneManager::FixedUpdate();
				lag -= Time::GetFixedDeltaTime();
			}
			
			SceneManager::Update();
			Renderer::Render();
		}
	}

	Cleanup();
}