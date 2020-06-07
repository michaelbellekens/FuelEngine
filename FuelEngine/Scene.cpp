#include "FuelEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace fuel;

unsigned int Scene::m_IdCounter = 0;
size_t Scene::m_SelectedGameObject = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
{}

Scene::~Scene()
{
}

const std::string& fuel::Scene::GetName() const
{
	return m_Name;
}

void fuel::Scene::DrawGameObjects()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		if (ImGui::Selectable(m_Objects[idx]->GetName().c_str(), m_SelectedGameObject == idx))
			m_SelectedGameObject = idx;
	}
}

void fuel::Scene::DrawComponents()
{
	m_Objects[m_SelectedGameObject]->DrawComponents();
}

void Scene::AddToScene(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
	object->AttachScene(this);
}

void fuel::Scene::Initialize()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		m_Objects[idx]->Initialize();
	}
}

void Scene::Start()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		m_Objects[idx]->Start();
	}
}

void Scene::Update()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		m_Objects[idx]->Update();
	}
}

void fuel::Scene::FixedUpdate()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		m_Objects[idx]->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		m_Objects[idx]->Render();
	}
}

void fuel::Scene::AddCollider(BaseCollider* collider)
{
	const std::vector<BaseCollider*>::iterator it = std::find(m_AllColliders.begin(), m_AllColliders.end(), collider);

	if (it == m_AllColliders.end())
		m_AllColliders.push_back(collider);
}

const std::vector<BaseCollider*>& fuel::Scene::GetAllColliders() const
{
	return m_AllColliders;
}
