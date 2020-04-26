#pragma once
#include "BaseComponent.h"

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

		// Editor GUI
		void DrawGUI() override;
		const std::string& GetID() const override;

	private:
		Transform* m_pTransform;
		GameObject* m_pGameObject;
		std::string m_ID;
		std::string m_TextureName;
	};
}
