#pragma once
#include <SDL.h>

namespace fuel
{
	enum class PlayerID;
	enum class CommandID;
	enum class ButtonState
	{
		none,
		pressed,
		hold,
		released
	};
	
	class Command;
	class PlayerController;
	class InputBinding
	{
	public:
		InputBinding() = default;
		virtual ~InputBinding() = default;

		virtual PlayerID GetPlayerID() const = 0;
		virtual void Process() = 0;
		
		virtual void SetCommand(Command* command) = 0;
		virtual Command* GetCommand() const = 0;

		virtual void SetCurrentButtonState(const ButtonState& buttonState) = 0;
		virtual ButtonState GetCurrentButtonState() const = 0;
		virtual void SetTriggerState(const ButtonState& buttonState) = 0;
		virtual ButtonState GetTriggerState() const = 0;

	protected:
		PlayerID m_PlayerID{ };
		Command* m_pCommand{ nullptr };
		ButtonState m_TriggerState{ ButtonState::none };
		PlayerController* m_pPlayerController{ nullptr };
	};

	class ControllerBinding final : public InputBinding
	{
	public:
		ControllerBinding(PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, WORD gamepadButton);
		virtual ~ControllerBinding() = default;

		PlayerID GetPlayerID() const override;
		void SetPlayerID(PlayerID newPlayerID);
		void Process() override;

		void SetCommand(Command* command) override;
		Command* GetCommand() const override;

		void SetCurrentButtonState(const ButtonState& buttonState) override;
		ButtonState GetCurrentButtonState() const override;
		void SetTriggerState(const ButtonState& buttonState) override;
		ButtonState GetTriggerState() const override;

		WORD GetGamepadButton() const;

	private:
		WORD m_ControllerButton{ 0 };
		ButtonState m_CurrentState{ ButtonState::none };
	};

	class KeyBinding final : public InputBinding
	{
	public:
		KeyBinding(PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, SDL_Keycode keyboardButton);
		virtual ~KeyBinding() = default;

		PlayerID GetPlayerID() const override;
		void Process() override;

		void SetCommand(Command* command) override;
		Command* GetCommand() const override;

		void SetCurrentButtonState(const ButtonState& buttonState) override;
		ButtonState GetCurrentButtonState() const override;
		void SetPreviousButtonState(const ButtonState& buttonState);
		ButtonState GetPreviousButtonState() const;
		void SetTriggerState(const ButtonState& buttonState) override;
		ButtonState GetTriggerState() const override;

		SDL_Keycode GetKeyboardButton() const;

	private:
		SDL_Keycode m_KeyboardButton;
		ButtonState m_CurrentState{ ButtonState::none };
		ButtonState m_PreviousState{ ButtonState::none };
	};
}
