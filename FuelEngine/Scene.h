#pragma once
#include "Button.h"
#include "SceneManager.h"
#include "RenderComponent.h"

namespace fuel
{
	struct SceneData
	{
		SceneData()
			: numGameObjects(0)
			, numButtons(0)
		{}

		unsigned int numGameObjects;
		unsigned int numButtons;
	};
	
	class SceneObject;
	class BaseCollider;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		
		void AddToScene(const std::shared_ptr<SceneObject>& object);

		void Initialize();
		void Start();
		
		void Update();
		void FixedUpdate();
		void Render() const;

		void AddCollider(BaseCollider* collider);
		const std::vector<BaseCollider*>& GetAllColliders() const;

		void AddButton(Button* pButton);
		void NextButton();
		void PreviousButton();
		void ExecuteButtonAction();
		void HandleButtonEvent(ButtonAction action);
		
		const std::string& GetName() const;

		// Saving and Loading
		unsigned int GetNumGameObjects() const;
		std::vector<std::shared_ptr<SceneObject>>& GetSceneObjects();

		// Editor GUI
		void DrawGameObjects();
		void DrawComponents();

	private:
		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::vector<BaseCollider*> m_AllColliders{};
		std::vector<Button*> m_pButtons{};
		
		static unsigned int m_IdCounter;
		static size_t m_SelectedGameObject;
	};

}
