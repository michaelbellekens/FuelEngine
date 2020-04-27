#include "FuelEnginePCH.h"
#include "RigidBody2D.h"

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Logger.h"
#include "Time.h"

void fuel::RigidBody2D::Initialize()
{
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;
	m_ID = ss.str();
}

void fuel::RigidBody2D::OnStart()
{
	for (BaseCollider* collider : m_pColliders)
	{
		m_pGameObject->GetScene()->AddCollider(collider);
	}
	
	m_pTransform = m_pGameObject->GetTransform();
	if (m_pTransform)
	{
		m_Position = m_pTransform->GetPosition();
	}
}

void fuel::RigidBody2D::Update()
{
	m_pTransform->SetPosition(m_Position);
}

void fuel::RigidBody2D::FixedUpdate()
{
	m_Acceleration = Vector2();
	if (!m_IsKinematic)
	{
		const Vector2 accelByForce{ m_Force.x / m_Mass, m_Force.y / m_Mass };

		if(m_UseGravity)
			m_Acceleration = m_Gravity;
		m_Acceleration += accelByForce;

		m_Velocity += m_Acceleration * Time::GetFixedDeltaTime();
		m_Position += m_Velocity;

		CheckCollision();
	}
}

void fuel::RigidBody2D::Render() const
{
}

void fuel::RigidBody2D::SetGameObject(GameObject* parent)
{
	m_pGameObject = parent;
}

fuel::GameObject* fuel::RigidBody2D::GetGameObject() const
{
	return m_pGameObject;
}

size_t fuel::RigidBody2D::GetType()
{
	return typeid(this).hash_code();
}

void fuel::RigidBody2D::MovePosition(const Vector3& pos)
{
	UNREFERENCED_PARAMETER(pos);
}

fuel::Vector3 fuel::RigidBody2D::GetPosition() const
{
	return m_Position;
}

void fuel::RigidBody2D::AddForce(const Vector2& force)
{
	m_Force += force;
}

void fuel::RigidBody2D::SetForce(const Vector2& force)
{
	m_Force = force;
}

void fuel::RigidBody2D::SetDrag(float drag)
{
	m_Drag = drag;
}

void fuel::RigidBody2D::SetIsKinematic(bool isKinematic)
{
	m_IsKinematic = isKinematic;
}

bool fuel::RigidBody2D::GetIsKinematic() const
{
	return m_IsKinematic;
}

void fuel::RigidBody2D::SetMass(float mass)
{
	m_Mass = mass;
}

float fuel::RigidBody2D::GetMass() const
{
	return m_Mass;
}

void fuel::RigidBody2D::UseGravity(bool useGravity)
{
	m_UseGravity = useGravity;
}

void fuel::RigidBody2D::SetGravity(const Vector2& gravity)
{
	m_Gravity = gravity;
}

fuel::Vector2 fuel::RigidBody2D::GetGravity() const
{
	return m_Gravity;
}

void fuel::RigidBody2D::AddCollider(BaseCollider* collider)
{
	const std::vector<BaseCollider*>::iterator it{ std::find(m_pColliders.begin(), m_pColliders.end(), collider) };
	if (it == m_pColliders.end())
	{
		m_pColliders.push_back(collider);
	}
	else
	{
		Logger::LogWarning("Collider is already added to Rigidbody of: " + m_pGameObject->GetName());
	}
}

void fuel::RigidBody2D::DrawGUI()
{
	ImGui::Text("RigidBody2D Component");
	ImGui::Spacing();
}

const std::string& fuel::RigidBody2D::GetID() const
{
	return m_ID;
}

void fuel::RigidBody2D::CheckCollision()
{
	// todo: Check if rigidBody is Colliding with something
	const std::vector<BaseCollider*> sceneColliders{ m_pGameObject->GetScene()->GetAllColliders() };
	for (BaseCollider* sceneCollider : sceneColliders)
	{
		const std::vector<BaseCollider*>::iterator it{ std::find(m_pColliders.begin(), m_pColliders.end(), sceneCollider) };
		if (it != m_pColliders.end())
			continue;

		switch (sceneCollider->GetShapeType())
		{
		case ShapeType::Sphere:
			CheckSphereCollision(sceneCollider);
			break;
		case ShapeType::Rect:
			CheckBoxCollision(sceneCollider);
			break;
		}
	}
}

void fuel::RigidBody2D::CheckBoxCollision(BaseCollider* sceneCollider)
{
	BoxCollider* other{ static_cast<BoxCollider*>(sceneCollider) };
	for (BaseCollider* ownedCollider : m_pColliders)
	{
		if (ownedCollider->IsColliding(other->GetDimensions()))
		{
			Logger::LogWarning(other->GetGameObject()->GetName() + " is overlapping with rigidbody: " + m_pGameObject->GetName());
		}
	}
}

void fuel::RigidBody2D::CheckSphereCollision(BaseCollider* sceneCollider)
{
	SphereCollider* other{ static_cast<SphereCollider*>(sceneCollider) };
	for (BaseCollider* ownedCollider : m_pColliders)
	{
		if (ownedCollider->IsColliding(other->GetDimensions()))
		{
			Logger::LogWarning(other->GetGameObject()->GetName() + " is overlapping with rigidbody: " + m_pGameObject->GetName());
		}
	}
}
