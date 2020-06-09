#pragma once
#include "BaseComponent.h"


namespace fuel
{
	enum class PlayerID;
	class VibrationComponent : public BaseComponent
	{
	public:
		VibrationComponent() = default;
		virtual ~VibrationComponent() = default;

		VibrationComponent(const VibrationComponent& other) = delete;
		VibrationComponent(VibrationComponent&& other) = delete;
		VibrationComponent& operator=(const VibrationComponent& other) = delete;
		VibrationComponent& operator=(VibrationComponent&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(fuel::GameObject* parent) override;
		fuel::GameObject* GetGameObject() const override;

		size_t GetType() override;

		void Play();
		void Stop();
		void SetLeftVibration(float vibration);
		void SetRightVibration(float vibration);
		void SetDuration(float durationSec);
		void SetPlayerID(PlayerID playerID);

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
		float m_LeftVibration{};
		float m_RightVibration{};
		float m_Duration{};
		float m_CurrentDuration{};
		bool m_CanPlay{};

		GameObject* m_Gameobject{};
		PlayerID m_PlayerID{};
		std::string m_ID{};
	};
}

