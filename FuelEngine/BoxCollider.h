#pragma once
#include "BaseCollider.h"

namespace fuel
{
	class Transform;
	class BoxCollider final : public BaseCollider
	{
	public:
		BoxCollider() = default;
		virtual ~BoxCollider() = default;
		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		Vector2 GetPosition() override;

		bool IsTrigger() const override;
		void SetIsTrigger(const bool isTrigger) override;
		bool IsColliding(const Rectf& dimensions) const override;
		bool IsColliding(const Spheref& sphere) const override;
		bool IsColliding(const Vector2& point) const override;

		Rectf GetDimensions() const;
		void SetDimensions(const Rectf& dimensions);

		ShapeType GetShapeType() const override;

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

		bool CanPassFromBellow() const override;
		void SetCanPassFromBellow(const bool canPass) override;

		Vector2 GetMidPoint() const override;

		// Editor GUI
		void DrawGUI() override;
		const std::string& GetID() const override;

	private:
		GameObject* m_pGameObject{ nullptr };
		Transform* m_pTransform{ nullptr };
		std::string m_ID = "";

		Rectf m_Dimensions{ 0.f, 0.f, 50.f, 50.f };
		bool m_IsTrigger{ false };
		bool m_CanPassFromBellow{ false };

		bool IsPointInSphere(const Spheref& sphere, const Vector2& point) const;
	};
}
