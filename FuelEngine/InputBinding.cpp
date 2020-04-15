#include "FuelEnginePCH.h"
#include "InputBinding.h"
#include "InputManager.h"
#include "Commands.h"

fuel::ControllerBinding::ControllerBinding(PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, WORD gamepadButton)
{
	m_PlayerID = playerID;
	m_pCommand = fuel::InputManager::GetCommand(commandID);
	m_TriggerState = triggerState;
	m_ControllerButton = gamepadButton;
	m_pPlayerController = playerController;
}

fuel::PlayerID fuel::ControllerBinding::GetPlayerID() const
{
	return m_PlayerID;
}

void fuel::ControllerBinding::SetPlayerID(PlayerID newPlayerID)
{
	m_PlayerID = newPlayerID;
}

void fuel::ControllerBinding::Process()
{
	if (m_CurrentState == m_TriggerState)
	{
		m_pCommand->Execute(m_pPlayerController);
	}
}

void fuel::ControllerBinding::SetCommand(Command* command)
{
	m_pCommand = command;
}

fuel::Command* fuel::ControllerBinding::GetCommand() const
{
	return m_pCommand;
}

void fuel::ControllerBinding::SetCurrentButtonState(const ButtonState& buttonState)
{
	m_CurrentState = buttonState;
}

fuel::ButtonState fuel::ControllerBinding::GetCurrentButtonState() const
{
	return m_CurrentState;
}

void fuel::ControllerBinding::SetTriggerState(const ButtonState& buttonState)
{
	m_TriggerState = buttonState;
}

fuel::ButtonState fuel::ControllerBinding::GetTriggerState() const
{
	return m_TriggerState;
}

WORD fuel::ControllerBinding::GetGamepadButton() const
{
	return m_ControllerButton;
}

fuel::KeyBinding::KeyBinding(PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, SDL_Keycode keyboardButton)
{
	m_PlayerID = playerID;
	m_pCommand = fuel::InputManager::GetCommand(commandID);
	m_TriggerState = triggerState;
	m_KeyboardButton = keyboardButton;
	m_pPlayerController = playerController;
}

fuel::PlayerID fuel::KeyBinding::GetPlayerID() const
{
	return m_PlayerID;
}

void fuel::KeyBinding::Process()
{
	if (m_CurrentState == m_TriggerState)
	{
		m_pCommand->Execute(m_pPlayerController);
	}
}

void fuel::KeyBinding::SetCommand(Command* command)
{
	m_pCommand = command;
}

fuel::Command* fuel::KeyBinding::GetCommand() const
{
	return m_pCommand;
}

void fuel::KeyBinding::SetCurrentButtonState(const ButtonState& buttonState)
{
	m_CurrentState = buttonState;
}

fuel::ButtonState fuel::KeyBinding::GetCurrentButtonState() const
{
	return m_CurrentState;
}

void fuel::KeyBinding::SetPreviousButtonState(const ButtonState& buttonState)
{
	m_PreviousState = buttonState;
}

fuel::ButtonState fuel::KeyBinding::GetPreviousButtonState() const
{
	return m_PreviousState;
}

void fuel::KeyBinding::SetTriggerState(const ButtonState& buttonState)
{
	m_TriggerState = buttonState;
}

fuel::ButtonState fuel::KeyBinding::GetTriggerState() const
{
	return m_TriggerState;
}

SDL_Keycode fuel::KeyBinding::GetKeyboardButton() const
{
	return m_KeyboardButton;
}
