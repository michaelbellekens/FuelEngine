#include "FuelEnginePCH.h"
#include "BubbleComponent.h"

#include "BoxCollider.h"
#include "RigidBody2D.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "Scene.h"
#include "SoundManager.h"

fuel::BubbleComponent::BubbleComponent()
	: m_ScorePlayer1()
	, m_ScorePlayer2()
{
}

void fuel::BubbleComponent::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::BubbleComponent::OnStart()
{
	m_pRigidBody = m_pGameObject->GetComponent<RigidBody2D>();
	m_pRenderComp = m_pGameObject->GetComponent<RenderComponent>();

	m_pRigidBody->SetDrag(0.5f);
	m_pRigidBody->UseGravity(false);
	m_pRigidBody->SetMass(1.f);

	m_pRenderComp->SetTexture("Bubble.png");

	m_pGameObject->GetComponent<BoxCollider>()->SetDimensions({ 0.f, 0.f, 16.f, 16.f });
	m_pGameObject->GetComponent<BoxCollider>()->SetIsTrigger(true);
}

void fuel::BubbleComponent::Update()
{
}

void fuel::BubbleComponent::FixedUpdate()
{
	if (m_CapturedEnemy)
	{
		m_pRigidBody->SetPosition(m_pGameObject->GetTransform()->GetPosition());
	}
}

void fuel::BubbleComponent::Render() const
{
}

void fuel::BubbleComponent::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::BubbleComponent::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::BubbleComponent::GetType()
{
	return typeid(this).hash_code();
}

void fuel::BubbleComponent::SetOwner(PlayerID owner)
{
	m_Owner = owner;
}

void fuel::BubbleComponent::SetScoreReferences(int* score1, int* score2)
{
	m_ScorePlayer1 = score1;
	m_ScorePlayer2 = score2;
}

fuel::ComponentType fuel::BubbleComponent::GetCompType() const
{
	return ComponentType::BUBBLE;
}

void fuel::BubbleComponent::Safe(std::ofstream& binStream) const
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::BubbleComponent::Load(std::ifstream& binStream)
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::BubbleComponent::OnCollisionEnter(BaseCollider* other)
{
	if (other->GetGameObject()->CompareTag("Player") && m_CapturedEnemy)
	{
		AddScore(100);
		m_pRigidBody->SetPosition({ -100.f, -100.f, 0.f });
		m_pGameObject->GetTransform()->SetPosition(-100.f, -100.f);
		m_pRigidBody->SetIsKinematic(true);
		m_pGameObject->SetActive(false);
		SoundManager::GetInstance().StartSound("ScoreUp");
	}
	else if (other->GetGameObject()->CompareTag("Enemy") && !m_CapturedEnemy)
	{
		m_CapturedEnemy = true;
		m_pRenderComp->SetTexture("Bubble_ZenChan.png");
		m_pRigidBody->SetForce({ 0.f, 0.f });

		other->GetGameObject()->GetTransform()->SetPosition(-200.f, -200.f);
		other->GetGameObject()->SetActive(false);
		AddScore(50);
		SoundManager::GetInstance().StartSound("EnemyCaptured");
	}
	else if (other->GetGameObject()->CompareTag("StaticScene"))
	{
		Logger::LogWarning("Bubble collides with: " + other->GetGameObject()->GetName());
		m_pRigidBody->SetPosition({ -100.f, -100.f, 0.f });
		m_pGameObject->GetTransform()->SetPosition(-100.f, -100.f);
		m_pRigidBody->SetIsKinematic(true);
		m_pGameObject->SetActive(false);
		SoundManager::GetInstance().StartSound("BubblePop");
	}
}

void fuel::BubbleComponent::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::BubbleComponent::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::BubbleComponent::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::BubbleComponent::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::BubbleComponent::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::BubbleComponent::DrawGUI()
{
}

const std::string& fuel::BubbleComponent::GetID() const
{
	return m_ID;
}

void fuel::BubbleComponent::AddScore(const int score)
{
	switch (m_Owner)
	{
	case PlayerID::PlayerOne:
		*m_ScorePlayer1 += score;
		break;
	case PlayerID::PlayerTwo:
		*m_ScorePlayer2 += score;
		break;
	}
}
