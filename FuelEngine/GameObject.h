#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Scene.h"

namespace fuel
{
	class Texture2D;
	class BaseComponent;
	class GameObject : public SceneObject
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize() override;
		void Start() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void AttachScene(Scene* scene) override;

		template<typename T>
		T* AddComponent();
		template<typename T>
		T* GetComponent();
		
		void SetTransform(Transform* transform);
		Transform* GetTransform() const;

		void SetName(const std::string& name) override;
		std::string& GetName() override;

		// Editor GUI
		void DrawComponents() override;
		
	private:
		std::string m_Name;
		Transform* m_Transform;
		std::vector<BaseComponent*> m_pComponents;
		Scene* m_pLinkedScene;
	};

	template<typename T>
	T* GameObject::AddComponent()
	{		
		T* component = new T();
		component->SetGameObject(this);
		m_pComponents.push_back(component);
		return component;
	}

	template<typename T>
	T* GameObject::GetComponent()
	{
		for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
		{
			if (typeid(*m_pComponents[idx]) == typeid(T))
				return static_cast<T*>(m_pComponents[idx]);
		}
		return nullptr;
	}
}
