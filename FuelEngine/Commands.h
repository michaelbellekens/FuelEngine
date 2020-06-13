#pragma once
#include "PlayerController.h"
#include "GameObject.h"
#include "Scene.h"

namespace fuel
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute(fuel::PlayerController* controller) = 0;
	};

	class JumpCommand final : public Command
	{
	public:
		JumpCommand() = default;
		virtual ~JumpCommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->Jump();
		}
	};

	class FireCommand final : public Command
	{
	public:
		FireCommand() = default;
		virtual ~FireCommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->Fire();
		}
	};

	class DuckCommand final : public Command
	{
	public:
		DuckCommand() = default;
		virtual ~DuckCommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->Duck();
		}
	};

	class FartCommand final : public Command
	{
	public:
		FartCommand() = default;
		virtual ~FartCommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->Fart();
		}
	};

	class MenuCommand final : public Command
	{
	public:
		MenuCommand() = default;
		virtual ~MenuCommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->OpenMenu();
		}
	};

	class MoveUpUICommand final : public Command
	{
	public:
		MoveUpUICommand() = default;
		virtual ~MoveUpUICommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->MoveUpUI();
		}
	};

	class MoveDownUICommand final : public Command
	{
	public:
		MoveDownUICommand() = default;
		virtual ~MoveDownUICommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->MoveDownUI();
		}
	};

	class ClickUICommand final : public Command
	{
	public:
		ClickUICommand() = default;
		virtual ~ClickUICommand() = default;

		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
				controller->ClickUI();
		}
	};
}
