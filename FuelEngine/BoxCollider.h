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

		bool IsTrigger() const override;
		void SetIsTrigger(const bool isTrigger) override;
		bool IsColliding(const Rectf& dimensions) const override;
		bool IsColliding(const Spheref& sphere) const override;
		bool IsColliding(const Vector2& point) const override;

		Rectf GetDimensions() const;
		void SetDimensions(const Rectf& shape);

		ShapeType GetShapeType() const override;

		// Editor GUI
		void DrawGUI() override;
		const std::string& GetID() const override;

	private:
		GameObject* m_pGameObject{ nullptr };
		Transform* m_pTransform{ nullptr };
		std::string m_ID = "";

		Rectf m_Dimensions{ 0.f, 0.f, 50.f, 50.f };
		bool m_IsTrigger{ false };

		bool IsPointInSphere(const Spheref& sphere, const Vector2& point) const;
	};
}
