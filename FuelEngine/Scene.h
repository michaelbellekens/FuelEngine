#pragma once
#include "SceneManager.h"
#include "FixedAllocator.h"
#include "RenderComponent.h"
#include "Transform.h"

namespace fuel
{
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

		const std::string& GetName() const;

		// Editor GUI
		void DrawGameObjects();
		void DrawComponents();

	private:
		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::vector<BaseCollider*> m_AllColliders{};
		
		static unsigned int m_IdCounter;
		static size_t m_SelectedGameObject;
	};

}
