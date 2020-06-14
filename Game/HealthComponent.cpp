#include "FuelEnginePCH.h"
#include "HealthComponent.h"

fuel::HealthComponent::HealthComponent()
{
}

void fuel::HealthComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::HealthComponent::OnStart()
{
}

void fuel::HealthComponent::Update()
{
}

void fuel::HealthComponent::FixedUpdate()
{
}

void fuel::HealthComponent::Render() const
{
}

void fuel::HealthComponent::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::HealthComponent::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::HealthComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::HealthComponent::Damage()
{
	--m_Lives;
	if (m_Lives < 0)
		m_Lives = 0;
}

int fuel::HealthComponent::GetNumberOfLives() const
{
	return m_Lives;
}

void fuel::HealthComponent::SetNUmberOfLives(const int lives)
{
	m_Lives = lives;
}

fuel::ComponentType fuel::HealthComponent::GetCompType() const
{
	return ComponentType::HEALTH;
}

void fuel::HealthComponent::Safe(std::ofstream& binStream) const
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::HealthComponent::Load(std::ifstream& binStream)
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::HealthComponent::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::HealthComponent::DrawGUI()
{
}

const std::string& fuel::HealthComponent::GetID() const
{
	return m_ID;
}
