#include "FuelEnginePCH.h"
#include "BubbleBobble.h"

#include <SDL.h>
#include "BoxCollider.h"
#include "FileManager.h"
#include "Logger.h"
#include "RigidBody2D.h"
#include "SceneManager.h"
#include "Time.h"
#include "SpriteComponent.h"
#include "Transform.h"

BubbleBobble::BubbleBobble()
	: m_MainMenuScene(fuel::SceneManager::CreateScene("MainMenu"))
	, m_LevelOneScene(fuel::SceneManager::CreateScene("Level_One"))
	, m_LevelTwoScene(fuel::SceneManager::CreateScene("Level_Two"))
	, m_LevelThreeScene(fuel::SceneManager::CreateScene("Level_Three"))
	, m_pPlayer1(nullptr)
	, m_pPlayer2(nullptr)
	, m_GameMode(SOLO)
{}

BubbleBobble::~BubbleBobble()
{
}

void BubbleBobble::Initialize()
{
	fuel::Logger::LogInfo("Game Initialize");
	LoadScenes();
	fuel::SceneManager::SetActiveScene("MainMenu");
	InitializeButtons();

	// Initialize levels
	InitializeLevelOne();
	InitializeLevelTwo();
	InitializeLevelThree();
}

void BubbleBobble::Update()
{
	const std::string activeSceneName{ fuel::SceneManager::GetActiveScene()->GetName() };
	if (activeSceneName == "MainMenu")
	{
		UpdateMainMenu();
	}
	else if (activeSceneName == "Level_One")
	{
		UpdateLevelOne();
	}
	else if (activeSceneName == "Level_Two")
	{
		UpdateLevelTwo();
	}
	else if (activeSceneName == "Level_Three")
	{
		UpdateLevelThree();
	}
}

void BubbleBobble::FixedUpdate()
{
}

void BubbleBobble::Draw()
{
}

void BubbleBobble::LoadScenes()
{
	fuel::FileManager::LoadScene(&m_MainMenuScene, "MainMenu");
	fuel::FileManager::LoadScene(&m_LevelOneScene, "LevelOne");
	fuel::FileManager::LoadScene(&m_LevelTwoScene, "LevelTwo");
	fuel::FileManager::LoadScene(&m_LevelThreeScene, "LevelThree");
}

void BubbleBobble::InitializeButtons()
{
	fuel::Logger::LogInfo("Buttons initialized!");
	fuel::Button* pButtonSolo = reinterpret_cast<fuel::Button*>(m_MainMenuScene.FindObject("B_OnePlayer").get());
	fuel::Button* pButtonDuo = reinterpret_cast<fuel::Button*>(m_MainMenuScene.FindObject("B_TwoPlayer").get());
	fuel::Button* pButtonVS = reinterpret_cast<fuel::Button*>(m_MainMenuScene.FindObject("B_Versus").get());
	fuel::Button* pButtonQuit = reinterpret_cast<fuel::Button*>(m_MainMenuScene.FindObject("B_Quit").get());

	const std::function<void()> soloFunction = [this]()
	{
		m_GameMode = SOLO;
		SwitchToScene("Level_One");
	};
	
	const std::function<void()> coopFunction = [this]()
	{
		m_GameMode = COOP;
		SwitchToScene("Level_One");
	};
	
	const std::function<void()> vsFunction = [this]()
	{
		m_GameMode = VS;
		SwitchToScene("Level_One");
	};
	
	const std::function<void()> quitFunction = []()
	{
		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
	};

	pButtonSolo->AddFunctionData(soloFunction);
	pButtonDuo->AddFunctionData(coopFunction);
	pButtonVS->AddFunctionData(vsFunction);
	pButtonQuit->AddFunctionData(quitFunction);
}

void BubbleBobble::InitializeLevelOne()
{
	for (int i{ 0 }; i < 4; ++i)
	{
		auto go = std::make_shared<fuel::GameObject>();
		m_LevelOneScene.AddToScene(go);
		go->SetName("Enemy_" + std::to_string(i));
		go->SetTag("Enemy");
		fuel::Transform* player2Transform = go->AddComponent<fuel::Transform>();
		player2Transform->SetPosition(501.f, 50.f);
		fuel::RigidBody2D* player2RigidBody = go->AddComponent<fuel::RigidBody2D>();
		player2RigidBody->SetIsKinematic(false);
		player2RigidBody->UseGravity(true);
		player2RigidBody->SetBounciness(0.2f);
		fuel::BoxCollider* player2Collider = go->AddComponent<fuel::BoxCollider>();
		player2Collider->SetDimensions(fuel::Rectf(0.f, 0.f, 16.f, 16.f));
		fuel::SpriteComponent* pSpriteCompPlayer2 = go->AddComponent<fuel::SpriteComponent>();
		pSpriteCompPlayer2->SetTexture("CharacterSpriteSheet.png");
		pSpriteCompPlayer2->SetColumns(8);
		pSpriteCompPlayer2->SetRows(16);
		pSpriteCompPlayer2->SetAnimTime(0.1f);
		pSpriteCompPlayer2->AddAnimation(4, 8);
		pSpriteCompPlayer2->AddAnimation(5, 8);
		pSpriteCompPlayer2->SetScale(1.f, 1.f);
		pSpriteCompPlayer2->SetAnimation(4);
		pSpriteCompPlayer2->SetDirectionIDs(5, 4);
		//fuel::AIController* pAIController{ go->AddComponent<fuel::AIController>() };
		//UNREFERENCED_PARAMETER(pAIController);

		m_EnemiesLevelOne.push_back(go);
	}

	m_EnemiesLevelOne[0]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(100.f, 430.f, 0.f));
	m_EnemiesLevelOne[1]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(510.f, 430.f, 0.f));
	m_EnemiesLevelOne[2]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(200.f, 164.f, 0.f));
	m_EnemiesLevelOne[3]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(400.f, 259.f, 0.f));
}

void BubbleBobble::InitializeLevelTwo()
{
	for (int i{ 0 }; i < 5; ++i)
	{
		auto go = std::make_shared<fuel::GameObject>();
		m_LevelTwoScene.AddToScene(go);
		go->SetName("Enemy_" + std::to_string(i));
		go->SetTag("Enemy");
		fuel::Transform* player2Transform = go->AddComponent<fuel::Transform>();
		player2Transform->SetPosition(501.f, 50.f);
		fuel::RigidBody2D* player2RigidBody = go->AddComponent<fuel::RigidBody2D>();
		player2RigidBody->SetIsKinematic(false);
		player2RigidBody->UseGravity(true);
		player2RigidBody->SetBounciness(0.2f);
		fuel::BoxCollider* player2Collider = go->AddComponent<fuel::BoxCollider>();
		player2Collider->SetDimensions(fuel::Rectf(0.f, 0.f, 16.f, 16.f));
		fuel::SpriteComponent* pSpriteCompPlayer2 = go->AddComponent<fuel::SpriteComponent>();
		pSpriteCompPlayer2->SetTexture("CharacterSpriteSheet.png");
		pSpriteCompPlayer2->SetColumns(8);
		pSpriteCompPlayer2->SetRows(16);
		pSpriteCompPlayer2->SetAnimTime(0.1f);
		pSpriteCompPlayer2->AddAnimation(4, 8);
		pSpriteCompPlayer2->AddAnimation(5, 8);
		pSpriteCompPlayer2->SetScale(1.f, 1.f);
		pSpriteCompPlayer2->SetAnimation(4);
		pSpriteCompPlayer2->SetDirectionIDs(5, 4);
		//fuel::AIController* pAIController{ go->AddComponent<fuel::AIController>() };
		//UNREFERENCED_PARAMETER(pAIController);

		m_EnemiesLevelTwo.push_back(go);
	}

	m_EnemiesLevelTwo[0]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(100.f, 430.f, 0.f));
	m_EnemiesLevelTwo[1]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(510.f, 430.f, 0.f));
	m_EnemiesLevelTwo[2]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(200.f, 164.f, 0.f));
	m_EnemiesLevelTwo[3]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(400.f, 259.f, 0.f));
	m_EnemiesLevelTwo[4]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(320.f, 50.f, 0.f));
}

void BubbleBobble::InitializeLevelThree()
{
	for (int i{ 0 }; i < 5; ++i)
	{
		auto go = std::make_shared<fuel::GameObject>();
		m_LevelThreeScene.AddToScene(go);
		go->SetName("Enemy_" + std::to_string(i));
		go->SetTag("Enemy");
		fuel::Transform* player2Transform = go->AddComponent<fuel::Transform>();
		player2Transform->SetPosition(501.f, 50.f);
		fuel::RigidBody2D* player2RigidBody = go->AddComponent<fuel::RigidBody2D>();
		player2RigidBody->SetIsKinematic(false);
		player2RigidBody->UseGravity(true);
		player2RigidBody->SetBounciness(0.2f);
		fuel::BoxCollider* player2Collider = go->AddComponent<fuel::BoxCollider>();
		player2Collider->SetDimensions(fuel::Rectf(0.f, 0.f, 16.f, 16.f));
		fuel::SpriteComponent* pSpriteCompPlayer2 = go->AddComponent<fuel::SpriteComponent>();
		pSpriteCompPlayer2->SetTexture("CharacterSpriteSheet.png");
		pSpriteCompPlayer2->SetColumns(8);
		pSpriteCompPlayer2->SetRows(16);
		pSpriteCompPlayer2->SetAnimTime(0.1f);
		pSpriteCompPlayer2->AddAnimation(4, 8);
		pSpriteCompPlayer2->AddAnimation(5, 8);
		pSpriteCompPlayer2->SetScale(1.f, 1.f);
		pSpriteCompPlayer2->SetAnimation(4);
		pSpriteCompPlayer2->SetDirectionIDs(5, 4);
		//fuel::AIController* pAIController{ go->AddComponent<fuel::AIController>() };
		//UNREFERENCED_PARAMETER(pAIController);

		m_EnemiesLevelThree.push_back(go);
	}

	m_EnemiesLevelThree[0]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(100.f, 430.f, 0.f));
	m_EnemiesLevelThree[1]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(510.f, 430.f, 0.f));
	m_EnemiesLevelThree[2]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(200.f, 164.f, 0.f));
	m_EnemiesLevelThree[3]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(400.f, 259.f, 0.f));
	m_EnemiesLevelThree[4]->GetComponent<fuel::Transform>()->SetPosition(fuel::Vector3(320.f, 50.f, 0.f));
}

void BubbleBobble::SwitchToScene(const std::string& sceneName)
{
	fuel::SceneManager::SetActiveScene(sceneName);
	fuel::Scene* pCurrentScene{ fuel::SceneManager::GetActiveScene() };

	if (m_MainMenuScene.GetIsActive())
		return;

	m_pPlayer1 = reinterpret_cast<fuel::GameObject*>(pCurrentScene->FindObject("Player1").get());
	m_pPlayer2 = reinterpret_cast<fuel::GameObject*>(pCurrentScene->FindObject("Player2").get());

	switch (m_GameMode)
	{
	case SOLO:
		m_pPlayer1->GetComponent<fuel::RigidBody2D>()->SetPosition(fuel::Vector3( 50.f, 50.f, 0.f ));
		m_pPlayer1->SetActive(true);
		m_pPlayer2->SetActive(false);
		break;
	case COOP:
		m_pPlayer1->GetComponent<fuel::RigidBody2D>()->SetPosition(fuel::Vector3(50.f, 50.f, 0.f));
		m_pPlayer2->GetComponent<fuel::RigidBody2D>()->SetPosition(fuel::Vector3(501.f, 50.f, 0.f));
		m_pPlayer1->SetActive(true);
		m_pPlayer2->SetActive(true);
		break;
	case VS:
		m_pPlayer1->GetComponent<fuel::RigidBody2D>()->SetPosition(fuel::Vector3(50.f, 50.f, 0.f));
		m_pPlayer2->GetComponent<fuel::RigidBody2D>()->SetPosition(fuel::Vector3(501.f, 50.f, 0.f));
		m_pPlayer1->SetActive(true);
		m_pPlayer2->SetActive(true);
		m_pPlayer2->SetTag("Enemy");
		m_pPlayer2->GetComponent<fuel::SpriteComponent>()->AddAnimation(15, 8);
		m_pPlayer2->GetComponent<fuel::SpriteComponent>()->SetDirectionIDs(15, 15);
		m_pPlayer2->GetComponent<fuel::SpriteComponent>()->SetAnimation(15);
		break;
	}
}

void BubbleBobble::UpdateMainMenu()
{
}

void BubbleBobble::UpdateLevelOne()
{
	//m_CurrentTimer += Time::GetDeltaTime();
	const bool isOnEdge{ m_EnemiesLevelOne[2]->GetComponent<fuel::RigidBody2D>()->IsOnEdge() };
	if (isOnEdge)
		fuel::Logger::LogInfo("Enemy is on edge");
	
	if (m_CurrentTimer > 5.f)
	{
		m_CurrentTimer = 0.f;
		SwitchToScene("Level_Two");
	}
}

void BubbleBobble::UpdateLevelTwo()
{
	m_CurrentTimer += Time::GetDeltaTime();
	if (m_CurrentTimer > 5.f)
	{
		m_CurrentTimer = 0.f;
		SwitchToScene("Level_Three");
	}
}

void BubbleBobble::UpdateLevelThree()
{
	m_CurrentTimer += Time::GetDeltaTime();
	if (m_CurrentTimer > 5.f)
	{
		m_CurrentTimer = 0.f;
		SwitchToScene("MainMenu");
	}
}
