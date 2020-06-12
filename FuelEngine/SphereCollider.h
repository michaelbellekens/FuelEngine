#pragma once
#include "BaseCollider.h"
#include "Transform.h"

namespace fuel
{
	class Transform;
	class SphereCollider final : public BaseCollider
	{
	public:
		SphereCollider() = default;
		virtual ~SphereCollider() = default;
		SphereCollider(const SphereCollider& other) = delete;
		SphereCollider(SphereCollider&& other) = delete;
		SphereCollider& operator=(const SphereCollider& other) = delete;
		SphereCollider& operator=(SphereCollider&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject * parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;
		Vector2 GetPosition() override;

		bool IsTrigger() const override;
		void SetIsTrigger(const bool isTrigger) override;
		bool IsColliding(const Spheref& shape) const override;
		bool IsColliding(const Rectf & rect) const override;
		bool IsColliding(const Vector2 & point) const override;

		Spheref GetDimensions() const;
		void SetDimensions(const Spheref& shape);
		void SetRadius(const float radius);

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

		Spheref m_Dimensions{ 0.f, 0.f , 10 };
		bool m_IsTrigger{ false };
		bool m_CanPassFromBellow{ false };
	};
}
