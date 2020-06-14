#include "FuelEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Button.h"
#include "Logger.h"
#include <algorithm>
#include "BaseCollider.h"

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

std::shared_ptr<SceneObject> fuel::Scene::FindObject(const std::string& objectName) const
{
	const auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [objectName](std::shared_ptr<SceneObject> object) {return object->GetName() == objectName; });
	if (it == m_Objects.end())
	{
		Logger::LogWarning("Object with the name \"" + objectName + "\" has not been found!");
		return nullptr;
	}
	return *it;
}

bool fuel::Scene::GetIsActive() const
{
	return m_IsActive;
}

unsigned int fuel::Scene::GetNumGameObjects() const
{
	return static_cast<unsigned int>(m_Objects.size());
}

std::vector<std::shared_ptr<SceneObject>>& fuel::Scene::GetSceneObjects()
{
	return m_Objects;
}

void fuel::Scene::DrawGameObjects()
{
	for (size_t idx{ 0 }; idx < m_Objects.size(); ++idx)
	{
		if (ImGui::Selectable(m_Objects[idx]->GetName().c_str(), m_SelectedGameObject == idx))
			m_SelectedGameObject = idx;
	}

	// Check that when scenes switch the index is still within bounds
	if (m_SelectedGameObject > m_Objects.size())
		m_SelectedGameObject = static_cast<int>(m_Objects.size()) - 1;

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

void fuel::Scene::RemoveFromScene(const std::string& objectName)
{
	/*const auto colliderIt = std::find_if(m_AllColliders.begin(), m_AllColliders.end(), [objectName](BaseCollider* collider) {return collider->GetGameObject()->GetName() == objectName; });
	if (colliderIt != m_AllColliders.end())
	{
		m_AllColliders.erase(colliderIt);
		
	}*/
	for (int i{ 0 }; i < static_cast<int>(m_AllColliders.size()); ++i)
	{
		if (m_AllColliders[i]->GetGameObject()->GetName() == objectName)
		{
			m_AllColliders[i] = nullptr;
			break;
		}
	}
	m_AllColliders.erase(std::remove(m_AllColliders.begin(), m_AllColliders.end(), nullptr), m_AllColliders.end());

	
	const auto objecIt = std::find_if(m_Objects.begin(), m_Objects.end(), [objectName](std::shared_ptr<SceneObject> object) {return object->GetName() == objectName; });
	if (objecIt != m_Objects.end())
	{
		m_Objects.erase(objecIt);
	}
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

void fuel::Scene::OnEnable()
{
	//Logger::LogInfo("Enabled scene \"" + m_Name + "\"");
	m_IsActive = true;
}

void fuel::Scene::OnDisable()
{
	//Logger::LogInfo("Disable scene \"" + m_Name + "\"");
	m_IsActive = false;
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

void fuel::Scene::AddButton(Button* pButton)
{
	m_pButtons.push_back(pButton);
}

void fuel::Scene::NextButton()
{
	const int numButtons{ static_cast<int>(m_pButtons.size()) };
	int currentButton{ 0 };
	
	for (Button* pButton : m_pButtons)
	{
		if (pButton->IsSelected())
		{
			currentButton = pButton->GetButtonID();
			pButton->SetSelected(false);
		}
	}

	++currentButton;
	currentButton %= numButtons;

	for (Button* pButton : m_pButtons)
	{
		if (pButton->GetButtonID() == currentButton)
			pButton->SetSelected(true);
	}
}

void fuel::Scene::PreviousButton()
{
	const int numButtons{ static_cast<int>(m_pButtons.size()) };
	int currentButton{ 0 };

	for (Button* pButton : m_pButtons)
	{
		if (pButton->IsSelected())
		{
			currentButton = pButton->GetButtonID();
			pButton->SetSelected(false);
		}
	}

	--currentButton;
	if (currentButton < 0)
		currentButton = numButtons - 1;

	for (Button* pButton : m_pButtons)
	{
		if (pButton->GetButtonID() == currentButton)
			pButton->SetSelected(true);
	}
}

void fuel::Scene::ExecuteButtonAction()
{
	for (Button* pButton : m_pButtons)
	{
		if (pButton->IsSelected())
		{
			pButton->ExecuteButtonAction();
			return;
		}
	}
}
