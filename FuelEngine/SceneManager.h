#pragma once
#include "Singleton.h"

namespace fuel
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		static Scene& CreateScene(const std::string& name) { return GetInstance().ICreateScene(name); }

		static void Initialize() { GetInstance().IInitialize(); }
		static void Start() { GetInstance().IStart(); }
		static void Update() { GetInstance().IUpdate(); }
		static void FixedUpdate() { GetInstance().IFixedUpdate(); }
		static void Render() { GetInstance().IRender(); }
		static void SetActiveScene(const std::string& sceneName) { GetInstance().ISetActiveScene(sceneName); }

		static void DrawGameObjects() { GetInstance().IDrawGameObjects(); }
		static void DrawComponents() { GetInstance().IDrawComponents(); }
	private:
		Scene& ICreateScene(const std::string& name);

		void IInitialize();
		void IStart();
		void IUpdate();
		void IFixedUpdate();
		void IRender() const;

		void ISetActiveScene(const std::string& sceneName);

		// Editor GUI
		void IDrawGameObjects();
		void IDrawComponents();
		
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}
