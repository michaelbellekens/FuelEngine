#include "FuelEnginePCH.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "VibrationComponent.h"
#include "Logger.h"

fuel::PlayerController::PlayerController()
	: m_pGameObject{ nullptr }
	, m_PlayerID{ PlayerID::PlayerOne }
	, m_ID{"" }
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
}

void fuel::PlayerController::Update()
{
	Vector2 axis = InputManager::GetControllerAxis(true, m_PlayerID);
	TextComponent* text = m_pGameObject->GetComponent<TextComponent>();
	if (text)
	{
		text->SetText(std::to_string(InputManager::GetTriggerAxis(false, m_PlayerID)));
	}

	//Logger::LogInfo(InputManager::GetMousePosition());
	//Logger::LogWarning(InputManager::GetMousePosition());
	//Logger::LogError(InputManager::GetMousePosition());
	
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
	Logger::LogInfo("Jump");
}

void fuel::PlayerController::Fire()
{
	Logger::LogInfo("Fire");
	VibrationComponent* pVibrationComp = m_pGameObject->GetComponent<VibrationComponent>();
	if (pVibrationComp)
		pVibrationComp->Play();
}

void fuel::PlayerController::Duck()
{
	Logger::LogInfo("Duck");
}

void fuel::PlayerController::Fart()
{
	Logger::LogInfo("Fart");
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
