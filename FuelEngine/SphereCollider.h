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

		bool IsTrigger() const override;
		void SetIsTrigger(const bool isTrigger) override;
		bool IsColliding(const Spheref& shape) const override;
		bool IsColliding(const Rectf & rect) const override;
		bool IsColliding(const Vector2 & point) const override;

		Spheref GetDimensions() const;
		void SetDimensions(const Spheref& shape);
		void SetRadius(const float radius);

		ShapeType GetShapeType() const override;

		// Editor GUI
		void DrawGUI() override;
		const std::string& GetID() const override;

	private:
		GameObject* m_pGameObject{ nullptr };
		Transform* m_pTransform{ nullptr };
		std::string m_ID = "";

		Spheref m_Dimensions{ 0.f, 0.f , 10 };
		bool m_IsTrigger{ false };
	};
}
