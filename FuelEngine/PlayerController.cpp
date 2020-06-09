#include "FuelEnginePCH.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "VibrationComponent.h"
#include "Logger.h"
#include "Scene.h"

fuel::PlayerController::PlayerController()
	: m_pGameObject{ nullptr }
	, m_PlayerID{ PlayerID::PlayerOne }
	, m_ID{"" }
	, m_IsInMenu{ true }
{
}

void fuel::PlayerController::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::PlayerController::OnStart()
{
	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::Jump, ButtonState::pressed, XINPUT_GAMEPAD_A);
	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::Fire, ButtonState::released, XINPUT_GAMEPAD_Y);
	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::Fart, ButtonState::released, XINPUT_GAMEPAD_X);

	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::MoveUpUI, ButtonState::released, XINPUT_GAMEPAD_DPAD_UP);
	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::MoveDownUI, ButtonState::released, XINPUT_GAMEPAD_DPAD_DOWN);
	InputManager::AddControllerBinding(m_PlayerID, this, CommandID::ClickUI, ButtonState::released, XINPUT_GAMEPAD_A);
}

void fuel::PlayerController::Update()
{
	Vector2 axis = InputManager::GetControllerAxis(true, m_PlayerID);
	TextComponent* text = m_pGameObject->GetComponent<TextComponent>();
	if (text)
	{
		text->SetText(std::to_string(InputManager::GetTriggerAxis(false, m_PlayerID)));
	}
	
	if (InputManager::IsLeftMousePressed())
	{
		Logger::LogInfo("Left mouse button pressed!");
	}
	if (InputManager::IsMiddleMousePressed())
	{
		Logger::LogWarning("Middle mouse button pressed!");
	}
	if (InputManager::IsRightMousePressed())
	{
		Logger::LogError("Right mouse button pressed!");
	}
}

void fuel::PlayerController::FixedUpdate()
{
}

void fuel::PlayerController::Render() const
{
}

void fuel::PlayerController::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::PlayerController::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::PlayerController::GetType()
{
	return typeid(this).hash_code();
}

void fuel::PlayerController::SetPlayerID(const PlayerID id)
{
	m_PlayerID = id;
}

fuel::PlayerID fuel::PlayerController::GetPlayerID() const
{
	return m_PlayerID;
}

void fuel::PlayerController::Jump()
{
	if (m_IsInMenu)
		return;
	
	Logger::LogInfo("Jump");
}

void fuel::PlayerController::Fire()
{
	if (m_IsInMenu)
		return;
	
	Logger::LogInfo("Fire");
	VibrationComponent* pVibrationComp = m_pGameObject->GetComponent<VibrationComponent>();
	if (pVibrationComp)
		pVibrationComp->Play();
}

void fuel::PlayerController::Duck()
{
	if (m_IsInMenu)
		return;
	
	Logger::LogInfo("Duck");
}

void fuel::PlayerController::Fart()
{
	if (m_IsInMenu)
		return;
	
	Logger::LogInfo("Fart");
}

void fuel::PlayerController::MoveUpUI()
{
	if (!m_IsInMenu)
		return;

	m_pGameObject->GetScene()->PreviousButton();
}

void fuel::PlayerController::MoveDownUI()
{
	if (!m_IsInMenu)
		return;

	m_pGameObject->GetScene()->NextButton();
}

void fuel::PlayerController::ClickUI()
{
	if (!m_IsInMenu)
		return;

	m_pGameObject->GetScene()->ExecuteButtonAction();
}

void fuel::PlayerController::Safe(std::ofstream& binStream) const
{
	binStream.write((const char*)&m_PlayerID, sizeof(PlayerID));
}

void fuel::PlayerController::Load(std::ifstream& binStream)
{
	binStream.read((char*)&m_PlayerID, sizeof(PlayerID));
}

fuel::ComponentType fuel::PlayerController::GetCompType() const
{
	return ComponentType::CONTROLLER;
}

void fuel::PlayerController::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::PlayerController::DrawGUI()
{
	ImGui::Text("Player Controller Component");
	
	// Create dropdown menu
	const std::string items[] = { "Player1", "Player2", "Player3", "Player4" };
	static std::string current_item = "Player1";
	const std::string& dropdownLabel{ "##PlayerID" + m_ID };
	if (ImGui::BeginCombo(dropdownLabel.c_str(), current_item.c_str()))
	{
		for (int idx{ 0 }; idx <= int(PlayerID::PlayerFour); ++idx)
		{
			const bool is_selected = (current_item == items[idx]);
			if (ImGui::Selectable(items[idx].c_str(), is_selected))
			{
				current_item = items[idx];
				ChangePlayerID(current_item);
			}
		}
		
		ImGui::EndCombo();
	}
}

const std::string& fuel::PlayerController::GetID() const
{
	return m_ID;
}

void fuel::PlayerController::ChangePlayerID(const std::string& playerID)
{
	if (playerID == "Player1")
	{
		InputManager::ChangePlayerID(m_PlayerID, PlayerID::PlayerOne);
		m_PlayerID = PlayerID::PlayerOne;
		Logger::LogInfo("Player ID of controller changed to 'Player1'");
	}
	else if (playerID == "Player2")
	{
		InputManager::ChangePlayerID(m_PlayerID, PlayerID::PlayerTwo);
		m_PlayerID = PlayerID::PlayerTwo;
		Logger::LogInfo("Player ID of controller changed to 'Player2'");
	}
	else if (playerID == "Player3")
	{
		InputManager::ChangePlayerID(m_PlayerID, PlayerID::PlayerThree);
		m_PlayerID = PlayerID::PlayerThree;
		Logger::LogInfo("Player ID of controller changed to 'Player3'");
	}
	else if (playerID == "Player4")
	{
		InputManager::ChangePlayerID(m_PlayerID, PlayerID::PlayerFour);
		m_PlayerID = PlayerID::PlayerFour;
		Logger::LogInfo("Player ID of controller changed to 'Player4'");
	}
}
