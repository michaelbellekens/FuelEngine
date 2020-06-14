#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace fuel
{
	class RigidBody2D;
	class RenderComponent;
	class BubbleComponent : public BaseComponent
	{
	public:
		BubbleComponent() ;
		~BubbleComponent() = default;

		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;

		void Initialize() override;
		void OnStart() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		void SetOwner(PlayerID owner);
		void SetScoreReferences(int* score1, int* score2);

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
		void AddScore(int score);
		
		GameObject* m_pGameObject{ nullptr };
		std::string m_ID{};
		RigidBody2D* m_pRigidBody{ nullptr };
		RenderComponent* m_pRenderComp{ nullptr };
		PlayerID m_Owner{ PlayerID::PlayerOne };
		bool m_CapturedEnemy{ false };
		int* m_ScorePlayer1;
		int* m_ScorePlayer2;
	};
}
