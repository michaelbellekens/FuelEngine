#include "FuelEnginePCH.h"
#include "SpriteComponent.h"

#include <SDL.h>

#include "FileManager.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Transform.h"

fuel::SpriteComponent::SpriteComponent()
	: m_Texture(nullptr)
	, m_pTransform(nullptr)
	, m_pGameObject(nullptr)
	, m_ID{ "" }
	, m_TextureName{ "" }
	, m_AnimationLoops()
	, m_Cols(0)
	, m_Rows(0)
	, m_CurrentAnimFrame(0)
	, m_CurrentAnimation(0)
	, m_AnimTime(0.f)
	, m_CurrentAnimTime(0.f)
	, m_Scale(1.f, 1.f)
{
}

void fuel::SpriteComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::SpriteComponent::OnStart()
{
	if (m_pGameObject)
		m_pTransform = m_pGameObject->GetTransform();
}

void fuel::SpriteComponent::Update()
{
	if (m_AnimationLoops.empty())
		return;
	
	m_CurrentAnimTime += Time::GetDeltaTime();
	if (m_CurrentAnimTime >= m_AnimTime)
	{
		m_CurrentAnimTime = 0.f;
		++m_CurrentAnimFrame;
		m_CurrentAnimFrame %= m_AnimationLoops.at(m_CurrentAnimation) - 1;
	}
}

void fuel::SpriteComponent::FixedUpdate()
{
}

void fuel::SpriteComponent::Render() const
{
	int width{};
	int height{};
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	
	SDL_Rect destRect;
	destRect.x = static_cast<int>(m_pTransform->GetPosition().x);
	destRect.y = static_cast<int>(m_pTransform->GetPosition().y);
	destRect.w = static_cast<int>(width / m_AnimationLoops.at(m_CurrentAnimation) * m_Scale.x);
	destRect.h = static_cast<int>((height / m_Rows) * m_Scale.y);

	SDL_Rect srcRect;
	srcRect.x = width / m_AnimationLoops.at(m_CurrentAnimation) * m_CurrentAnimFrame;
	srcRect.y = (height / m_Rows) * m_CurrentAnimation;
	srcRect.w = width / m_AnimationLoops.at(m_CurrentAnimation);
	srcRect.h = height / m_Rows;

	Renderer::RenderSprite(*m_Texture, destRect, srcRect);
}

void fuel::SpriteComponent::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::SpriteComponent::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::SpriteComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::SpriteComponent::SetAnimation(const int animID)
{
	m_CurrentAnimation = animID;
	m_CurrentAnimFrame = 0;
	m_CurrentAnimTime = 0.f;
}

void fuel::SpriteComponent::SetColumns(const int col)
{
	m_Cols = col;
}

void fuel::SpriteComponent::SetRows(const int row)
{
	m_Rows = row;
}

void fuel::SpriteComponent::SetTexture(const std::string& filename)
{
	m_TextureName = filename;
	m_Texture = fuel::ResourceManager::LoadTexture(filename);
}

void fuel::SpriteComponent::AddAnimation(const int animID, const int numFrames)
{
	m_AnimationLoops.emplace(std::make_pair(animID, numFrames));
}

void fuel::SpriteComponent::SetAnimTime(const float animTime)
{
	m_AnimTime = animTime;
}

void fuel::SpriteComponent::SetScale(const float x, const float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void fuel::SpriteComponent::Safe(std::ofstream& binStream) const
{
	FileManager::WriteString(binStream, m_TextureName);
	binStream.write((const char*)&m_Cols, sizeof(int));
	binStream.write((const char*)&m_Rows, sizeof(int));
	binStream.write((const char*)&m_CurrentAnimFrame, sizeof(int));
	binStream.write((const char*)&m_CurrentAnimation, sizeof(int));
	binStream.write((const char*)&m_AnimTime, sizeof(float));
	binStream.write((const char*)&m_Scale.x, sizeof(float));
	binStream.write((const char*)&m_Scale.y, sizeof(float));

	unsigned int numAnimations{ m_AnimationLoops.size() };
	binStream.write((const char*)&numAnimations, sizeof(unsigned int));

	for (std::pair<int, int> animLoop : m_AnimationLoops)
	{
		binStream.write((const char*)&animLoop.first, sizeof(int));
		binStream.write((const char*)&animLoop.second, sizeof(int));
	}
}

void fuel::SpriteComponent::Load(std::ifstream& binStream)
{
	std::string textureName{};
	FileManager::ReadString(binStream, textureName);

	SetTexture(textureName);

	binStream.read((char*)&m_Cols, sizeof(int));
	binStream.read((char*)&m_Rows, sizeof(int));
	binStream.read((char*)&m_CurrentAnimFrame, sizeof(int));
	binStream.read((char*)&m_CurrentAnimation, sizeof(int));
	binStream.read((char*)&m_AnimTime, sizeof(float));
	binStream.read((char*)&m_Scale.x, sizeof(float));
	binStream.read((char*)&m_Scale.y, sizeof(float));

	unsigned int numAnimations{};
	binStream.read((char*)&numAnimations, sizeof(unsigned int));

	for (unsigned int i{ 0 }; i < numAnimations; ++i)
	{
		int keyID{};
		binStream.read((char*)&keyID, sizeof(int));
		int animFrames{};
		binStream.read((char*)&animFrames, sizeof(int));

		m_AnimationLoops.emplace(std::make_pair(keyID, animFrames));
	}
}

fuel::ComponentType fuel::SpriteComponent::GetCompType() const
{
	return ComponentType::SPRITERENDERER;
}

void fuel::SpriteComponent::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::SpriteComponent::DrawGUI()
{
	ImGui::Text("Sprite Component");
	ImGui::Spacing();

	const std::string textureLabel{ "##TextureName" + m_ID };
	const unsigned int numChars = 255;
	char nameBuffer[numChars];
	strcpy_s(nameBuffer, m_TextureName.c_str());

	ImGui::Text("Texture file");
	ImGui::SameLine(100);
	ImGui::PushItemWidth(200);
	ImGui::InputText(textureLabel.c_str(), nameBuffer, numChars);
	ImGui::PopItemWidth();

	if (ResourceManager::DoesFileExist(nameBuffer) && nameBuffer != m_TextureName)
	{
		SetTexture(nameBuffer);
		m_TextureName = nameBuffer;
	}

	// Dimensions ---------------------------------------------------
	const std::string labelCol{ "##SpriteComponentCol" + m_ID };
	const std::string labelRow{ "##SpriteComponentRow" + m_ID };

	ImGui::Text("Rows and Cols:");
	ImGui::SameLine(120);
	ImGui::Text("Rows:");

	ImGui::SameLine(165);
	ImGui::PushItemWidth(80);
	ImGui::InputInt(labelRow.c_str(), &m_Rows, 0, 0);
	ImGui::PopItemWidth();

	ImGui::SameLine(255);
	ImGui::Text("Col:");

	ImGui::SameLine(300);
	ImGui::PushItemWidth(80);
	ImGui::InputInt(labelCol.c_str(), &m_Cols, 0, 0);
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// AnimationID --------------------------------------------------
	const std::string labelAnimID{ "##SpriteComponentAnimID" + m_ID };

	ImGui::Text("Animation ID:");
	ImGui::SameLine(120);
	ImGui::Text("ID:");

	ImGui::SameLine(165);
	ImGui::PushItemWidth(80);
	ImGui::InputInt(labelAnimID.c_str(), &m_CurrentAnimation, 0, 0);
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Animation Time -----------------------------------------------
	const std::string labelAnimTime{ "##SpriteComponentAnimTime" + m_ID };

	ImGui::Text("Animation Time:");
	ImGui::SameLine(120);
	ImGui::Text("Sec:");

	ImGui::SameLine(165);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelAnimTime.c_str(), &m_AnimTime, 0, 0, "%.2f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Animation Scale ----------------------------------------------
	const std::string labelScaleX{ "##SpriteComponent_ScaleX" + m_ID };
	const std::string labelScaleY{ "##SpriteComponent_ScaleY" + m_ID };

	ImGui::Text("Scale:");
	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelScaleX.c_str(), &m_Scale.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(labelScaleY.c_str(), &m_Scale.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Animations----------------------------------------------------
	ImGui::Text("Animation List:");
	
	int animIdx{ 0 };
	for(std::pair<int, int> animLoop : m_AnimationLoops)
	{
		const std::string labelAnimationID{ "##SpriteComponent_AnimId" + std::to_string(animIdx) + m_ID };
		const std::string labelAnimFrames{ "##SpriteComponent_AnimFrames" + std::to_string(animIdx) + m_ID };

		ImGui::Text("Animation:");
		ImGui::SameLine(95);
		ImGui::Text("ID:");

		ImGui::SameLine(140);
		ImGui::PushItemWidth(80);
		ImGui::InputInt(labelAnimationID.c_str(), &animLoop.first, 0, 0);
		ImGui::PopItemWidth();

		ImGui::SameLine(230);
		ImGui::Text("Frames:");

		ImGui::SameLine(280);
		ImGui::PushItemWidth(80);
		ImGui::InputInt(labelAnimFrames.c_str(), &animLoop.second, 0, 0);
		ImGui::PopItemWidth();
		++animIdx;
	}
	// --------------------------------------------------------------
}

const std::string& fuel::SpriteComponent::GetID() const
{
	return m_ID;
}
