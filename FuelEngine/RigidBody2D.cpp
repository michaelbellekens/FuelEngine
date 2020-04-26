#include "FuelEnginePCH.h"
#include "RigidBody2D.h"
#include "GameObject.h"

void fuel::RigidBody2D::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::RigidBody2D::OnStart()
{
	m_pTransform = m_pGameObject->GetTransform();
}

void fuel::RigidBody2D::Update()
{
}

void fuel::RigidBody2D::FixedUpdate()
{
}

void fuel::RigidBody2D::Render() const
{
}

void fuel::RigidBody2D::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::RigidBody2D::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::RigidBody2D::GetType()
{
	return typeid(this).hash_code();
}

void fuel::RigidBody2D::DrawGUI()
{
	ImGui::Text("RigidBody2D Component");
	ImGui::Spacing();
}

const std::string& fuel::RigidBody2D::GetID() const
{
	return m_ID;
}
