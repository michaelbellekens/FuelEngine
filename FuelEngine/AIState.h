#pragma once

namespace fuel
{
	class AIState
	{
	public:
		AIState() = default;
		virtual ~AIState() = default;

		AIState(const AIState& other) = delete;
		AIState(AIState&& other) = delete;
		AIState& operator=(const AIState& other) = delete;
		AIState& operator=(AIState&& other) = delete;

		virtual void Enter() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
	};
}
