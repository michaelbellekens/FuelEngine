#include "FuelEnginePCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"

#include "FileManager.h"
#include "Renderer.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"

fuel::TextComponent::TextComponent()
	: m_NeedsUpdate{ true }
	, m_Text{ ""}
	, m_Color{ Color4() }
	, m_Font{ nullptr }
	, m_FontName{ "" }
	, m_FontSize{ 36 }
	, m_Texture{ nullptr }
	, m_pGameObject{ nullptr }
	, m_pTransform{ nullptr }
	, m_ID{"" }
	, m_Position{ 0.f, 0.f }
{
	// Set default font
	m_Font = ResourceManager::LoadFont("Lingua.otf", 36);;
	m_Text = "Change me";
	m_FontName = m_Font->GetName();
}

void fuel::TextComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::TextComponent::OnStart()
{
	m_pTransform = m_pGameObject->GetComponent<Transform>();
}

void fuel::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		// If string is empty render space
		if (m_Text.empty())
			m_Text = " ";

		const Uint8 r{ static_cast<Uint8>(m_Color.r * 255.f) };
		const Uint8 g{ static_cast<Uint8>(m_Color.g * 255.f) };
		const Uint8 b{ static_cast<Uint8>(m_Color.b * 255.f) };
		const Uint8 a{ static_cast<Uint8>(m_Color.a * 255.f) };
		const SDL_Color color = { r,g,b, a }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void fuel::TextComponent::Render() const
{
	if (m_Texture != nullptr && m_pTransform != nullptr)
	{
		auto pos = m_pTransform->GetPosition() + m_Position;
		Renderer::RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void fuel::TextComponent::FixedUpdate()
{
}

// This implementation uses the "dirty flag" pattern
void fuel::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void fuel::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}

void fuel::TextComponent::SetPosition(const float x, const float y)
{
	m_Position = Vector2(x, y);
}

void fuel::TextComponent::SetSize(unsigned int fontSize)
{
	m_FontSize = static_cast<int>(fontSize);
	m_Font = ResourceManager::LoadFont("Fonts/" + m_FontName, fontSize);
	m_NeedsUpdate = true;
}

void fuel::TextComponent::SetColor(const Color4& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

void fuel::TextComponent::SetColor(const float r, const float g, const float b, const float a)
{
	m_Color = Color4(r, g, b, a);
	m_NeedsUpdate = true;
}

void fuel::TextComponent::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::TextComponent::GetGameObject() const
{
	return m_pGameObject;
}

void fuel::TextComponent::SetTransform(Transform* transComp)
{
	m_pTransform = transComp;
}

size_t fuel::TextComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::TextComponent::DrawGUI()
{
	ImGui::Text("Text Component");
	ImGui::Spacing();

	// Text0.
	ImGui::Text("Text:");
	ImGui::SameLine(100);
	const unsigned int numChars = 255;
	char nameBuffer[numChars];
	strcpy_s(nameBuffer, m_Text.c_str());
	const std::string rightVibLabel{ "##TextInputLabel" + m_ID };
	ImGui::PushItemWidth(200);
	ImGui::InputText(rightVibLabel.c_str(), nameBuffer, 100);
	ImGui::PopItemWidth();

	if (nameBuffer != m_Text)
	{
		SetText(nameBuffer);
	}

	const std::string posLabelX{ "##TextComponentPosX_" + m_ID };
	const std::string posLabelY{ "##TextComponentPosY_" + m_ID };

	ImGui::Text("Position:");

	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(100);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelX.c_str(), &m_Position.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(190);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelY.c_str(), &m_Position.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	// Text Color
	ImGui::Text("Text Color:");
	ImGui::SameLine(100);
	float newColor[4] = { m_Color.r, m_Color.g, m_Color.b, m_Color.a };
	const std::string colorPickLabel{ "##ColorPickerLabel" + m_ID };
	ImGui::ColorEdit4(colorPickLabel.c_str(), newColor);
	SetColor(newColor[0], newColor[1], newColor[2], newColor[3]);
	
	// Font Size
	ImGui::Text("Font size:");
	ImGui::SameLine(100);
	ImGui::PushItemWidth(200);
	const std::string fontSizeLabel{ "##FontSizeLabel" + m_ID };
	const int oldSize{ m_FontSize };
	ImGui::InputInt(fontSizeLabel.c_str(), &m_FontSize, 1, 5);
	ImGui::PopItemWidth();
	if (m_FontSize != oldSize)
		SetSize(m_FontSize);
	
	// Font type
	ImGui::Text("Font name:");
	ImGui::SameLine(100);
	char fontBuffer[numChars];
	strcpy_s(fontBuffer, m_FontName.c_str());
	const std::string fontNameLabel{ "##FontNameInputLabel" + m_ID };
	ImGui::PushItemWidth(200);
	ImGui::InputText(fontNameLabel.c_str(), fontBuffer, 50);
	ImGui::PopItemWidth();

	const std::string subFolder{ "Fonts/" };
	if (ResourceManager::DoesFileExist(subFolder + fontBuffer) && fontBuffer != m_FontName)
	{
		SetFont(ResourceManager::LoadFont(fontBuffer, 36));
		m_FontName = m_Font->GetName();
	}
}

const std::string& fuel::TextComponent::GetID() const
{
	return m_ID;
}

fuel::ComponentType fuel::TextComponent::GetCompType() const
{
	return ComponentType::TEXTRENDERER;
}

void fuel::TextComponent::Safe(std::ofstream& binStream) const
{
	FileManager::WriteString(binStream, m_Text);
	binStream.write((const char*)&m_Color, sizeof(Color4));
	FileManager::WriteString(binStream, m_FontName);
	binStream.write((const char*)&m_FontSize, sizeof(int));
	
	binStream.write((const char*)&m_Position, sizeof(Vector2));
}

void fuel::TextComponent::Load(std::ifstream& binStream)
{
	FileManager::ReadString(binStream, m_Text);
	binStream.read((char*)&m_Color, sizeof(Color4));
	FileManager::ReadString(binStream, m_FontName);
	binStream.read((char*)&m_FontSize, sizeof(int));
	SetFont(ResourceManager::LoadFont(m_FontName, m_FontSize));

	binStream.read((char*)&m_Position, sizeof(Vector2));
	m_NeedsUpdate = true;
}

void fuel::TextComponent::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::TextComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::TextComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::TextComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::TextComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::TextComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}
