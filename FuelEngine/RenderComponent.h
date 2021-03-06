#pragma once
#include "BaseComponent.h"

namespace fuel
{
	class Texture2D;
	class Transform;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Initialize() override;
		void OnStart() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		void SetTransform(Transform* transComp);

		size_t GetType() override;
		
		void SetTexture(const std::string& filename);

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
		std::shared_ptr<Texture2D> m_Texture;
		Transform* m_pTransform;
		GameObject* m_pGameObject;
		std::string m_ID;
		std::string m_TextureName;
	};
}
