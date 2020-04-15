#include "FuelEnginePCH.h"
#include "InputManager.h"
#include "Tools.h"
#include "Commands.h"


fuel::InputManager::~InputManager()
{
	for (ControllerBinding* controllerBinding : m_pControllerBindings)
		delete controllerBinding;

	for (KeyBinding* keyBinding : m_pKeyboardBindings)
		delete keyBinding;

	for (std::pair<CommandID, Command*> command : m_Commands)
		delete command.second;
}

void fuel::InputManager::IInitialize()
{
	RefreshControllerConnections();
	CreateCommands();

	ImGuiIO& io = ImGui::GetIO();

	io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
	io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
	io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
	io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
	io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
	io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;
}

void fuel::InputManager::CreateCommands()
{
	AddCommand(new JumpCommand(), CommandID::Jump);
	AddCommand(new FireCommand(), CommandID::Fire);
	AddCommand(new DuckCommand(), CommandID::Duck);
	AddCommand(new FartCommand(), CommandID::Fart);
}

bool fuel::InputManager::IProcessInput()
{
	ImGuiIO& io = ImGui::GetIO();

	ResetMouseFlags();

	// Handle all gamepad input and controllerBindings
	UpdateGamepadStates();
	ProcessGamepadInput();

#pragma region SDL_Event_Loop
	int wheel = 0;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_WINDOWEVENT)
		{
			// Got reference from: https://github.com/Tyyppi77/imgui_sdl/blob/master/example.cpp#L38
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<float>(e.window.data1);
				io.DisplaySize.y = static_cast<float>(e.window.data2);
			}
		}

		else if (e.type == SDL_MOUSEWHEEL)
		{
			// Got reference from: https://github.com/Tyyppi77/imgui_sdl/blob/master/example.cpp#L46
			wheel = e.wheel.y;
			m_MouseWheelDelta = wheel;
			//std::cout << wheel << std::endl;
		}

		else if (e.type == SDL_TEXTINPUT)
		{
			// Got reference from: https://github.com/ocornut/imgui/blob/master/examples/imgui_impl_sdl.cpp#L107
			io.AddInputCharactersUTF8(e.text.text);
		}

		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			// Got reference from: https://github.com/ocornut/imgui/blob/master/examples/imgui_impl_sdl.cpp#L92
			const int key = e.key.keysym.scancode;
			IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
			io.KeysDown[key] = (e.type == SDL_KEYDOWN);
			io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
			io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
			io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
		}

		if (!io.WantCaptureKeyboard && !io.WantCaptureMouse && !io.WantTextInput)
		{
			// Handle all keyBindings
			ProcessKeyboardInput(e);
		}
	}
#pragma endregion 
	
	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	// Got reference from: https://github.com/Tyyppi77/imgui_sdl/blob/master/example.cpp#L55
	// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)
	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);
	
	return true;
}

#pragma region Commands
fuel::Command* fuel::InputManager::IGetCommand(CommandID commandID)
{
	if (m_Commands.find(commandID) == m_Commands.end())
		return nullptr;

	return m_Commands[commandID];
}

void fuel::InputManager::IAddCommand(Command* command, CommandID commandID)
{
	if (m_Commands.find(commandID) == m_Commands.end())
		m_Commands.insert(std::make_pair(commandID, command));
}

void fuel::InputManager::IAddControllerBinding(const PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, WORD gamepadButton)
{
	m_pControllerBindings.push_back(new	ControllerBinding(playerID, playerController, commandID, triggerState, gamepadButton));
}
#pragma endregion

#pragma region Gamepads
void fuel::InputManager::ProcessGamepadInput()
{
	for (ControllerBinding* controllerBinding : m_pControllerBindings)
	{
		ButtonState currentGamepadButtonState{ GetGamepadButtonState(controllerBinding->GetGamepadButton(), int(controllerBinding->GetPlayerID())) };
		controllerBinding->SetCurrentButtonState(currentGamepadButtonState);
		controllerBinding->Process();
	}
}

void fuel::InputManager::RefreshControllerConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

void fuel::InputManager::UpdateGamepadStates()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadStates[i] = m_CurrentGamepadStates[i];

		const DWORD dwResult = XInputGetState(i, &m_CurrentGamepadStates[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

bool fuel::InputManager::IsGamepadButtonPressed(const WORD button, int playerID) const
{
	return (m_CurrentGamepadStates[playerID].Gamepad.wButtons & button) != 0;
}

bool fuel::InputManager::WasGamepadButtonPressed(const WORD button, int playerID) const
{
	return (m_OldGamepadStates[playerID].Gamepad.wButtons & button) != 0;
}

fuel::ButtonState fuel::InputManager::GetGamepadButtonState(const WORD button, int playerID) const
{
	if (WasGamepadButtonPressed(button, playerID))
		if (IsGamepadButtonPressed(button, playerID))
			return ButtonState::hold;
		else
			return ButtonState::released;
	else
		if (IsGamepadButtonPressed(button, playerID))
			return ButtonState::pressed;
		else
			return ButtonState::none;
}

fuel::Vector2 fuel::InputManager::IGetControllerAxis(bool leftJoystick, PlayerID playerID) const
{
	Vector2 stickAxis{};
	const int controllerID{ static_cast<int>(playerID) };
	if (leftJoystick)
	{
		stickAxis = Vector2(m_CurrentGamepadStates[controllerID].Gamepad.sThumbLX, m_CurrentGamepadStates[controllerID].Gamepad.sThumbLY);
		if (stickAxis.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stickAxis.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			stickAxis.x = 0;

		if (stickAxis.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stickAxis.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			stickAxis.y = 0;
	}
	else
	{
		stickAxis = Vector2(m_CurrentGamepadStates[controllerID].Gamepad.sThumbRX, m_CurrentGamepadStates[controllerID].Gamepad.sThumbRY);
		if (stickAxis.x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && stickAxis.x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			stickAxis.x = 0;

		if (stickAxis.y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && stickAxis.y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			stickAxis.y = 0;
	}

	
	if (stickAxis.x > 0)
		stickAxis.x /= 32767;
	else
		stickAxis.x /= 32768;

	if (stickAxis.y > 0)
		stickAxis.y /= 32767;
	else
		stickAxis.y /= 32768;

	return stickAxis;
}

float fuel::InputManager::IGetTriggerAxis(bool leftTrigger, PlayerID playerID) const
{
	float triggerAxis{};
	const int controllerID{ static_cast<int>(playerID) };

	if (leftTrigger)
		triggerAxis = m_CurrentGamepadStates[controllerID].Gamepad.bLeftTrigger / 255.f;
	else
		triggerAxis = m_CurrentGamepadStates[controllerID].Gamepad.bRightTrigger / 255.f;

	return triggerAxis;
}

void fuel::InputManager::ISetVibration(float leftVibration, float rightVibration, PlayerID playerIndex)
{
	XINPUT_VIBRATION vibration;
	Clamp<float>(leftVibration, 1.0f, 0.0f);
	Clamp<float>(rightVibration, 1.0f, 0.0f);

	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = static_cast<WORD>(leftVibration * 65535);
	vibration.wRightMotorSpeed = static_cast<WORD>(rightVibration * 65535);

	XInputSetState(static_cast<UINT>(playerIndex), &vibration);
}
void fuel::InputManager::IChangePlayerID(PlayerID oldPlayerID, PlayerID newPlayerID)
{
	for (ControllerBinding* pBinding : m_pControllerBindings)
	{
		if (pBinding->GetPlayerID() == oldPlayerID)
			pBinding->SetPlayerID(newPlayerID);
	}
}
#pragma endregion

#pragma region Keyboard
void fuel::InputManager::ProcessKeyboardInput(SDL_Event e)
{
	for (KeyBinding* keyBinding : m_pKeyboardBindings)
	{
		if (e.key.keysym.sym == keyBinding->GetKeyboardButton())
		{
			if (e.type == SDL_KEYDOWN)
			{
				keyBinding->SetPreviousButtonState(keyBinding->GetCurrentButtonState());
				if (keyBinding->GetPreviousButtonState() == ButtonState::pressed)
					keyBinding->SetCurrentButtonState(ButtonState::hold);
				else if (keyBinding->GetPreviousButtonState() == ButtonState::hold)
					keyBinding->SetCurrentButtonState(ButtonState::hold);
				else
					keyBinding->SetCurrentButtonState(ButtonState::pressed);

				keyBinding->Process();
			}
			else if (e.type == SDL_KEYUP)
			{
				keyBinding->SetCurrentButtonState(ButtonState::released);
				keyBinding->Process();
				keyBinding->SetCurrentButtonState(ButtonState::none);
			}
		}	
	}
	if (e.button.button == SDL_BUTTON_LEFT && e.button.state == SDL_RELEASED)
	{
		m_IsLeftMousePressed = true;
	}
	if (e.button.button == SDL_BUTTON_MIDDLE && e.button.state == SDL_RELEASED)
	{
		m_IsMiddleMousePressed = true;
	}
	if (e.button.button == SDL_BUTTON_RIGHT && e.button.state == SDL_RELEASED)
	{
		m_IsRightMousePressed = true;
	}
}

void fuel::InputManager::IAddKeyboardBinding(const PlayerID playerID, PlayerController* playerController, CommandID commandID, ButtonState triggerState, SDL_Keycode keyboardButton)
{
	m_pKeyboardBindings.push_back(new KeyBinding(playerID, playerController, commandID, triggerState, keyboardButton));
}

int fuel::InputManager::IGetMouseWheelDelta() const
{
	return m_MouseWheelDelta;
}

fuel::Vector2 fuel::InputManager::IGetMousePosition()
{
	int xPos, yPos;
	SDL_GetMouseState(&xPos, &yPos);

	m_MousePosition.x = static_cast<float>(xPos);
	m_MousePosition.y = static_cast<float>(EngineSettings::GetWindowHeight() - yPos);
	
	return m_MousePosition;
}

void fuel::InputManager::ResetMouseFlags()
{
	m_IsLeftMousePressed = false;
	m_IsMiddleMousePressed = false;
	m_IsRightMousePressed = false;
}
#pragma endregion