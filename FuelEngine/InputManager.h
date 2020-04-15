#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"
#include "InputBinding.h"
#include "EngineSettings.h"
#include <array>
#include <SDL.h>

namespace fuel
{
	enum class PlayerID
	{
		PlayerOne,
		PlayerTwo,
		PlayerThree,
		PlayerFour
	};
	
	enum class CommandID
	{
		Jump,
		Fart,
		Duck,
		Fire
	};

	class Command;
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		static void Initialize() { GetInstance().IInitialize(); }
		static bool ProcessInput() { return GetInstance().IProcessInput(); }
		
		static Command* GetCommand(CommandID commandName) { return GetInstance().IGetCommand(commandName); }
		static void AddCommand(Command* command, CommandID commandID) { GetInstance().IAddCommand(command, commandID); }

		// Controller input
		static void AddControllerBinding(const PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, WORD gamepadButton) { GetInstance().IAddControllerBinding(playerID, playerController, commandID, triggerState, gamepadButton); }
		static Vector2 GetControllerAxis(bool leftJoystick, PlayerID playerID) { return GetInstance().IGetControllerAxis(leftJoystick, playerID); }
		static float GetTriggerAxis(bool leftTrigger, PlayerID playerID) { return GetInstance().IGetTriggerAxis(leftTrigger, playerID); }
		static void SetVibration(float leftVibration, float rightVibration, PlayerID playerIndex) { GetInstance().ISetVibration(leftVibration, rightVibration, playerIndex); }
		static void ChangePlayerID(PlayerID oldPlayerID, PlayerID newPlayerID) { GetInstance().IChangePlayerID(oldPlayerID, newPlayerID); }
		
		// Keyboard input
		static void AddKeyboardBinding(const PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, SDL_Keycode keyboardButton) { GetInstance().IAddKeyboardBinding(playerID, playerController, commandID, triggerState, keyboardButton); }

		// Mouse input
		static int GetMouseWheelDelta() { return GetInstance().IGetMouseWheelDelta(); }
		static Vector2 GetMousePosition() { return GetInstance().IGetMousePosition(); }
		static bool IsLeftMousePressed() { return GetInstance().m_IsLeftMousePressed; }
		static bool IsMiddleMousePressed() { return GetInstance().m_IsMiddleMousePressed; }
		static bool IsRightMousePressed() { return GetInstance().m_IsRightMousePressed; }
		
	private:
		void IInitialize();
		void CreateCommands();
		
		bool IProcessInput();

		Command* IGetCommand(CommandID commandID);
		void IAddCommand(Command* command, CommandID commandID);
		void IAddControllerBinding(const PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, WORD gamepadButton);

		void ProcessGamepadInput();
		void RefreshControllerConnections();
		void UpdateGamepadStates();
		bool IsGamepadButtonPressed(const WORD button, int playerID) const;
		bool WasGamepadButtonPressed(const WORD button, int playerID) const;
		ButtonState GetGamepadButtonState(const WORD button, int playerID) const;
		Vector2 IGetControllerAxis(bool leftJoystick, PlayerID playerID) const;
		float IGetTriggerAxis(bool leftTrigger, PlayerID playerID) const;
		void ISetVibration(float leftVibration, float rightVibration, PlayerID playerIndex);
		void IChangePlayerID(PlayerID oldPlayerID, PlayerID newPlayerID);

		void ProcessKeyboardInput(SDL_Event e);
		void IAddKeyboardBinding(const PlayerID playerID, PlayerController * playerController, CommandID commandID, ButtonState triggerState, SDL_Keycode keyboardButton);

		int IGetMouseWheelDelta() const;
		Vector2 IGetMousePosition();
		void ResetMouseFlags();

		std::array<XINPUT_STATE, 4> m_CurrentGamepadStates{};
		std::array<XINPUT_STATE, 4> m_OldGamepadStates{};
		std::map<CommandID, Command*> m_Commands{};
		std::vector<ControllerBinding*> m_pControllerBindings{};
		std::vector<KeyBinding*> m_pKeyboardBindings{};
		bool m_ConnectedGamepads[XUSER_MAX_COUNT]{};
		int m_MouseWheelDelta{};
		Vector2 m_MousePosition{};
		bool m_IsLeftMousePressed{};
		bool m_IsMiddleMousePressed{};
		bool m_IsRightMousePressed{};
	};
}
