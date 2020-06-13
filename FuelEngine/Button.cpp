#include "FuelEnginePCH.h"
#include "Button.h"

#include "InputManager.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Scene.h"

fuel::Button::Button()
	: m_Name("New Button")
	, m_Tag("Button")
	, m_pTransform(nullptr)
	, m_pRenderComponent(nullptr)
	, m_pTextComponent(nullptr)
	, m_pLinkedScene(nullptr)
	, m_IsActive(true)
	, m_IsTriggered(false)
	, m_ButtonID(0)
	, m_IsSelected(true)
	, m_ButtonAction(ButtonAction::QUIT)
{
	m_pTransform = new Transform();
	m_pRenderComponent = new RenderComponent();
	m_pTextComponent = new TextComponent();
}

fuel::Button::~Button()
{
	SafeDelete(m_pTransform);
	SafeDelete(m_pRenderComponent);
	SafeDelete(m_pTextComponent);
}

void fuel::Button::Initialize()
{
	m_pTextComponent->SetTransform(m_pTransform);
	m_pRenderComponent->SetTransform(m_pTransform);
}

void fuel::Button::Start()
{
}

void fuel::Button::Update()
{
	if (m_IsSelected)
	{
		m_pTextComponent->SetColor(0.30588f, 0.02745f, 0.37647f, 1.f);
	}
	else
		m_pTextComponent->SetColor(99.f / 255.f, 75.f / 255.f, 98.f / 255.f, 1.f);
	
	m_pTransform->Update();
	m_pRenderComponent->Update();
	m_pTextComponent->Update();
}

void fuel::Button::FixedUpdate()
{
}

void fuel::Button::Render() const
{
	if (!m_IsActive)
		return;
	
	m_pRenderComponent->Render();
	m_pTextComponent->Render();
}

void fuel::Button::AttachScene(Scene* scene)
{
	m_pLinkedScene = scene;
}

fuel::Scene* fuel::Button::GetScene() const
{
	return m_pLinkedScene;
}

fuel::Transform* fuel::Button::GetTransform() const
{
	return m_pTransform;
}

void fuel::Button::SetName(const std::string& name)
{
	m_Name = name;
}

std::string& fuel::Button::GetName()
{
	return m_Name;
}

void fuel::Button::SetTag(const std::string& tagName)
{
	m_Tag = tagName;
}

std::string fuel::Button::GetTag() const
{
	return m_Tag;
}

bool fuel::Button::CompareTag(const std::string& tagName) const
{
	return m_Tag == tagName;
}

void fuel::Button::SetActive(const bool isActive)
{
	m_IsActive = isActive;
}

bool fuel::Button::GetIsActive() const
{
	return m_IsActive;
}

bool fuel::Button::GetIsTriggered() const
{
	return m_IsTriggered;
}

fuel::ObjectType fuel::Button::GetObjectType() const
{
	return ObjectType::BUTTON;
}

void fuel::Button::Safe(std::ofstream& binStream) const
{
	binStream.write((const char*)&m_ButtonID, sizeof(int));
	binStream.write((const char*)&m_IsSelected, sizeof(bool));
	binStream.write((const char*)&m_ButtonAction, sizeof(ButtonAction));

	m_pTransform->Safe(binStream);
	m_pRenderComponent->Safe(binStream);
	m_pTextComponent->Safe(binStream);
}

void fuel::Button::Load(std::ifstream& binStream)
{
	binStream.read((char*)&m_ButtonID, sizeof(int));
	binStream.read((char*)&m_IsSelected, sizeof(bool));
	binStream.read((char*)&m_ButtonAction, sizeof(ButtonAction));

	m_pTransform->Load(binStream);
	m_pRenderComponent->Load(binStream);
	m_pTextComponent->Load(binStream);
}

void fuel::Button::ExecuteButtonAction() const
{
	m_ExecutionFunction();
}

void fuel::Button::AddFunctionData(std::function<void()> funtPointer)
{
	m_ExecutionFunction = funtPointer;
}

void fuel::Button::SetText(const std::string& text)
{
	m_pTextComponent->SetText(text);
}

void fuel::Button::SetFont(const std::shared_ptr<Font>& font)
{
	m_pTextComponent->SetFont(font);
}

void fuel::Button::SetFontSize(const int size)
{
	m_pTextComponent->SetSize(size);
}

void fuel::Button::SetTextOffset(const Vector2& offset)
{
	m_pTextComponent->SetPosition(offset.x, offset.y);
}

void fuel::Button::SetTexture(const std::string fileName)
{
	m_pRenderComponent->SetTexture(fileName);
}

void fuel::Button::SetSelected(bool isSelected)
{
	m_IsSelected = isSelected;
}

void fuel::Button::SetButtonID(const int id)
{
	m_ButtonID = id;
}

int fuel::Button::GetButtonID() const
{
	return m_ButtonID;
}

bool fuel::Button::IsSelected() const
{
	return m_IsSelected;
}

void fuel::Button::SetButtonAction(const ButtonAction action)
{
	m_ButtonAction = action;
}

void fuel::Button::DrawComponents()
{
	m_pTransform->DrawGUI();
	ImGui::Separator();
	m_pRenderComponent->DrawGUI();
	ImGui::Separator();
	m_pTextComponent->DrawGUI();
	ImGui::Separator();
}
