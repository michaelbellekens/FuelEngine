#include "FuelEnginePCH.h"
#include "ZenChan.h"

#include "Transform.h"
#include "BoxCollider.h"
#include "ZenChanStates.h"
#include "RigidBody2D.h"
#include "SpriteComponent.h"
#include "AIController.h"

fuel::ZenChan::ZenChan()
	: m_pAIController(nullptr)
{
	AddComponent<Transform>();
	m_pRigidBody = AddComponent<fuel::RigidBody2D>();
	AddComponent<fuel::BoxCollider>();
	m_pSpriteRenderer = AddComponent<fuel::SpriteComponent>();
	m_pAIController = AddComponent<fuel::AIController>();
}

void fuel::ZenChan::Initialize()
{
	GameObject::Initialize();
	
	m_pRigidBody->SetIsKinematic(false);
	m_pRigidBody->UseGravity(true);
	m_pRigidBody->SetBounciness(0.2f);
	
	m_pSpriteRenderer->SetTexture("CharacterSpriteSheet.png");
	m_pSpriteRenderer->SetColumns(8);
	m_pSpriteRenderer->SetRows(16);
	m_pSpriteRenderer->SetAnimTime(0.1f);
	m_pSpriteRenderer->AddAnimation(4, 8);
	m_pSpriteRenderer->AddAnimation(5, 8);
	m_pSpriteRenderer->SetScale(1.f, 1.f);
	m_pSpriteRenderer->SetAnimation(4);
	m_pSpriteRenderer->SetDirectionIDs(5, 4);
	
	GetComponent<BoxCollider>()->SetDimensions(fuel::Rectf(0.f, 0.f, 16.f, 16.f));
}

void fuel::ZenChan::Start()
{
	GameObject::Start();
	m_pAIController->SetState(new WanderState_ZN());
}

void fuel::ZenChan::Update()
{
	GameObject::Update();
	if (m_pPlayer1)
	{
		const Vector3 pos{ m_Transform->GetPosition() };
		const Vector3 posPlayer{ m_pPlayer1->GetTransform()->GetPosition() };
		const Vector3 distance{ posPlayer - pos };
		if (std::abs(distance.x) < 100.f && std::abs(distance.y) < 60.f && posPlayer.y < pos.y + 16.f)
		{
			AttackState_ZN* attackState = new AttackState_ZN();
			attackState->SetTarget(m_pPlayer1);
			m_pAIController->SetState(attackState);
		}
		else if (distance.MagnitudeSqr() > std::powf(350.f, 2.f))
		{
			m_pAIController->SetState(new WanderState_ZN());
		}
	}
	else if (m_pPlayer2)
	{
		const Vector3 pos{ m_Transform->GetPosition() };
		const Vector3 posPlayer{ m_pPlayer2->GetTransform()->GetPosition() };
		const Vector3 distance{ posPlayer - pos };
		if (std::abs(distance.x) < 100.f && std::abs(distance.y) < 60.f && posPlayer.y < pos.y + 16.f)
		{
			AttackState_ZN* attackState = new AttackState_ZN();
			attackState->SetTarget(m_pPlayer2);
			m_pAIController->SetState(attackState);
		}
		else if (distance.MagnitudeSqr() > std::powf(350.f, 2.f))
		{
			m_pAIController->SetState(new WanderState_ZN());
		}
	}
}

void fuel::ZenChan::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void fuel::ZenChan::Render() const
{
	GameObject::Render();
}

void fuel::ZenChan::AttachScene(fuel::Scene* scene)
{
	m_pLinkedScene = scene;
}

void fuel::ZenChan::SetName(const std::string& name)
{
	m_Name = name;
}

std::string& fuel::ZenChan::GetName()
{
	return m_Name;
}

void fuel::ZenChan::SetPlayer1(GameObject* pPlayer1)
{
	m_pPlayer1 = pPlayer1;
}

void fuel::ZenChan::SetPlayer2(GameObject* pPlayer2)
{
	m_pPlayer2 = pPlayer2;
}

fuel::ObjectType fuel::ZenChan::GetObjectType() const
{
	return GAMEOBJECT;
}

void fuel::ZenChan::OnCollisionEnter(BaseCollider* other)
{
	GameObject::OnCollisionEnter(other);
}

void fuel::ZenChan::OnCollisionStay(BaseCollider* other)
{
	GameObject::OnCollisionStay(other);
}

void fuel::ZenChan::OnCollisionExit(BaseCollider* other)
{
	GameObject::OnCollisionExit(other);
}

void fuel::ZenChan::OnTriggerEnter(BaseCollider* other)
{
	GameObject::OnTriggerEnter(other);
}

void fuel::ZenChan::OnTriggerStay(BaseCollider* other)
{
	GameObject::OnTriggerStay(other);
}

void fuel::ZenChan::OnTriggerExit(BaseCollider* other)
{
	GameObject::OnTriggerExit(other);
}

void fuel::ZenChan::DrawComponents()
{
	GameObject::DrawComponents();
}
