#pragma once
#include "BaseComponent.h"

namespace fuel
{
	class RigidBody2D;
	class SpriteComponent;
	
	enum class PlayerID;
	class PlayerController : public BaseComponent
	{
	public:
		PlayerController();
		~PlayerController() = default;

		PlayerController(const PlayerController& other) = delete;
		PlayerController(PlayerController&& other) = delete;
		PlayerController& operator=(const PlayerController& other) = delete;
		PlayerController& operator=(PlayerController&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		void SetPlayerID(const PlayerID id);
		PlayerID GetPlayerID() const;

		void SetIsInMenu(const bool inMenu);
		
		// Controls
		void Jump();
		void Fire();
		void Duck();
		void Fart();

		// UI Controls
		void MoveUpUI();
		void MoveDownUI();
		void ClickUI();

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
		void ChangePlayerID(const std::string& playerID);
		
	private:
		GameObject* m_pGameObject;
		RigidBody2D* m_pRigidBody;
		SpriteComponent* m_pSpriteRenderer;
		PlayerID m_PlayerID;
		std::string m_ID;
		bool m_IsInMenu;
		bool m_IsGrounded;
	};
}
