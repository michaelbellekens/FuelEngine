#include "FuelEnginePCH.h"
#include "RenderComponent.h"

#include "FileManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Transform.h"

fuel::RenderComponent::RenderComponent()
	: m_Texture(nullptr)
	, m_pGameObject(nullptr)
	, m_ID{ "" }
	, m_TextureName{ "" }
{
}

void fuel::RenderComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::RenderComponent::OnStart()
{
	if (m_pGameObject)
		m_pTransform = m_pGameObject->GetTransform();
}

void fuel::RenderComponent::Update()
{
}

void fuel::RenderComponent::FixedUpdate()
{
}

void fuel::RenderComponent::Render() const
{
	const fuel::Vector3 pos = m_pTransform->GetPosition();
	fuel::Renderer::RenderTexture(*m_Texture, pos.x, pos.y);
}

void fuel::RenderComponent::SetGameObject(fuel::GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::RenderComponent::GetGameObject() const
{
	return m_pGameObject;
}

void fuel::RenderComponent::SetTransform(Transform* transComp)
{
	m_pTransform = transComp;
}

size_t fuel::RenderComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::RenderComponent::SetTexture(const std::string& filename)
{
	m_TextureName = filename;
	m_Texture = fuel::ResourceManager::LoadTexture(filename);
}

void fuel::RenderComponent::Safe(std::ofstream& binStream) const
{
	FileManager::WriteString(binStream, m_TextureName);
}

void fuel::RenderComponent::Load(std::ifstream& binStream)
{
	std::string textureName{};
	FileManager::ReadString(binStream, textureName);

	SetTexture(textureName);
}

fuel::ComponentType fuel::RenderComponent::GetCompType() const
{
	return ComponentType::RENDERER;
}

void fuel::RenderComponent::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RenderComponent::DrawGUI()
{
	ImGui::Text("Renderer Component");
	ImGui::Spacing();

	const std::string textureLabel{"##TextureName" + m_ID };
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
}

const std::string& fuel::RenderComponent::GetID() const
{
	return m_ID;
}
