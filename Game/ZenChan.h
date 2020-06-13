#pragma once
#include "GameObject.h"

namespace fuel
{
	class RigidBody2D;
	class SpriteComponent;
	class AIController;
	class ZenChan : public fuel::GameObject
	{
	public:
		ZenChan();
		virtual ~ZenChan() = default;
		ZenChan(const ZenChan& other) = delete;
		ZenChan(ZenChan&& other) = delete;
		ZenChan& operator=(const ZenChan& other) = delete;
		ZenChan& operator=(ZenChan&& other) = delete;

		void Initialize() override;
		void Start() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void AttachScene(fuel::Scene* scene) override;

		void SetName(const std::string& name) override;
		std::string& GetName() override;

		void SetPlayer1(GameObject* pPlayer1);
		void SetPlayer2(GameObject* pPlayer2);

		// Saving and Loading
		fuel::ObjectType GetObjectType() const override;

		// Physics
		void OnCollisionEnter(BaseCollider* other) override;
		void OnCollisionStay(BaseCollider* other) override;
		void OnCollisionExit(BaseCollider* other) override;

		void OnTriggerEnter(BaseCollider* other) override;
		void OnTriggerStay(BaseCollider* other) override;
		void OnTriggerExit(BaseCollider* other) override;
		
		// Editor GUI
		void DrawComponents() override;

	private:
		RigidBody2D* m_pRigidBody;
		SpriteComponent* m_pSpriteRenderer;
		AIController* m_pAIController;

		GameObject* m_pPlayer1{ nullptr };
		GameObject* m_pPlayer2{ nullptr };
	};
}
