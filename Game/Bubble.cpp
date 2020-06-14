#include "FuelEnginePCH.h"
#include "Bubble.h"

#include "Transform.h"
#include "BoxCollider.h"
#include "RenderComponent.h"
#include "RigidBody2D.h"
#include "Scene.h"

int fuel::Bubble::m_Count = 0;

fuel::Bubble::Bubble()
	: m_pRigidBody(nullptr)
	, m_pSpriteRenderer(nullptr)
	, m_CapturedEnemy(false)
{
	++m_Count;

	m_Transform = AddComponent<Transform>();
	m_pRigidBody = AddComponent<RigidBody2D>();
	AddComponent<BoxCollider>();
	m_pSpriteRenderer = AddComponent<RenderComponent>();
}

void fuel::Bubble::Initialize()
{
	GameObject::Initialize();
	m_pSpriteRenderer->SetTransform(m_Transform);

	
	m_pRigidBody->SetDrag(0.5f);
	m_pRigidBody->UseGravity(false);
	m_pRigidBody->SetMass(1.f);

	m_pSpriteRenderer->SetTexture("Bubble.png");

	m_Name = "Bubble_" + std::to_string(m_Count);
}

void fuel::Bubble::Start()
{
	GameObject::Start();
}

void fuel::Bubble::Update()
{
	GameObject::Update();
}

void fuel::Bubble::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void fuel::Bubble::Render() const
{
	GameObject::Render();
}

void fuel::Bubble::AttachScene(fuel::Scene* scene)
{
	m_pLinkedScene = scene;
}

void fuel::Bubble::SetName(const std::string& name)
{
	m_Name = name;
}

std::string& fuel::Bubble::GetName()
{
	return m_Name;
}

void fuel::Bubble::SetSpawnPosition(const Vector2& position)
{
	m_pRigidBody->SetPosition(position);
}

void fuel::Bubble::SetDirection(const Vector2& direction)
{
	m_pRigidBody->AddForce(direction, true);
}

fuel::ObjectType fuel::Bubble::GetObjectType() const
{
	return fuel::ObjectType::GAMEOBJECT;
}

void fuel::Bubble::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
	/*if (other->GetGameObject()->CompareTag("Player") && m_CapturedEnemy)
	{
		// todo: Add score
		// todo: spawn pickup
		m_pLinkedScene->RemoveFromScene(m_Name);
	}
	else if (other->GetGameObject()->CompareTag("Enemy"))
	{
		m_CapturedEnemy = true;
		m_pSpriteRenderer->SetTexture("Bubble_ZenChan.png");
		m_pRigidBody->SetForce({ 0.f, 0.f });
	}*/
	//else
	//{
		//m_IsActive = false;
		//m_pLinkedScene->RemoveFromScene(m_Name);
	//}
}

void fuel::Bubble::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::Bubble::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::Bubble::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::Bubble::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::Bubble::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::Bubble::DrawComponents()
{
	GameObject::DrawComponents();
}
