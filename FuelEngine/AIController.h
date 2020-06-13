#pragma once
#include "BaseComponent.h"

namespace fuel
{
	class Transform;
	class AIController final : public BaseComponent
	{
	public:
		AIController() = default;
		virtual ~AIController() = default;
		AIController(const AIController& other) = delete;
		AIController(AIController&& other) = delete;
		AIController& operator=(const AIController& other) = delete;
		AIController& operator=(AIController&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

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
		Transform* m_pTransform{ nullptr };
		GameObject* m_pGameObject{ nullptr };
		std::string m_ID{ };

		
	};
}
