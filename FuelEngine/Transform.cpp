#include "FuelEnginePCH.h"
#include "Transform.h"
#include "GameObject.h"
#include "EngineSettings.h"

fuel::Transform::Transform()
	: m_pGameObject{ nullptr }
	, m_Position{}
	, m_ID{ "" }
{
	
}

fuel::Transform::~Transform()
{
}

void fuel::Transform::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::Transform::Update()
{
}

void fuel::Transform::FixedUpdate()
{
}

void fuel::Transform::Render() const
{
}

void fuel::Transform::OnStart()
{
}

void fuel::Transform::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
	parent->SetTransform(this);
}

fuel::GameObject* fuel::Transform::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::Transform::GetType()
{
	return typeid(this).hash_code();
}

const fuel::Vector3& fuel::Transform::GetPosition() const
{
	return m_Position;
}

void fuel::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void fuel::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void fuel::Transform::SetPosition(const Vector3& newPosition)
{
	m_Position = newPosition;
}

void fuel::Transform::SetPosition(const Vector2& newPosition)
{
	SetPosition(newPosition.x, newPosition.y);
}

void fuel::Transform::DrawGUI()
{
	const std::string posLabelX{ "##TransformPosX_" + m_ID };
	const std::string posLabelY{ "##TransformPosY_" + m_ID };
	const std::string posLabelZ{ "##TransformPosZ_" + m_ID };
	
	ImGui::Text("Transform Component");
	ImGui::Text("Position:");

	ImGui::SameLine(80);
	ImGui::Text("X:");
	
	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelX.c_str(), &m_Position.x,0, 0 ,"%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");
	
	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelY.c_str(), &m_Position.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(290);
	ImGui::Text("Z:");

	ImGui::SameLine(305);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelZ.c_str(), &m_Position.z, 0, 0, "%.1f");
	ImGui::PopItemWidth();	
}

const std::string& fuel::Transform::GetID() const
{
	return m_ID;
}
