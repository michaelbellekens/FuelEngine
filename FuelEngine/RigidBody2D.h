#pragma once
#include "BaseComponent.h"
#include "BaseCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"

#include "Logger.h"
#include <type_traits>

namespace fuel
{
	class Transform;
	class RigidBody2D final : public BaseComponent
	{
	public:
		RigidBody2D() = default;
		virtual ~RigidBody2D() = default;
		RigidBody2D(const RigidBody2D& other) = delete;
		RigidBody2D(RigidBody2D&& other) = delete;
		RigidBody2D& operator=(const RigidBody2D& other) = delete;
		RigidBody2D& operator=(RigidBody2D&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		// RigidBody Specific functions
		void MovePosition(const Vector3& pos);
		Vector3 GetPosition() const;

		void AddForce(const Vector2& force);
		void SetForce(const Vector2& force);

		void SetDrag(float drag);
		
		void SetIsKinematic(bool isKinematic);
		bool GetIsKinematic() const;

		void SetMass(float mass);
		float GetMass() const;

		void UseGravity(bool useGravity);
		void SetGravity(const Vector2& gravity);
		Vector2 GetGravity() const;

		void AddCollider(BaseCollider* collider);
		
		// Editor GUI
		
		void DrawGUI() override;
		const std::string& GetID() const override;

	private:
		Transform* m_pTransform{ nullptr };
		GameObject* m_pGameObject{ nullptr };
		std::string m_ID{ };

		std::vector<BaseCollider*> m_pColliders{};
		Vector3 m_Position{};
		Vector2 m_Velocity{};
		Vector2 m_Acceleration{};
		Vector2 m_Force{};
		float m_Mass{ 1.f };
		float m_Drag{ 0.f };
		Vector2 m_Gravity{ 0.f, 0.1f };
		
		bool m_IsKinematic{ false };
		bool m_UseGravity{ true };

		void CheckCollision();
		void CheckBoxCollision(BaseCollider* sceneCollider);
		void CheckSphereCollision(BaseCollider* sceneCollider);
		//template<typename T>
		//void CheckCollisionWithShape(BaseCollider* sceneCollider);
	};
	
	/*template<typename T>
	inline void RigidBody2D::CheckCollisionWithShape(BaseCollider* sceneCollider)
	{
		if (!std::is_base_of<BaseCollider, T>::value)
		{
			const std::string errorLog{ "Tried to check collision with unvalid class of type: " };
			Logger::LogError(errorLog + typeid(T).name());
			return;
		}

		T* other{ static_cast<T*>(sceneCollider) };
		for (BaseCollider* ownedCollider : m_pColliders)
		{
			if (ownedCollider->IsColliding(other->GetDimensions()))
			{
				Logger::LogWarning(other->GetGameObject()->GetName() + " is overlapping with rigidbody: " + m_pGameObject->GetName());
				m_Position -= m_Velocity;
				m_Velocity = Vector2();
			}
		}
	}*/
}
