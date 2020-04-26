#include "FuelEnginePCH.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoxCollider.h"

#include <SDL.h>

#include "InputManager.h"
#include "Logger.h"
#include "Renderer.h"

void fuel::BoxCollider::Initialize()
{
	SetDimensions(Rectf(0.f, 0.f, 200.f, 200.f));
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::BoxCollider::OnStart()
{
	m_pTransform = m_pGameObject->GetTransform();
}

void fuel::BoxCollider::Update()
{
}

void fuel::BoxCollider::FixedUpdate()
{
	const Spheref testSphere{ InputManager::GetMousePosition(), 25.f };

	if (IsColliding(testSphere))
	{
		Logger::LogInfo("Sphere is Colliding with BoxCollider 2D!");
	}
	
}

void fuel::BoxCollider::Render() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(m_pTransform->GetPosition().x + m_Dimensions.x);
	rect.y = static_cast<int>(m_pTransform->GetPosition().y + m_Dimensions.y);
	rect.w = static_cast<int>(m_Dimensions.width);
	rect.h = static_cast<int>(m_Dimensions.height);
	
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(Renderer::GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 0, 0, 255);


	// DEBUG
	SDL_Rect testRect;
	testRect.x = static_cast<int>(InputManager::GetMousePosition().x - 25.f);
	testRect.y = static_cast<int>(InputManager::GetMousePosition().y - 25.f);
	testRect.w = 50;
	testRect.h = 50;

	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(Renderer::GetSDLRenderer(), &testRect);
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 0, 0, 255);
	// ------
}

void fuel::BoxCollider::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::BoxCollider::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::BoxCollider::GetType()
{
	return typeid(this).hash_code();
}

bool fuel::BoxCollider::IsTrigger() const
{
	return m_IsTrigger;
}

void fuel::BoxCollider::SetIsTrigger(const bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

bool fuel::BoxCollider::IsColliding(const Rectf& shape) const
{
	const Vector2 topLeft1{ m_pTransform->GetPosition().x + m_Dimensions.x, m_pTransform->GetPosition().y + m_Dimensions.y };
	const Vector2 topLeft2{ shape.x, shape.y };
	const Vector2 bottomRight1{ topLeft1.x + m_Dimensions.width, topLeft1.y + m_Dimensions.height };
	const Vector2 bottomRight2{ topLeft2.x + shape.width, topLeft2.y + shape.height };

	if (topLeft1.x > bottomRight2.x || topLeft2.x > bottomRight1.x)
	{
		return false;
	}
	if (topLeft1.y > bottomRight2.y || topLeft2.y > bottomRight1.y)
	{
		return false;
	}
	
	return true;
}

bool fuel::BoxCollider::IsColliding(const Spheref& sphere) const
{
	const Vector2 actualPos{ m_Dimensions.x + m_pTransform->GetPosition().x, m_Dimensions.y + m_pTransform->GetPosition().y };
	
	const float distX = abs(sphere.x - actualPos.x - m_Dimensions.width / 2);
	const float distY = abs(sphere.y - actualPos.y - m_Dimensions.height / 2);

	if (distX > m_Dimensions.width / 2 + sphere.radius) 
		return false;
	if (distY > m_Dimensions.height / 2 + sphere.radius)
		return false;

	if (distX <= m_Dimensions.width / 2)
		return true;
	if (distY <= m_Dimensions.height / 2)
		return true;

	const float dx = distX - m_Dimensions.width / 2;
	const float dy = distY - m_Dimensions.height / 2;
	
	return dx * dx + dy * dy <= sphere.radius * sphere.radius;
}

bool fuel::BoxCollider::IsColliding(const Vector2& point) const
{
	const float posX{ m_pTransform->GetPosition().x + m_Dimensions.x };
	const float posY{ m_pTransform->GetPosition().y + m_Dimensions.y };
	const float width{ m_Dimensions.width };
	const float height{ m_Dimensions.height };
	
	return (point.x > posX&& point.x < (posX + width)) && (point.y > posY&& point.y < (posY + height));
}

fuel::Rectf fuel::BoxCollider::GetDimensions() const
{
	return m_Dimensions;
}

void fuel::BoxCollider::SetDimensions(const Rectf& dimensions)
{
	m_Dimensions = dimensions;
}

void fuel::BoxCollider::DrawGUI()
{	
	ImGui::Text("Box Collider2D Component");
	ImGui::Spacing();

	// Position -----------------------------------------------------
	const std::string labelPosX{ "##BoxCollider2D_X" + m_ID };
	const std::string labelPosY{ "##BoxCollider2D_Y" + m_ID };
	
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
	const std::string labelWidth{ "##BoxCollider2D_W" + m_ID };
	const std::string labelHeight{ "##BoxCollider2D_H" + m_ID };
	
	ImGui::Text("Dimensions:");
	ImGui::SameLine(95);
	ImGui::Text("Width:");

	ImGui::SameLine(140);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelWidth.c_str(), &m_Dimensions.width, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(230);
	ImGui::Text("Height:");

	ImGui::SameLine(280);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelHeight.c_str(), &m_Dimensions.height, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// IsTrigger ---------------------------------------------------
	const std::string labelTrigger{ "##BoxCollider_Trigger" + m_ID };
	ImGui::Text("Is Trigger");
	ImGui::SameLine(80);
	ImGui::Checkbox(labelTrigger.c_str(), &m_IsTrigger);
	// --------------------------------------------------------------
}

const std::string& fuel::BoxCollider::GetID() const
{
	return m_ID;
}

bool fuel::BoxCollider::IsPointInSphere(const Spheref& sphere, const Vector2& point) const
{
	if ((point.x - sphere.x) * (point.x - sphere.x) +
		(point.y - sphere.y) * (point.y - sphere.y) <= sphere.radius * sphere.radius)
	{
		return true;
	}
	return false;
}
