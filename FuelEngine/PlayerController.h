#pragma once
#include "BaseComponent.h"

namespace fuel
{
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

		// Controls
		void Jump();
		void Fire();
		void Duck();
		void Fart();

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
		PlayerID m_PlayerID;
		std::string m_ID;
	};
}
