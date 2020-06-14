#pragma once
#include "GameObject.h"

namespace fuel
{
	class RigidBody2D;
	class RenderComponent;
	class Bubble : public fuel::GameObject
	{
	public:
		Bubble();
		virtual ~Bubble() = default;
		Bubble(const Bubble& other) = delete;
		Bubble(Bubble&& other) = delete;
		Bubble& operator=(const Bubble& other) = delete;
		Bubble& operator=(Bubble&& other) = delete;

		void Initialize() override;
		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void AttachScene(fuel::Scene * scene) override;

		void SetName(const std::string & name) override;
		std::string& GetName() override;

		// Bubble functions
		void SetSpawnPosition(const Vector2& position);
		void SetDirection(const Vector2& direction);

		// Saving and Loading
		fuel::ObjectType GetObjectType() const override;

		// Physics
		void OnCollisionEnter(BaseCollider * other) override;
		void OnCollisionStay(BaseCollider * other) override;
		void OnCollisionExit(BaseCollider * other) override;

		void OnTriggerEnter(BaseCollider * other) override;
		void OnTriggerStay(BaseCollider * other) override;
		void OnTriggerExit(BaseCollider * other) override;

		// Editor GUI
		void DrawComponents() override;

	private:
		RigidBody2D* m_pRigidBody;
		RenderComponent* m_pSpriteRenderer;
		bool m_CapturedEnemy;

		static int m_Count;
	};
}	
