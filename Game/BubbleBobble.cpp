#include "FuelEnginePCH.h"
#include "BubbleBobble.h"

#include "FileManager.h"
#include "Logger.h"
#include "SceneManager.h"

BubbleBobble::BubbleBobble()
	: m_MainMenuScene(fuel::SceneManager::CreateScene("MainMenu"))
	, m_LevelOneScene(fuel::SceneManager::CreateScene("Level_One"))
	, m_LevelTwoScene(fuel::SceneManager::CreateScene("Level_Two"))
	, m_LevelThreeScene(fuel::SceneManager::CreateScene("Level_Three"))
{}

BubbleBobble::~BubbleBobble()
{
}

void BubbleBobble::Initialize()
{
	fuel::Logger::LogInfo("Game Initialize");
	LoadScenes();
}

void BubbleBobble::Update()
{
	fuel::Logger::LogInfo("Game Update");
}

void BubbleBobble::FixedUpdate()
{
	fuel::Logger::LogInfo("Game FixedUpdate");
}

void BubbleBobble::Draw()
{
	fuel::Logger::LogInfo("Game Draw");
}

void BubbleBobble::LoadScenes()
{
	fuel::FileManager::LoadScene(&m_MainMenuScene, "Level_MainMenu");
	fuel::FileManager::LoadScene(&m_MainMenuScene, "Level_LevelOne");
	fuel::FileManager::LoadScene(&m_MainMenuScene, "Level_LevelTwo");
	fuel::FileManager::LoadScene(&m_MainMenuScene, "Level_LevelThree");
}
