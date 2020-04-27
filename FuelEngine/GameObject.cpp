#include "FuelEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

fuel::GameObject::GameObject()
	: m_Transform{nullptr}
	, m_pComponents{}
	, m_pLinkedScene(nullptr)
	, m_Name{ "New GameObject" }
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
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Update();
	}
}

void fuel::GameObject::FixedUpdate()
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->FixedUpdate();
	}
}

void fuel::GameObject::Render() const
{
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Render();
	}
}

void fuel::GameObject::AttachScene(Scene* scene)
{
	m_pLinkedScene = scene;
}

fuel::Scene* fuel::GameObject::GetScene()
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

void fuel::GameObject::DrawComponents()
{
	//for (BaseComponent* comp : m_pComponents)
	for (size_t idx{ 0 }; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->DrawGUI();
		ImGui::Separator();
	}
}
