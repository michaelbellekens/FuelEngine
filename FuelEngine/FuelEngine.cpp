#include "FuelEnginePCH.h"
#include "FuelEngine.h"

#include <mutex>


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
	//auto& scene = SceneManager::CreateScene("MainMenu");

	/*std::shared_ptr<GameObject> go;

	std::string tileData;
	FileManager::ReadLevelTiles(tileData, "../Data/LevelData/LevelTiles_Level3.txt");

	int tileID{ 0 };
	int yOffset{ 0 };
	for (int i{ 0 }; i < 25; ++i)
	{
		for (int j{ 0 }; j < 32; ++j)
		{
			const int idx{ j + i * 32 };

			if (tileData[idx] != 'x')
				continue;

			const int xOffset{ 640 / 32 };

			go = std::make_shared<GameObject>();
			scene.AddToScene(go);
			go->SetName("Block_" + std::to_string(tileID));
			go->SetTag("StaticScene");
			go->AddComponent<Transform>();
			go->GetTransform()->SetPosition(static_cast<float>(xOffset * j), static_cast<float>(yOffset));
			RenderComponent* pRenderComponent = go->AddComponent<RenderComponent>();
			pRenderComponent->SetTexture("wallTile_3.png");
			RigidBody2D* pRigidBody = go->AddComponent<RigidBody2D>();
			pRigidBody->SetIsKinematic(true);
			pRigidBody->UseGravity(false);
			BoxCollider* pBoxCollider = go->AddComponent<BoxCollider>();
			pBoxCollider->SetDimensions(Rectf(0.f, 0.f, 20.f, 20.f));

			if (j >= 2 && j <=29 && i > 1 && i < 23)
			{
				pBoxCollider->SetCanPassFromBellow(true);
			}

			++tileID;
		}
		yOffset += 480 / 25;
	}

	go = std::make_shared<GameObject>();
	scene.AddToScene(go);
	go->SetName("Player1");
	go->SetTag("Player");
	Transform* spriteTransform = go->AddComponent<Transform>();
	spriteTransform->SetPosition(50.f, 50.f);
	RigidBody2D* spriteRigidBody = go->AddComponent<RigidBody2D>();
	spriteRigidBody->SetIsKinematic(false);
	spriteRigidBody->UseGravity(true);
	spriteRigidBody->SetBounciness(0.2f);
	BoxCollider* spriteCollider = go->AddComponent<BoxCollider>();
	spriteCollider->SetDimensions(Rectf(0.f, 0.f, 16.f, 16.f));
	SpriteComponent* pSpriteComp = go->AddComponent<SpriteComponent>();
	pSpriteComp->SetTexture("CharacterSpriteSheet.png");
	pSpriteComp->SetColumns(8);
	pSpriteComp->SetRows(16);
	pSpriteComp->SetAnimTime(0.1f);
	pSpriteComp->AddAnimation(0, 8);
	pSpriteComp->AddAnimation(1, 8);
	pSpriteComp->SetScale(1.f, 1.f);
	pSpriteComp->SetAnimation(0);
	pSpriteComp->SetDirectionIDs(1, 0);
	PlayerController* pController1 = go->AddComponent<PlayerController>();
	pController1->SetPlayerID(PlayerID::PlayerOne);
	pController1->SetIsInMenu(false);
	
	go = std::make_shared<GameObject>();
	scene.AddToScene(go);
	go->SetName("Player2");
	go->SetTag("Player");
	Transform* player2Transform = go->AddComponent<Transform>();
	player2Transform->SetPosition(501.f, 50.f);
	RigidBody2D* player2RigidBody = go->AddComponent<RigidBody2D>();
	player2RigidBody->SetIsKinematic(false);
	player2RigidBody->UseGravity(true);
	player2RigidBody->SetBounciness(0.2f);
	BoxCollider* player2Collider = go->AddComponent<BoxCollider>();
	player2Collider->SetDimensions(Rectf(0.f, 0.f, 16.f, 16.f));
	SpriteComponent* pSpriteCompPlayer2 = go->AddComponent<SpriteComponent>();
	pSpriteCompPlayer2->SetTexture("CharacterSpriteSheet.png");
	pSpriteCompPlayer2->SetColumns(8);
	pSpriteCompPlayer2->SetRows(16);
	pSpriteCompPlayer2->SetAnimTime(0.1f);
	pSpriteCompPlayer2->AddAnimation(2, 8);
	pSpriteCompPlayer2->AddAnimation(3, 8);
	pSpriteCompPlayer2->SetScale(1.f, 1.f);
	pSpriteCompPlayer2->SetAnimation(2);
	pSpriteCompPlayer2->SetDirectionIDs(3, 2);
	PlayerController* pController2 = go->AddComponent<PlayerController>();
	pController2->SetPlayerID(PlayerID::PlayerTwo);
	pController2->SetIsInMenu(false);
	
	go = std::make_shared<GameObject>();
	scene.AddToScene(go);
	go->SetName("Score Player 1");
	go->SetTag("UI");
	go->AddComponent<Transform>();
	go->GetTransform()->SetPosition(45.f, 30.f);
	TextComponent* pScorePlayer1{ go->AddComponent<TextComponent>() };
	pScorePlayer1->SetFont(ResourceManager::LoadFont("Pixeled.ttf", 12));
	pScorePlayer1->SetSize(12);
	pScorePlayer1->SetText("000000");

	go = std::make_shared<GameObject>();
	scene.AddToScene(go);
	go->SetName("Score Player 2");
	go->SetTag("UI");
	go->AddComponent<Transform>();
	go->GetTransform()->SetPosition(520.f, 30.f);
	TextComponent* pScorePlayer2{ go->AddComponent<TextComponent>() };
	pScorePlayer2->SetFont(ResourceManager::LoadFont("Pixeled.ttf", 12));
	pScorePlayer2->SetSize(12);
	pScorePlayer2->SetText("000000");
	*/
	SoundManager::GetInstance().AddSound("BubblePop", "../Data/SoundFX/Bubble_Pop.wav");
	
	//FileManager::SaveScene(&scene, "LevelThree");
	//FileManager::LoadScene(&scene, "LevelThree");
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
	m_pGame->Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::Init("../Data/");
	InputManager::Initialize();
	Time::SetFixedFrameRate(EngineSettings::GetDefaultFrameRateMode());
	Time::SetFixedFPS(EngineSettings::GetDefaultFrameRate());
	
	LoadGame();

	// Start scenes
	SceneManager::Initialize();
	SceneManager::Start();

	std::mutex m_Mutex;

	// Threading test ------------------------------------------------------- //
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
	}
	// ------------------------------------------------------------------- //

	updateThread.join();
	Cleanup();
}