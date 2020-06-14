#pragma once
#include "PlayerController.h"
#include "GameObject.h"
#include "Scene.h"
#include "RigidBody2D.h"
namespace fuel
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void SetExecuteFunction(std::function<void(fuel::PlayerController* controller)> executeFunct) = 0;
		virtual void Execute(fuel::PlayerController* controller) = 0;

	protected:
		std::function<void(fuel::PlayerController * controller)> m_ExecutionFunction;
		bool m_IsFunctionSet{ false };
	};

	class JumpCommand final : public Command
	{
	public:
		JumpCommand() = default;
		virtual ~JumpCommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->Jump();
			}
		}
	};

	class FireCommand final : public Command
	{
	public:
		FireCommand() = default;
		virtual ~FireCommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->Fire();
			}
		}
	};

	class DuckCommand final : public Command
	{
	public:
		DuckCommand() = default;
		virtual ~DuckCommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->Duck();
			}
		}
	};

	class FartCommand final : public Command
	{
	public:
		FartCommand() = default;
		virtual ~FartCommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->Fart();
			}
		}
	};

	class MenuCommand final : public Command
	{
	public:
		MenuCommand() = default;
		virtual ~MenuCommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->OpenMenu();
			}
		}
	};

	class MoveUpUICommand final : public Command
	{
	public:
		MoveUpUICommand() = default;
		virtual ~MoveUpUICommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->MoveUpUI();
			}
		}
	};

	class MoveDownUICommand final : public Command
	{
	public:
		MoveDownUICommand() = default;
		virtual ~MoveDownUICommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->MoveDownUI();
			}
		}
	};

	class ClickUICommand final : public Command
	{
	public:
		ClickUICommand() = default;
		virtual ~ClickUICommand() = default;

		void SetExecuteFunction(const std::function<void(fuel::PlayerController * controller)> executeFunct) override
		{
			m_ExecutionFunction = executeFunct;
			m_IsFunctionSet = true;
		}
		
		void Execute(fuel::PlayerController* controller) override
		{
			if (controller->GetGameObject()->GetScene()->GetIsActive())
			{
				if (m_IsFunctionSet)
				{
					m_ExecutionFunction(controller);
					return;
				}
				
				controller->ClickUI();
			}
		}
	};
}
