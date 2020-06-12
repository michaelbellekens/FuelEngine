#pragma once
#include <map>

#include "BaseComponent.h"
#include "BaseCollider.h"
#include "GameObject.h"

#include "Logger.h"

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

		bool GetIsFacingLeft() const;
		
		void AddForce(const Vector2& force, bool impulse = false);
		void SetForce(const Vector2& force);

		void SetDrag(float drag);
		
		void SetIsKinematic(bool isKinematic);
		bool GetIsKinematic() const;

		void SetMass(float mass);
		float GetMass() const;

		void UseGravity(bool useGravity);
		void SetGravity(const Vector2& gravity);
		Vector2 GetGravity() const;

		void SetBounciness(const float bounciness);
		
		void AddCollider(BaseCollider* collider);

		bool IsGrounded();

		// Loading and Saving
		ComponentType GetCompType() const override;
		void Safe(std::ofstream& binStream) const override;
		void Load(std::ifstream& binStream) override;

		//Physics
		void OnCollisionEnter(BaseCollider* other) override;
		void OnCollisionStay(BaseCollider* other) override;
		void OnCollisionExit(BaseCollider* other) override;

		void OnTriggerEnter(BaseCollider* other) override;
		void OnTriggerStay(BaseCollider* other) override;
		void OnTriggerExit(BaseCollider* other) override;
		
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
		Vector2 m_InputVelocity{};
		Vector2 m_Acceleration{};
		Vector2 m_Force{};
		float m_Mass{ 1.f };
		float m_Drag{ 2.f };
		Vector2 m_Gravity{ 0.f, 9.81f };
		float m_Bounciness{ 0.5f };
		
		bool m_IsKinematic{ false };
		bool m_UseGravity{ true };
		bool m_IsFacingLeft{ false };
		/**
		 * \brief Holds Collider ID as key and pair as value in format [isColliding, isInTrigger]
		 */
		std::map<std::string, std::pair<bool, bool>> m_RegisteredCollisions{};

		bool IsCollidingAfterMove();
		void CheckCollision();
		void CheckBoxCollision(BaseCollider* sceneCollider);
		void CheckSphereCollision(BaseCollider* sceneCollider);
		void SetVelocityAfterCollision(BaseCollider* ownCollider, BaseCollider* sceneCollider);

		void HandlePhysicsEvents(const bool prevTriggerState, const bool triggerState, const bool prevCollisionState, const bool collisionState, BaseCollider* pCollider);
	};
}
