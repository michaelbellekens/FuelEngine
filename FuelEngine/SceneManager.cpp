#include "FuelEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Logger.h"

void fuel::SceneManager::IInitialize()
{
	for (size_t idx{ 0 }; idx < m_Scenes.size(); ++idx)
	{
		m_Scenes[idx]->Initialize();
	}

	if (m_Scenes.front() != nullptr)
	{
		SetActiveScene(m_Scenes.front()->GetName());
	}
	else
	{
		Logger::LogError("Game contains no scenes!");
	}
}

void fuel::SceneManager::IStart()
{
	for (size_t idx{ 0 }; idx < m_Scenes.size(); ++idx)
	{
		m_Scenes[idx]->Start();
	}
}

void fuel::SceneManager::IUpdate()
{
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update();
	//}
	m_ActiveScene->Update();
}

void fuel::SceneManager::IFixedUpdate()
{
	//std::cout << "FixedUpdate" << std::endl;
	m_ActiveScene->FixedUpdate();
}

void fuel::SceneManager::IRender() const
{
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
	m_ActiveScene->Render();
}

void fuel::SceneManager::ISetActiveScene(const std::string& sceneName)
{
	std::vector<std::shared_ptr<Scene>>::iterator newActiveScene{ std::find_if(m_Scenes.begin(), m_Scenes.end(), [sceneName](std::shared_ptr<Scene> scene) { return scene->GetName() == sceneName; }) };
	if (newActiveScene != m_Scenes.end())
	{
		m_ActiveScene = *newActiveScene;
		Logger::LogInfo("Scene \"" + sceneName + "\" is new active scene.");
	}
	else
	{
		Logger::LogWarning("Scene \"" + sceneName + "\" has not been found!");
	}
}

void fuel::SceneManager::IDrawGameObjects()
{
	m_ActiveScene->DrawGameObjects();
}

void fuel::SceneManager::IDrawComponents()
{
	m_ActiveScene->DrawComponents();
}

fuel::Scene& fuel::SceneManager::ICreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

