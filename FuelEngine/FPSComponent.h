#pragma once
#include "BaseComponent.h"

namespace fuel
{
	class TextComponent;
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent() = default;

		void Initialize() override;
		void OnStart() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

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
		// Component links
		TextComponent* m_pFPSCounter{ nullptr };
		GameObject* m_pGameObject{ nullptr };

		std::string m_fpsLabel{ "FPS: " };
		float m_UpdateInterval{ 0.5f };
		float m_UpdateTime{ 0 };
		int m_RenderedFrames{ 0 };
		int m_CurrentFrame{ 0 };
		std::string m_ID{};
	};
}
