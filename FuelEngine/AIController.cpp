#include "FuelEnginePCH.h"
#include "AIController.h"

void fuel::AIController::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::AIController::OnStart()
{
}

void fuel::AIController::Update()
{
}

void fuel::AIController::FixedUpdate()
{
}

void fuel::AIController::Render() const
{
}

void fuel::AIController::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::AIController::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::AIController::GetType()
{
	return typeid(this).hash_code();
}

fuel::ComponentType fuel::AIController::GetCompType() const
{
	return ComponentType::AICONTROLLER;
}

void fuel::AIController::Safe(std::ofstream& binStream) const
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::AIController::Load(std::ifstream& binStream)
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::AIController::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::AIController::DrawGUI()
{
}

const std::string& fuel::AIController::GetID() const
{
	return m_ID;
}

