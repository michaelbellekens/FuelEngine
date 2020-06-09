#include "FuelEnginePCH.h"
#include "FuelEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "GameObject.h"
#include "Scene.h"
#include "EngineSettings.h"
#include "EngineComponents.h"
#include "FileManager.h"
#include "SoundManager.h"
#include "SpriteComponent.h"


using namespace std;
using namespace std::chrono;

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
	auto& scene = SceneManager::CreateScene("StartScene");

	/*auto go = std::make_shared<GameObject>();
	go->SetName("Background Holder");
	scene.AddToScene(go);
	RenderComponent* renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture("background.jpg");
	go->AddComponent<Transform>();
	
	go = std::make_shared<GameObject>();
	go->SetName("Logo Holder 2");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	RenderComponent* renderCompLogo2 = go->AddComponent<RenderComponent>();
	renderCompLogo2->SetTexture("logo.png");
	RigidBody2D* rigidBody1 = go->AddComponent<RigidBody2D>();
	rigidBody1->SetIsKinematic(true);
	rigidBody1->UseGravity(true);
	go->AddComponent<BoxCollider>();
	go->GetTransform()->SetPosition(100, 0);

	go = std::make_shared<GameObject>();
	go->SetName("Collision Test");
	scene.AddToScene(go);
	go->AddComponent<Transform>();
	RigidBody2D* rigidBody2{ go->AddComponent<RigidBody2D>() };
	rigidBody2->SetIsKinematic(true);
	BoxCollider* boxCol{ go->AddComponent<BoxCollider>() };
	boxCol->SetDimensions(Rectf(0.f, 0.f, 200.f, 100.f));
	go->GetTransform()->SetPosition(0.f, 380.f);
	go->SetTag("CollisionBox");

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

	go = std::make_shared<GameObject>();
	go->SetName("SpriteTest");
	scene.AddToScene(go);
	Transform* spriteTransform = go->AddComponent<Transform>();
	spriteTransform->SetPosition(20.f, 20.f);
	RigidBody2D* spriteRigidBody = go->AddComponent<RigidBody2D>();
	spriteRigidBody->SetIsKinematic(false);
	spriteRigidBody->UseGravity(true);
	BoxCollider* spriteCollider = go->AddComponent<BoxCollider>();
	spriteCollider->SetDimensions(Rectf(0.f, 0.f, 64.f, 64.f));
	SpriteComponent* pSpriteComp = go->AddComponent<SpriteComponent>();
	pSpriteComp->SetTexture("CharacterSpriteSheet.png");
	pSpriteComp->SetColumns(8);
	pSpriteComp->SetRows(16);
	pSpriteComp->SetAnimTime(0.1f);
	pSpriteComp->AddAnimation(0, 8);
	pSpriteComp->AddAnimation(1, 8);
	pSpriteComp->AddAnimation(2, 8);
	pSpriteComp->AddAnimation(3, 8);
	pSpriteComp->AddAnimation(4, 8);
	pSpriteComp->AddAnimation(5, 8);
	pSpriteComp->AddAnimation(15, 8);
	pSpriteComp->SetScale(4.f, 4.f);
	pSpriteComp->SetAnimation(2);

	auto pButton{ std::make_shared<Button>() };
	scene.AddButton(pButton.get());
	scene.AddToScene(pButton);
	pButton->SetName("Button_1");
	pButton->SetSelected(true);
	pButton->SetTexture("logo.png");
	pButton->SetText("Solo");
	pButton->SetButtonAction(ButtonAction::OnePlayer);
	pButton->SetButtonID(0);
	pButton->GetTransform()->SetPosition(Vector3(300.f, 0.f, 0.f));

	pButton = std::make_shared<Button>();
	scene.AddButton(pButton.get());
	scene.AddToScene(pButton);
	pButton->SetName("Button_2");
	pButton->SetSelected(false);
	pButton->SetTexture("logo.png");
	pButton->SetText("Co-Op");
	pButton->SetButtonAction(ButtonAction::COOP);
	pButton->SetButtonID(1);
	pButton->GetTransform()->SetPosition(Vector3(300.f, 100.f, 0.f));

	pButton = std::make_shared<Button>();
	scene.AddButton(pButton.get());
	scene.AddToScene(pButton);
	pButton->SetName("Button_3");
	pButton->SetSelected(false);
	pButton->SetTexture("logo.png");
	pButton->SetText("VS");
	pButton->SetButtonAction(ButtonAction::VS);
	pButton->SetButtonID(2);
	pButton->GetTransform()->SetPosition(Vector3(300.f, 200.f, 0.f));

	pButton = std::make_shared<Button>();
	scene.AddButton(pButton.get());
	scene.AddToScene(pButton);
	pButton->SetName("Button_4");
	pButton->SetSelected(false);
	pButton->SetTexture("logo.png");
	pButton->SetText("Quit");
	pButton->SetButtonAction(ButtonAction::QUIT);
	pButton->SetButtonID(3);
	pButton->GetTransform()->SetPosition(Vector3(300.f, 300.f, 0.f));

	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Fart, ButtonState::pressed, SDLK_f);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Fire, ButtonState::hold, SDLK_k);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::Jump, ButtonState::released, SDLK_j);

	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::MoveUpUI, ButtonState::released, SDLK_UP);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::MoveDownUI, ButtonState::released, SDLK_DOWN);
	InputManager::AddKeyboardBinding(PlayerID::PlayerOne, playerController1, CommandID::ClickUI, ButtonState::released, SDLK_RETURN);
	*/
	SoundManager::GetInstance().AddSound("BubblePop", "../Data/SoundFX/Bubble_Pop.wav");
	
	//FileManager::GetInstance().SaveScene(&scene, "TestScene");
	FileManager::GetInstance().LoadScene(&scene, "TestScene");
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