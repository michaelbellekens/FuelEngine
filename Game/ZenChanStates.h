#pragma once
#include "AIState.h"

namespace fuel
{
	class SpriteComponent;
	class WanderState_ZN : public AIState
	{
	public:
		WanderState_ZN() = default;
		virtual ~WanderState_ZN() = default;

		void Enter(GameObject* actor) override;
		void Update() override;
		void FixedUpdate() override;
		void TriggerPhysicsEvent(const PhysicsEvent& physicsEvent) override;
		size_t GetID() const override;

	private:
		RigidBody2D* m_pRigidBody2D{ nullptr };
		SpriteComponent* m_pSpriteRenderer{ nullptr };
		GameObject* m_pActor{ nullptr };
		bool m_WanderLeft{ false };
		bool m_IsOnEdge{ false };
	};

	class AttackState_ZN : public AIState
	{
	public:
		AttackState_ZN() = default;
		virtual ~AttackState_ZN() = default;

		void Enter(GameObject* actor) override;
		void Update() override;
		void FixedUpdate() override;
		void TriggerPhysicsEvent(const PhysicsEvent& physicsEvent) override;
		size_t GetID() const override;
		
		void SetTarget(GameObject* pTarget);

	private:
		RigidBody2D* m_pRigidBody2D{ nullptr };
		SpriteComponent* m_pSpriteRenderer{ nullptr };
		GameObject* m_pActor{ nullptr };
		GameObject* m_pTarget{ nullptr };
		float m_CurrentJumpTime{ 3.f };
		float m_JumpCoolDown{ 3.f };
		float m_CurrentAttackTime{ 2.f };
		float m_AttackCooldown{ 2.f };
		bool m_IsMovingLeft{ false };
	};
}
