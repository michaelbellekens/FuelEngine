#pragma once
#include "BaseComponent.h"

namespace fuel
{
	class BubbleComponent;

	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent();
		~HealthComponent() = default;

		HealthComponent(const BubbleComponent& other) = delete;
		HealthComponent(BubbleComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		void Damage();
		int GetNumberOfLives() const;
		void SetNUmberOfLives(const int lives);
		
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
		GameObject* m_pGameObject{ nullptr };
		std::string m_ID{};

		int m_Lives{ 4 };
	};
}