#include "FuelEnginePCH.h"
#include "AIController.h"
#include "AIState.h"

fuel::AIController::~AIController()
{
	SafeDelete(m_pCurrentState);
}

void fuel::AIController::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::AIController::OnStart()
{
}

void fuel::AIController::Update()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Update();
	}
}

void fuel::AIController::FixedUpdate()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->FixedUpdate();
	}
}

void fuel::AIController::Render() const
{
}

void fuel::AIController::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::AIController::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::AIController::GetType()
{
	return typeid(this).hash_code();
}

void fuel::AIController::SetState(AIState* newState)
{
	if (m_pCurrentState)
	{
		const size_t id1{ m_pCurrentState->GetID() };
		const size_t id2{ newState->GetID() };
		if (id1 != id2)
			SafeDelete(m_pCurrentState);
		else
		{
			SafeDelete(newState);
			return;
		}
	}
	
	m_pCurrentState = newState;
	m_pCurrentState->Enter(m_pGameObject);
}

fuel::ComponentType fuel::AIController::GetCompType() const
{
	return ComponentType::AICONTROLLER;
}

void fuel::AIController::Safe(std::ofstream& binStream) const
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::AIController::Load(std::ifstream& binStream)
{
	UNREFERENCED_PARAMETER(binStream);
}

void fuel::AIController::OnCollisionEnter(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONCOLLISIONENTER, other });
}

void fuel::AIController::OnCollisionStay(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONCOLLISIONSTAY, other });
}

void fuel::AIController::OnCollisionExit(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONCOLLISIONEXIT, other });
}

void fuel::AIController::OnTriggerEnter(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONTRIGGERENTER, other });
}

void fuel::AIController::OnTriggerStay(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONTRIGGERSTAY, other });
}

void fuel::AIController::OnTriggerExit(BaseCollider* other)
{
	m_pCurrentState->TriggerPhysicsEvent({ ONTRIIGEREXIT, other });
}

void fuel::AIController::DrawGUI()
{
}

const std::string& fuel::AIController::GetID() const
{
	return m_ID;
}

