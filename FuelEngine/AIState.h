#pragma once
#include "RigidBody2D.h"

namespace fuel
{
	class GameObject;
	class AIState
	{
	public:
		AIState() = default;
		virtual ~AIState() = default;

		AIState(const AIState& other) = delete;
		AIState(AIState&& other) = delete;
		AIState& operator=(const AIState& other) = delete;
		AIState& operator=(AIState&& other) = delete;

		virtual void Enter(GameObject* actor) = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void TriggerPhysicsEvent(const PhysicsEvent& physicsEvent) = 0;
		virtual size_t GetID() const = 0;
	};
}
