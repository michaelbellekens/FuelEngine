#include "FuelEnginePCH.h"
#include "VibrationComponent.h"
#include "InputManager.h"

void fuel::VibrationComponent::Initialize()
{
	m_LeftVibration = 0.5f;
	m_RightVibration = 0.5f;
	m_Duration = 1.f;
	m_CurrentDuration = 0.f;
	m_CanPlay = false;
	m_PlayerID = PlayerID::PlayerOne;

	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::VibrationComponent::OnStart()
{
}

void fuel::VibrationComponent::Update()
{
	if (m_CanPlay)
	{
		m_CurrentDuration += Time::GetDeltaTime();
		if (m_CurrentDuration > m_Duration)
		{
			Stop();
			std::cout << "Vibration stopped!" << std::endl;
		}
	std::cout << "CurrentVibrationTime: " << m_CurrentDuration << std::endl;
	}
}

void fuel::VibrationComponent::FixedUpdate()
{
}

void fuel::VibrationComponent::Render() const
{
}

void fuel::VibrationComponent::SetGameObject(fuel::GameObject* parent)
{
	m_Gameobject = parent;
}

fuel::GameObject* fuel::VibrationComponent::GetGameObject() const
{
	return m_Gameobject;
}

size_t fuel::VibrationComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::VibrationComponent::Play()
{
	m_CanPlay = true;
	InputManager::SetVibration(m_LeftVibration, m_RightVibration, m_PlayerID);
}

void fuel::VibrationComponent::Stop()
{
	m_CanPlay = false;
	m_CurrentDuration = 0.f;
	InputManager::SetVibration(0, 0, m_PlayerID);
}

void fuel::VibrationComponent::SetLeftVibration(float vibration)
{
	m_LeftVibration = vibration;
}

void fuel::VibrationComponent::SetRightVibration(float vibration)
{
	m_RightVibration = vibration;
}

void fuel::VibrationComponent::SetDuration(float durationSec)
{
	m_Duration = durationSec;
}

void fuel::VibrationComponent::SetPlayerID(PlayerID playerID)
{
	m_PlayerID = playerID;
}

void fuel::VibrationComponent::DrawGUI()
{
	ImGui::Text("Gamepad Vibration Component");
	ImGui::Spacing();
	ImGui::Text("Vibration settings:");

	const std::string leftVibLabel{ "##LeftVibration" + m_ID };
	ImGui::Text("Left vibration:");
	ImGui::SameLine(150);
	ImGui::PushItemWidth(200);
	ImGui::InputFloat(leftVibLabel.c_str(), &m_LeftVibration, 0, 0, "%0.2f");
	ImGui::PopItemWidth();
	const std::string rightVibLabel{ "##RightVibration" + m_ID };
	ImGui::Text("Right vibration:");
	ImGui::SameLine(150);
	ImGui::PushItemWidth(200);
	ImGui::InputFloat(rightVibLabel.c_str(), &m_RightVibration, 0, 0, "%0.2f");
	ImGui::PopItemWidth();

	ImGui::Text("Time settings:");
	
	const std::string vibDurationLabel{ "##VibDuration" + m_ID };
	ImGui::Text("Vibration duration:");
	ImGui::SameLine(150);
	ImGui::PushItemWidth(200);
	ImGui::InputFloat(vibDurationLabel.c_str(), &m_Duration, 0, 0, "%0.1f");
	ImGui::PopItemWidth();
}

const std::string& fuel::VibrationComponent::GetID() const
{
	return m_ID;
}
