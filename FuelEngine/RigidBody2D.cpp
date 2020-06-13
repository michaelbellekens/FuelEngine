#include "FuelEnginePCH.h"
#include "RigidBody2D.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Scene.h"
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
		Clamp(m_Bounciness, 1.f, 0.f);
		
		float dragFactor{ m_Drag * Time::GetFixedDeltaTime() };
		if (m_Force.MagnitudeSqr() != 0)
		{
			m_Force.x -= m_Force.x > 0.f ? dragFactor : -dragFactor;
			m_Force.y -= m_Force.y >= 0.f ? 0.f : -dragFactor;

			if (m_Force.MagnitudeSqr() < 0.05f)
				m_Force = Vector2();
		}
		
		const Vector2 accelByForce{ m_Force.x / m_Mass, m_Force.y / m_Mass };

		if (m_UseGravity)
			m_Acceleration = m_Gravity;
		m_Acceleration += accelByForce;
		
		m_Velocity += m_Acceleration * Time::GetFixedDeltaTime();

		// Apply drag to negative vertical velocity
		if (m_Velocity.y < 0.f)
		{
			m_Velocity.y -= m_Velocity.y > 0.f ? dragFactor : -dragFactor;
		}
		
		// Apply drag to velocity horizontal velocity
		if (m_Velocity.x != 0.f)
		{
			if (std::abs(m_Velocity.x) < 0.3f)
				dragFactor /= 4.f;

			m_Velocity.x -= m_Velocity.x > 0.f ? dragFactor : -dragFactor;
			m_Velocity.x = std::abs(m_Velocity.x) < 0.04f ? 0.f : m_Velocity.x;
		}

		m_IsFacingLeft = m_Velocity.x > 0.f ? false : true;
		
		m_Position += m_Velocity + m_InputVelocity;

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
	m_InputVelocity.x = std::abs(m_Velocity.x) < 0.5f ? pos.x : 0.f;
}

fuel::Vector3 fuel::RigidBody2D::GetPosition() const
{
	return m_Position;
}

void fuel::RigidBody2D::SetPosition(const Vector3& pos)
{
	m_Position = pos;
}

bool fuel::RigidBody2D::GetIsFacingLeft() const
{
	return m_IsFacingLeft;
}

void fuel::RigidBody2D::AddForce(const Vector2& force, const bool impulse)
{
	m_Force += force;
	if (impulse)
		m_Velocity += force;
}

void fuel::RigidBody2D::SetForce(const Vector2& force)
{
	m_Force = force;
}

void fuel::RigidBody2D::SetDrag(const float drag)
{
	m_Drag = drag;
}

void fuel::RigidBody2D::SetIsKinematic(const bool isKinematic)
{
	m_IsKinematic = isKinematic;
}

bool fuel::RigidBody2D::GetIsKinematic() const
{
	return m_IsKinematic;
}

void fuel::RigidBody2D::SetMass(const float mass)
{
	m_Mass = mass;
}

float fuel::RigidBody2D::GetMass() const
{
	return m_Mass;
}

void fuel::RigidBody2D::UseGravity(const bool useGravity)
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

void fuel::RigidBody2D::SetBounciness(const float bounciness)
{
	m_Bounciness = bounciness;
}

void fuel::RigidBody2D::AddCollider(BaseCollider* collider)
{
	const std::vector<BaseCollider*>::iterator it{ std::find(m_pColliders.begin(), m_pColliders.end(), collider) };
	if (it == m_pColliders.end())
	{
		m_pColliders.push_back(collider);
		return;
	}

	Logger::LogWarning("Collider is already added to Rigidbody of: " + m_pGameObject->GetName());
}

bool fuel::RigidBody2D::IsGrounded()
{
	const std::vector<BaseCollider*> sceneColliders{ m_pGameObject->GetScene()->GetAllColliders() };
	for (BaseCollider* ownCollider : m_pColliders)
	{
		Rectf rectDim;
		Spheref sphereDim;
		
		Vector2 pos{};
		float width{};
		float height{};
		
		switch (ownCollider->GetShapeType())
		{
		case ShapeType::Sphere:
			rectDim = reinterpret_cast<BoxCollider*>(ownCollider)->GetDimensions();
			pos.x = rectDim.x;
			pos.y = rectDim.y;
			width = rectDim.width;
			height = rectDim.height;
			break;
		case ShapeType::Rect:
			sphereDim = reinterpret_cast<SphereCollider*>(ownCollider)->GetDimensions();
			pos.x = sphereDim.x;
			pos.y = sphereDim.y;
			width = sphereDim.radius;
			height = sphereDim.radius;
			break;
		}
		
		const Vector2 leftPoint{ pos.x + 1.f, pos.y + height + 2.f };
		const Vector2 rightPoint{ pos.x + width - 1.f, pos.y + height + 2.f };
		
		for (BaseCollider* sceneCollider : sceneColliders)
		{
			// If current scene collider is part of this Rigidbody2D skip to next collider
			const std::vector<BaseCollider*>::iterator it{ std::find(m_pColliders.begin(), m_pColliders.end(), sceneCollider) };
			if (it != m_pColliders.end())
				continue;

			if (sceneCollider->IsColliding(leftPoint) || sceneCollider->IsColliding(rightPoint))
				return true;
		}	
	}
	return false;
}

bool fuel::RigidBody2D::IsOnEdge()
{
	bool isLeftOnGround{ false };
	bool isRightOnGround{ false };
	
	const std::vector<BaseCollider*> sceneColliders{ m_pGameObject->GetScene()->GetAllColliders() };
	for (BaseCollider* ownCollider : m_pColliders)
	{
		Rectf rectDim;
		Spheref sphereDim;

		Vector2 pos{};
		float width{};
		float height{};

		switch (ownCollider->GetShapeType())
		{
		case ShapeType::Sphere:
			rectDim = reinterpret_cast<BoxCollider*>(ownCollider)->GetDimensions();
			pos.x = rectDim.x;
			pos.y = rectDim.y;
			width = rectDim.width;
			height = rectDim.height;
			break;
		case ShapeType::Rect:
			sphereDim = reinterpret_cast<SphereCollider*>(ownCollider)->GetDimensions();
			pos.x = sphereDim.x;
			pos.y = sphereDim.y;
			width = sphereDim.radius;
			height = sphereDim.radius;
			break;
		}

		const Vector2 leftPoint{ pos.x + 1.f, pos.y + height + 2.f };
		const Vector2 rightPoint{ pos.x + width - 1.f, pos.y + height + 2.f };

		for (BaseCollider* sceneCollider : sceneColliders)
		{
			// If current scene collider is part of this Rigidbody2D skip to next collider
			const std::vector<BaseCollider*>::iterator it{ std::find(m_pColliders.begin(), m_pColliders.end(), sceneCollider) };
			if (it != m_pColliders.end())
				continue;

			if (!isLeftOnGround)
				isLeftOnGround = sceneCollider->IsColliding(leftPoint);
			if (!isRightOnGround)
				isRightOnGround = sceneCollider->IsColliding(rightPoint);
		}
	}

	if (isLeftOnGround && !isRightOnGround)
		return true;
	if (!isLeftOnGround && isRightOnGround)
		return true;
	return false;
}

void fuel::RigidBody2D::Safe(std::ofstream& binStream) const
{
	binStream.write((const char*)&m_Position, sizeof(Vector3));
	binStream.write((const char*)&m_Velocity, sizeof(Vector2));
	binStream.write((const char*)&m_Acceleration, sizeof(Vector2));
	binStream.write((const char*)&m_Force, sizeof(Vector2));

	binStream.write((const char*)&m_Mass, sizeof(float));
	binStream.write((const char*)&m_Drag, sizeof(float));

	binStream.write((const char*)&m_Gravity, sizeof(Vector2));
	binStream.write((const char*)&m_Bounciness, sizeof(float));
	
	binStream.write((const char*)&m_IsKinematic, sizeof(bool));
	binStream.write((const char*)&m_UseGravity, sizeof(bool));
}

void fuel::RigidBody2D::Load(std::ifstream& binStream)
{
	binStream.read((char*)&m_Position, sizeof(Vector3));
	binStream.read((char*)&m_Velocity, sizeof(Vector2));
	binStream.read((char*)&m_Acceleration, sizeof(Vector2));
	binStream.read((char*)&m_Force, sizeof(Vector2));

	binStream.read((char*)&m_Mass, sizeof(float));
	binStream.read((char*)&m_Drag, sizeof(float));

	binStream.read((char*)&m_Gravity, sizeof(Vector2));
	binStream.read((char*)&m_Bounciness, sizeof(float));

	binStream.read((char*)&m_IsKinematic, sizeof(bool));
	binStream.read((char*)&m_UseGravity, sizeof(bool));
}

fuel::ComponentType fuel::RigidBody2D::GetCompType() const
{
	return ComponentType::RIGIDBODY;
}

void fuel::RigidBody2D::OnCollisionEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::OnCollisionStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::OnCollisionExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::OnTriggerEnter(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::OnTriggerStay(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::OnTriggerExit(BaseCollider* other)
{
	UNREFERENCED_PARAMETER(other);
}

void fuel::RigidBody2D::DrawGUI()
{
	ImGui::Text("RigidBody2D Component");
	ImGui::Spacing();

	// Position -----------------------------------------------------
	const std::string posLabelX{ "##RigidBody2DPosX_" + m_ID };
	const std::string posLabelY{ "##RigidBody2DPosY_" + m_ID };
	const std::string posLabelZ{ "##RigidBody2DPosZ_" + m_ID };
	ImGui::Text("Position:");

	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelX.c_str(), &m_Position.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelY.c_str(), &m_Position.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(290);
	ImGui::Text("Z:");

	ImGui::SameLine(305);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(posLabelZ.c_str(), &m_Position.z, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Velocity -----------------------------------------------------
	const std::string VelocityLabelX{ "##RigidBody2DVelX_" + m_ID };
	const std::string VelocityLabelY{ "##RigidBody2DVelY_" + m_ID };
	ImGui::Text("Velocity:");

	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(VelocityLabelX.c_str(), &m_Velocity.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(VelocityLabelY.c_str(), &m_Velocity.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Force --------------------------------------------------------
	const std::string forceLabelX{ "##RigidBody2DForceX_" + m_ID };
	const std::string forceLabelY{ "##RigidBody2DForceY_" + m_ID };
	ImGui::Text("Force:");

	ImGui::SameLine(80);
	ImGui::Text("X:");

	ImGui::SameLine(95);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(forceLabelX.c_str(), &m_Force.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(185);
	ImGui::Text("Y:");

	ImGui::SameLine(200);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(forceLabelY.c_str(), &m_Force.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Acceleration -------------------------------------------------
	const std::string accelLabelX{ "##RigidBody2DAccelX_" + m_ID };
	const std::string accelLabelY{ "##RigidBody2DAccelY_" + m_ID };
	ImGui::Text("Acceleration:");

	ImGui::SameLine(110);
	ImGui::Text("X:");

	ImGui::SameLine(125);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(accelLabelX.c_str(), &m_Acceleration.x, 0, 0, "%.1f");
	ImGui::PopItemWidth();

	ImGui::SameLine(215);
	ImGui::Text("Y:");

	ImGui::SameLine(230);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(accelLabelY.c_str(), &m_Acceleration.y, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Mass ---------------------------------------------------------
	const std::string massLabel{ "##RigidBody2DMass_" + m_ID };
	ImGui::Text("Mass:");

	ImGui::SameLine(50);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(massLabel.c_str(), &m_Mass, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Drag ---------------------------------------------------------
	const std::string dragLabel{ "##RigidBody2DDrag_" + m_ID };
	ImGui::Text("Drag:");

	ImGui::SameLine(50);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(dragLabel.c_str(), &m_Drag, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// Bounciness ---------------------------------------------------
	const std::string bouncinessLabel{ "##RigidBody2DBounciness_" + m_ID };
	ImGui::Text("Bounciness:");

	ImGui::SameLine(100);
	ImGui::PushItemWidth(80);
	ImGui::InputFloat(bouncinessLabel.c_str(), &m_Bounciness, 0, 0, "%.1f");
	ImGui::PopItemWidth();
	// --------------------------------------------------------------

	// IsKinematic --------------------------------------------------
	const std::string kinematicLabel{ "##RigidBody2DIsKinematic_" + m_ID };
	ImGui::Text("Is Kinematic:");
	ImGui::SameLine(100);
	ImGui::Checkbox(kinematicLabel.c_str(), &m_IsKinematic);
	// --------------------------------------------------------------

	// Gravity ------------------------------------------------------
	const std::string gravityLabel{ "##RigidBody2DUseGravity_" + m_ID };
	ImGui::Text("Use Gravity:");
	ImGui::SameLine(100);
	ImGui::Checkbox(gravityLabel.c_str(), &m_UseGravity);
	// --------------------------------------------------------------
}

const std::string& fuel::RigidBody2D::GetID() const
{
	return m_ID;
}

bool fuel::RigidBody2D::IsCollidingAfterMove()
{
	const std::vector<BaseCollider*> sceneColliders{ m_pGameObject->GetScene()->GetAllColliders() };
	for (BaseCollider* sceneCollider : sceneColliders)
	{
		// If current scene collider is part of this Rigidbody2D skip to next collider
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
	return true;
}

void fuel::RigidBody2D::CheckCollision()
{
	const std::vector<BaseCollider*> sceneColliders{ m_pGameObject->GetScene()->GetAllColliders() };
	for (BaseCollider* sceneCollider : sceneColliders)
	{
		// If current scene collider is part of this Rigidbody2D skip to next collider
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
	const auto it = m_RegisteredCollisions.find(sceneCollider->GetID());
	if (it == m_RegisteredCollisions.end())
	{
		m_RegisteredCollisions.insert({ sceneCollider->GetID(), std::make_pair(false, false) });
	}
	
	const bool isColliding{ m_RegisteredCollisions.at(sceneCollider->GetID()).first };
	const bool isTrigger{ m_RegisteredCollisions.at(sceneCollider->GetID()).second };
	bool removeCollider{ true };
	
	BoxCollider* other{ static_cast<BoxCollider*>(sceneCollider) };
	for (BaseCollider* ownedCollider : m_pColliders)
	{
		if (ownedCollider->IsColliding(other->GetDimensions()))
		{
			removeCollider = false;
			if (other->IsTrigger())
			{
				m_RegisteredCollisions.at(sceneCollider->GetID()).second = true; // inTrigger
				m_RegisteredCollisions.at(sceneCollider->GetID()).first = false; // isColliding
			}
			else
			{
				m_RegisteredCollisions.at(sceneCollider->GetID()).first = true; // isColliding
				m_RegisteredCollisions.at(sceneCollider->GetID()).second = false; // inTrigger

				if (!other->CanPassFromBellow() || m_Velocity.y >= 0.f)
				{
					SetVelocityAfterCollision(ownedCollider, sceneCollider);
				}
			}
		}
		else
		{
			m_RegisteredCollisions.at(sceneCollider->GetID()).first = false; // isColliding
			m_RegisteredCollisions.at(sceneCollider->GetID()).second = false; // inTrigger
		}
		HandlePhysicsEvents(isTrigger, m_RegisteredCollisions.at(sceneCollider->GetID()).second, isColliding, m_RegisteredCollisions.at(sceneCollider->GetID()).first, other);
	}

	if (removeCollider)
		m_RegisteredCollisions.erase(sceneCollider->GetID());
}

void fuel::RigidBody2D::CheckSphereCollision(BaseCollider* sceneCollider)
{
	const auto it = m_RegisteredCollisions.find(sceneCollider->GetID());
	if (it == m_RegisteredCollisions.end())
	{
		m_RegisteredCollisions.insert({ sceneCollider->GetID(), std::make_pair(false, false) });
	}

	const bool isColliding{ m_RegisteredCollisions.at(sceneCollider->GetID()).first };
	const bool isTrigger{ m_RegisteredCollisions.at(sceneCollider->GetID()).second };
	bool removeCollider{ true };
	
	SphereCollider* other{ static_cast<SphereCollider*>(sceneCollider) };
	for (BaseCollider* ownedCollider : m_pColliders)
	{
		if (ownedCollider->IsColliding(other->GetDimensions()))
		{
			removeCollider = false;
			if (other->IsTrigger())
			{
				m_RegisteredCollisions.at(sceneCollider->GetID()).second = true; // inTrigger
				m_RegisteredCollisions.at(sceneCollider->GetID()).first = false; // isColliding
			}
			else
			{
				m_RegisteredCollisions.at(sceneCollider->GetID()).first = true; // isColliding
				m_RegisteredCollisions.at(sceneCollider->GetID()).second = false; // inTrigger

				if (!other->CanPassFromBellow() || m_Velocity.y >= 0.f)
				{
					SetVelocityAfterCollision(ownedCollider, sceneCollider);
				}
			}
		}
		else
		{
			m_RegisteredCollisions.at(sceneCollider->GetID()).first = false;
			m_RegisteredCollisions.at(sceneCollider->GetID()).second = false;
		}
		HandlePhysicsEvents(isTrigger, m_RegisteredCollisions.at(sceneCollider->GetID()).second, isColliding, m_RegisteredCollisions.at(sceneCollider->GetID()).first, other);
	}

	if (removeCollider)
		m_RegisteredCollisions.erase(sceneCollider->GetID());
}

void fuel::RigidBody2D::SetVelocityAfterCollision(BaseCollider* ownCollider, BaseCollider* sceneCollider)
{
	const float pMidX = ownCollider->GetMidPoint().x;
	const float pMidY = ownCollider->GetMidPoint().y;
	const float aMidX = sceneCollider->GetMidPoint().x;
	const float aMidY = sceneCollider->GetMidPoint().y;

	Rectf rectDim;
	Spheref sphereDim;

	Vector2 ownColPos{};
	Vector2 ownColDim{};
	switch (ownCollider->GetShapeType())
	{
	case ShapeType::Rect:

		rectDim = reinterpret_cast<BoxCollider*>(ownCollider)->GetDimensions();
		ownColPos.x = rectDim.x;
		ownColPos.y = rectDim.y;
		ownColDim.x = rectDim.width;
		ownColDim.y = rectDim.height;
		break;
	case ShapeType::Sphere:
		sphereDim = reinterpret_cast<SphereCollider*>(ownCollider)->GetDimensions();
		ownColPos.x = sphereDim.x;
		ownColPos.y = sphereDim.y;
		ownColDim.x = sphereDim.radius;
		ownColDim.y = sphereDim.radius;
		break;
	}
	
	Vector2 sceneColPos{};
	Vector2 sceneColDim{};
	switch (sceneCollider->GetShapeType())
	{
	case ShapeType::Rect:

		rectDim = reinterpret_cast<BoxCollider*>(sceneCollider)->GetDimensions();
		sceneColPos.x = rectDim.x;
		sceneColPos.y = rectDim.y;
		sceneColDim.x = rectDim.width;
		sceneColDim.y = rectDim.height;
		break;
	case ShapeType::Sphere:
		sphereDim = reinterpret_cast<SphereCollider*>(sceneCollider)->GetDimensions();
		sceneColPos.x = sphereDim.x;
		sceneColPos.y = sphereDim.y;
		sceneColDim.x = sphereDim.radius;
		sceneColDim.y = sphereDim.radius;
		break;
	}

	// To find the side of entry calculate based on
	// the normalized sides
	float dx = (aMidX - pMidX) / (sceneColDim.x / 2.f);
	float dy = (aMidY - pMidY) / (sceneColDim.y / 2.f);

	// Calculate the absolute change in x and y
	float absDX = abs(dx);
	float absDY = abs(dy);

	if (absDX > absDY) {

		// If the player is approaching from positive X
		if (dx < 0 && m_Velocity.x + m_InputVelocity.x < 0.f) {
			m_Position.x = sceneColPos.x + sceneColDim.x;

			m_Velocity.x = -(m_Velocity.x + (m_InputVelocity.x * 2.f)) * m_Bounciness;
			if (abs(m_Velocity.x) < 0.05) {
				m_Velocity.x = 0;
			}
		}
		else if(dx > 0 && m_Velocity.x + m_InputVelocity.x > 0.f) {
			// If the player is approaching from negative X
			m_Position.x = sceneColPos.x - ownColDim.x;

			m_Velocity.x = -(m_Velocity.x + (m_InputVelocity.x * 2.f)) * m_Bounciness;
			if (abs(m_Velocity.x) < 0.05) {
				m_Velocity.x = 0;
			}
		}
	}
	else {

		// If the player is approaching from positive Y
		if (dy > 0 && m_Velocity.y > 0.f) {
			m_Position.y = sceneColPos.y - ownColDim.y;
			m_Force.y = 0.f;
			
			// Velocity component
			m_Velocity.y = -m_Velocity.y * m_Bounciness;
			if (abs(m_Velocity.y) < 0.05)
				m_Velocity.y = 0;
		}
		else if (dy < 0 && m_Velocity.y < 0.f){
			// If the player is approaching from negative Y
			m_Position.y = sceneColPos.y + sceneColDim.y;

			// Velocity component
			m_Velocity.y = -m_Velocity.y/* * m_Bounciness*/;
			if (abs(m_Velocity.y) < 0.05)
				m_Velocity.y = 0;
		}
	}

}

void fuel::RigidBody2D::HandlePhysicsEvents(const bool prevTriggerState, const bool triggerState, const bool prevCollisionState, const bool collisionState, BaseCollider* pCollider)
{
	// Check collision states
	if (!prevCollisionState && collisionState)
	{
		m_pGameObject->OnCollisionEnter(pCollider);
	}
	else if (prevCollisionState && collisionState)
	{
		m_pGameObject->OnCollisionStay(pCollider);
	}
	else if (prevCollisionState && !collisionState)
	{
		m_pGameObject->OnCollisionExit(pCollider);
	}

	if (!prevTriggerState && triggerState)
	{
		m_pGameObject->OnTriggerEnter(pCollider);
	}
	else if (prevTriggerState && triggerState)
	{
		m_pGameObject->OnTriggerStay(pCollider);
	}
	else if (prevTriggerState && !triggerState)
	{
		m_pGameObject->OnTriggerExit(pCollider);
	}
}
