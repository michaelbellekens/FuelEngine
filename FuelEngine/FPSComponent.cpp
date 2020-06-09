#include "FuelEnginePCH.h"
#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Time.h"

fuel::FPSComponent::FPSComponent()
{
}

void fuel::FPSComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
	
	const auto textFont = ResourceManager::LoadFont("Lingua.otf", 36);

	const int fps{ int(1.f / Time::GetDeltaTime()) };
	std::string fpsCount{ std::to_string(fps) };
}

void fuel::FPSComponent::OnStart()
{
	m_pFPSCounter = m_pGameObject->GetComponent<TextComponent>();
	if (m_pFPSCounter)
	{
		m_pFPSCounter->SetText(m_fpsLabel + "potato");
		m_pFPSCounter->SetPosition(80, 80);
	}
}

void fuel::FPSComponent::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::FPSComponent::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::FPSComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::FPSComponent::Update()
{
	++m_RenderedFrames;
	m_UpdateTime += Time::GetDeltaTime();

	if (m_UpdateTime >= m_UpdateInterval)
	{
		m_pFPSCounter->SetText(m_fpsLabel + std::to_string(int(std::roundf(m_RenderedFrames / m_UpdateTime))));
		m_RenderedFrames = 0;
		m_UpdateTime = 0;
	}
	m_pFPSCounter->Update();
}

void fuel::FPSComponent::FixedUpdate()
{
}

void fuel::FPSComponent::Render() const
{
	m_pFPSCounter->Render();
}

void fuel::FPSComponent::Safe(std::ofstream& binStream) const
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::FPSComponent::Load(std::ifstream& binStream)
{
	UNREFERENCED_PARAMETER(binStream);
}

fuel::ComponentType fuel::FPSComponent::GetCompType() const
{
	return ComponentType::FPS;
}

void fuel::FPSComponent::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::FPSComponent::DrawGUI()
{
	ImGui::Text("FPS Component");
	ImGui::Spacing();

	const std::string updateIntervalLabel{ "##UpdateInterval" + m_ID };
	ImGui::Text("Update interval:");
	ImGui::SameLine(150);
	ImGui::PushItemWidth(200);
	ImGui::InputFloat(updateIntervalLabel.c_str(), &m_UpdateInterval, 0, 0, "%0.3f");
	ImGui::PopItemWidth();
}

const std::string& fuel::FPSComponent::GetID() const
{
	return m_ID;
}
