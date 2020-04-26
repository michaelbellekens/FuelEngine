#include "FuelEnginePCH.h"
#include "Transform.h"
#include "GameObject.h"
#include "SphereCollider.h"

#include <SDL.h>

#include "InputManager.h"
#include "Logger.h"
#include "Renderer.h"


void fuel::SphereCollider::Initialize()
{
	SetRadius(100.f);
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::SphereCollider::OnStart()
{
	m_pTransform = m_pGameObject->GetTransform();
}

void fuel::SphereCollider::Update()
{
}

void fuel::SphereCollider::FixedUpdate()
{
	//const Rectf testRect{ InputManager::GetMousePosition(), Vector2(50.f, 50.f) };
	//
	//if (IsColliding(testRect))
	//{
	//	Logger::LogInfo("Mouse is overlapping with collider");
	//}
}

void fuel::SphereCollider::Render() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>((m_pTransform->GetPosition().x + m_Dimensions.x) - m_Dimensions.radius);
	rect.y = static_cast<int>((m_pTransform->GetPosition().y + m_Dimensions.y) - m_Dimensions.radius);
	rect.w = static_cast<int>(m_Dimensions.radius * 2.f);
	rect.h = static_cast<int>(m_Dimensions.radius * 2.f);

	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(Renderer::GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 0, 0, 255);

	// DEBUG
	//SDL_Rect testRect;
	//testRect.x = static_cast<int>(InputManager::GetMousePosition().x);
	//testRect.y = static_cast<int>(InputManager::GetMousePosition().y);
	//testRect.w = 50;
	//testRect.h = 50;

	//SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 255, 0, 255);
	//SDL_RenderDrawRect(Renderer::GetSDLRenderer(), &testRect);
	//SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 0, 0, 255);
	// ------
}

void fuel::SphereCollider::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::SphereCollider::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::SphereCollider::GetType()
{
	return typeid(this).hash_code();
}

bool fuel::SphereCollider::IsTrigger() const
{
	return m_IsTrigger;
}

void fuel::SphereCollider::SetIsTrigger(const bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

bool fuel::SphereCollider::IsColliding(const Spheref& shape) const
{
	const float distanceSqr{ (m_Dimensions.x - shape.x) * (m_Dimensions.x - shape.x) + (m_Dimensions.y - shape.y) * (m_Dimensions.y - shape.y) };
	const float sumRadiusSqr{ (m_Dimensions.radius + shape.radius) * (m_Dimensions.radius + shape.radius) };

	if (distanceSqr <= sumRadiusSqr)
		return true;
	
	return false;
}

bool fuel::SphereCollider::IsColliding(const Rectf& rect) const
{
	const Vector2 actualPos{ m_Dimensions.x + m_pTransform->GetPosition().x, m_Dimensions.y + m_pTransform->GetPosition().y };
	
	const float distX = abs(actualPos.x - rect.x - rect.width / 2);
	const float distY = abs(actualPos.y - rect.y - rect.height / 2);

	if (distX > rect.width / 2 + m_Dimensions.radius)
		return false;
	if (distY > rect.height / 2 + m_Dimensions.radius)
		return false;

	if (distX <= rect.width / 2)
		return true;
	if (distY <= rect.height / 2)
		return true;

	const float dx = distX - rect.width / 2;
	const float dy = distY - rect.height / 2;
	
	return dx * dx + dy * dy <= m_Dimensions.radius * m_Dimensions.radius;
}

bool fuel::SphereCollider::IsColliding(const Vector2& point) const
{
	const Vector2 actualPos{ m_Dimensions.x + m_pTransform->GetPosition().x, m_Dimensions.y + m_pTransform->GetPosition().y };
	if ((point.x - actualPos.x) * (point.x - actualPos.x) +
		(point.y - actualPos.y) * (point.y - actualPos.y) <= m_Dimensions.radius * m_Dimensions.radius)
	{
		return true;
	}
	return false;
}

fuel::Spheref fuel::SphereCollider::GetDimensions() const
{
	return m_Dimensions;
}

void fuel::SphereCollider::SetDimensions(const Spheref& shape)
{
	m_Dimensions = shape;
}

void fuel::SphereCollider::SetRadius(const float radius)
{
	m_Dimensions.radius = radius;
}

void fuel::SphereCollider::DrawGUI()
{
	ImGui::Text("Sphere Collider2D Component");
	ImGui::Spacing();
	
	// Position -----------------------------------------------------
	const std::string labelPosX{ "##SphereCollider2D_X" + m_ID };
	const std::string labelPosY{ "##SphereCollider2D_Y" + m_ID };

	ImGui::Text("Position:");
	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelPosX.c_str(), &m_Dimensions.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelPosY.c_str(), &m_Dimensions.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Dimensions ---------------------------------------------------
	const std::string labelWidth{ "##SphereCollider2D_W" + m_ID };
	const std::string labelHeight{ "##SphereCollider2D_H" + m_ID };

	ImGui::Text("Dimensions:");
	ImGui::SameLine(95);
	ImGui::Text("Radius:");

	ImGui::SameLine(140);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelWidth.c_str(), &m_Dimensions.radius, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// IsTrigger ---------------------------------------------------
	const std::string labelTrigger{ "##SphereCollider_Trigger" + m_ID };
	ImGui::Text("Is Trigger");
	ImGui::SameLine(80);
	ImGui::Checkbox(labelTrigger.c_str(), &m_IsTrigger);
	// --------------------------------------------------------------
}

const std::string& fuel::SphereCollider::GetID() const
{
	return m_ID;
}
