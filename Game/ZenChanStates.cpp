#include "FuelEnginePCH.h"
#include "ZenChanStates.h"

#include "BoxCollider.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "Time.h"
#include "Transform.h"

void fuel::WanderState_ZN::Enter(GameObject* actor)
{
	m_pActor = actor;
	m_pRigidBody2D = nullptr;
	if (m_pActor)
		m_pRigidBody2D = m_pActor->GetComponent<RigidBody2D>();
	if (m_pActor)
		m_pSpriteRenderer = m_pActor->GetComponent<SpriteComponent>();
	m_WanderLeft = rand() % 2 ? true : false;
}

void fuel::WanderState_ZN::Update()
{
}

void fuel::WanderState_ZN::FixedUpdate()
{
	if (m_pRigidBody2D)
	{
		const bool isOnEdge{ m_IsOnEdge };
		m_IsOnEdge = m_pRigidBody2D->IsOnEdge();
		
		if (!isOnEdge && m_IsOnEdge)
			m_WanderLeft = !m_WanderLeft;
		
		float speed{ 1.2f };
		if (!m_WanderLeft)
			speed *= -1;
		
		m_pRigidBody2D->MovePosition(Vector3(speed, 0.f, 0.f));
		m_pSpriteRenderer->LookLeft(!m_WanderLeft);
	}
}

void fuel::WanderState_ZN::TriggerPhysicsEvent(const PhysicsEvent& physicsEvent)
{
	if (physicsEvent.event == ONCOLLISIONENTER && physicsEvent.other->GetGameObject()->CompareTag("Enemy"))
		m_WanderLeft = !m_WanderLeft;

	if (physicsEvent.event == ONCOLLISIONENTER && physicsEvent.other->GetGameObject()->CompareTag("StaticScene"))
	{
		const Vector3 pos{ m_pRigidBody2D->GetPosition() };
		const Vector3 posWall{ physicsEvent.other->GetPosition() };
		const float height{ m_pActor->GetComponent<BoxCollider>()->GetDimensions().height };

		if (posWall.y < pos.y + height)
			m_WanderLeft = !m_WanderLeft;
	}
}

size_t fuel::WanderState_ZN::GetID() const
{
	return typeid(WanderState_ZN).hash_code();
}

void fuel::AttackState_ZN::Enter(GameObject* actor)
{
	m_pActor = actor;
	m_pRigidBody2D = nullptr;
	if (m_pActor)
		m_pRigidBody2D = m_pActor->GetComponent<RigidBody2D>();
	if (m_pActor)
		m_pSpriteRenderer = m_pActor->GetComponent<SpriteComponent>();
}

void fuel::AttackState_ZN::Update()
{
	m_CurrentAttackTime += Time::GetDeltaTime();
}

void fuel::AttackState_ZN::FixedUpdate()
{
	float speed{ 1.6f };
	const Vector3 pos{ m_pActor->GetTransform()->GetPosition() };
	const Vector3 targetPos{ m_pTarget->GetComponent<RigidBody2D>()->GetPosition() };

	m_CurrentJumpTime += Time::GetFixedDeltaTime();

	if (targetPos.y >= pos.y + 40.f)
	{
		if (m_IsMovingLeft)
			speed *= -1.f;
	}
	else if (targetPos.y < pos.y - 40.f && m_CurrentJumpTime > m_JumpCoolDown)
	{
		m_CurrentJumpTime = 0.f;
		speed = 1.4f;
		if (m_IsMovingLeft)
			speed *= -1.f;

		if (m_pRigidBody2D->IsGrounded())
			m_pRigidBody2D->AddForce({0.f, -5.5f}, true);

		if (targetPos.x <= pos.x)
		{
			speed *= -1.f;
			m_IsMovingLeft = true;
		}
	}
	else if (targetPos.x <= pos.x)
	{
		speed *= -1.f;
		m_IsMovingLeft = true;
	}
	else
		m_IsMovingLeft = false;
	
	m_pRigidBody2D->MovePosition(Vector3(speed, 0.f, 0.f));
	m_pSpriteRenderer->LookLeft(m_IsMovingLeft);
}

void fuel::AttackState_ZN::TriggerPhysicsEvent(const PhysicsEvent& physicsEvent)
{
	if (physicsEvent.event == ONCOLLISIONENTER && physicsEvent.other->GetGameObject()->CompareTag("StaticScene"))
	{
		const Vector3 pos{ m_pRigidBody2D->GetPosition() };
		const Vector3 posWall{ physicsEvent.other->GetPosition() };
		const float height{ m_pActor->GetComponent<BoxCollider>()->GetDimensions().height };

		if (posWall.y < pos.y + height)
			m_IsMovingLeft = !m_IsMovingLeft;
	}

	if (physicsEvent.event == ONCOLLISIONENTER && physicsEvent.other->GetGameObject()->CompareTag("Player"))
	{
		if (m_CurrentAttackTime >= m_AttackCooldown)
		{
			m_CurrentAttackTime = 0.f;
			const Vector3 pos{ m_pActor->GetTransform()->GetPosition() };
			const Vector3 targetPos{ physicsEvent.other->GetGameObject()->GetComponent<RigidBody2D>()->GetPosition() };
			Vector2 dir{ targetPos.x - pos.x, targetPos.y - pos.y };

			physicsEvent.other->GetGameObject()->GetComponent<RigidBody2D>()->AddForce(dir.Normalize() * 2.5f, true);
			physicsEvent.other->GetGameObject()->GetComponent<HealthComponent>()->Damage();
		}
	}
}

size_t fuel::AttackState_ZN::GetID() const
{
	return typeid(AttackState_ZN).hash_code();
}

void fuel::AttackState_ZN::SetTarget(GameObject* pTarget)
{
	m_pTarget = pTarget;
}
