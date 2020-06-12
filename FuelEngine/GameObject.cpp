#include "FuelEnginePCH.h"
#include "GameObject.h"

#include "Scene.h"
#include "Transform.h"
#include "SoundManager.h"
#include "BaseComponent.h"
#include "Logger.h"
#include "BaseCollider.h"

fuel::GameObject::GameObject()
	: m_Name{ "New GameObject" }
	, m_Tag{""}
	, m_pComponents{}
	, m_Transform{nullptr}
	, m_pLinkedScene(nullptr)
{
}

fuel::GameObject::~GameObject()
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		SafeDelete(m_pComponents[idx]);
	}
}

void fuel::GameObject::Initialize()
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Initialize();
	}
}

void fuel::GameObject::Start()
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->OnStart();
	}
}

void fuel::GameObject::Update()
{
	if (!m_IsActive)
		return;
	
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Update();
	}
}

void fuel::GameObject::FixedUpdate()
{
	if (!m_IsActive)
		return;
	
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->FixedUpdate();
	}
}

void fuel::GameObject::Render() const
{
	if (!m_IsActive)
		return;
	
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Render();
	}
}

void fuel::GameObject::AttachScene(Scene* scene)
{
	m_pLinkedScene = scene;
}

fuel::Scene* fuel::GameObject::GetScene() const
{
	return m_pLinkedScene;
}

void fuel::GameObject::SetTransform(Transform* transform)
{
	m_Transform = transform;
}

fuel::Transform* fuel::GameObject::GetTransform() const
{
	return m_Transform;
}

void fuel::GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

std::string& fuel::GameObject::GetName()
{
	return m_Name;
}

void fuel::GameObject::SetTag(const std::string& tagName)
{
	m_Tag = tagName;
}

std::string fuel::GameObject::GetTag() const
{
	return m_Tag;
}

bool fuel::GameObject::CompareTag(const std::string& tagName) const
{
	return m_Tag == tagName;
}

void fuel::GameObject::SetActive(const bool isActive)
{
	m_IsActive = isActive;
}

bool fuel::GameObject::GetIsActive() const
{
	return m_IsActive;
}

fuel::ObjectType fuel::GameObject::GetObjectType() const
{
	return ObjectType::GAMEOBJECT;
}

fuel::GameObjectData fuel::GameObject::GetGameObjectData() const
{
	GameObjectData data{};
	data.numComponents = m_pComponents.size();

	for (unsigned int i{ 0 }; i < m_pComponents.size(); ++i)
		data.componentTypes.push_back(m_pComponents[i]->GetCompType());

	return data;
}

std::vector<fuel::BaseComponent*> fuel::GameObject::GetComponents() const
{
	return m_pComponents;
}

void fuel::GameObject::OnCollisionEnter(BaseCollider* other)
{
	//Logger::LogInfo("CollisionEnter with:" + other->GetGameObject()->GetName());
	//Logger::LogInfo("CollisionEnter with: " + other->GetGameObject()->GetTag());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnCollisionEnter(other);
	}
}

void fuel::GameObject::OnCollisionStay(BaseCollider* other)
{
	//Logger::LogInfo("CollisionStay with:" + other->GetGameObject()->GetName());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnCollisionStay(other);
	}
}

void fuel::GameObject::OnCollisionExit(BaseCollider* other)
{
	//Logger::LogInfo("CollisionExit with:" + other->GetGameObject()->GetName());
	//Logger::LogInfo("CollisionExit with: " + other->GetGameObject()->GetTag());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnCollisionExit(other);
	}
}

void fuel::GameObject::OnTriggerEnter(BaseCollider* other)
{
	Logger::LogInfo("TriggerEnter with:" + other->GetGameObject()->GetName());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnTriggerEnter(other);
	}
}

void fuel::GameObject::OnTriggerStay(BaseCollider* other)
{
	Logger::LogInfo("TriggerStay with:" + other->GetGameObject()->GetName());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnTriggerStay(other);
	}
}

void fuel::GameObject::OnTriggerExit(BaseCollider* other)
{
	Logger::LogInfo("TriggerExit with:" + other->GetGameObject()->GetName());
	for (BaseComponent* pBaseComponent : m_pComponents)
	{
		pBaseComponent->OnTriggerExit(other);
	}
}

void fuel::GameObject::DrawComponents()
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->DrawGUI();
		ImGui::Separator();
	}
}
