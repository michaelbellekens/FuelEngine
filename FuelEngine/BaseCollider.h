#pragma once
#include "BaseComponent.h"

namespace fuel
{
	enum class ShapeType
	{
		Rect,
		Sphere
	};
	
	class BaseCollider : public BaseComponent
	{
	public:
		BaseCollider() = default;
		virtual ~BaseCollider() = default;

		BaseCollider(const BaseCollider& other) = delete;
		BaseCollider(BaseCollider&& other) = delete;
		BaseCollider& operator=(const BaseCollider& other) = delete;
		BaseCollider& operator=(BaseCollider&& other) = delete;

		virtual void Initialize() = 0;
		virtual void OnStart() = 0;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		virtual void SetGameObject(GameObject* parent) = 0;
		virtual GameObject* GetGameObject() const = 0;

		virtual size_t GetType() = 0;
		//virtual void SetEnabled(bool isEnabled) = 0;
		//virtual bool IsEnabled() const = 0;

		//virtual void BroadcastMessage() = 0;
		//virtual void ReceiveMessage(int message) = 0;

		virtual Vector2 GetPosition() = 0;
		
		virtual bool IsTrigger() const = 0;
		virtual void SetIsTrigger(const bool isTrigger) = 0;

		virtual bool IsColliding(const Rectf& dimensions) const = 0;
		virtual bool IsColliding(const Spheref& sphere) const = 0;
		virtual bool IsColliding(const Vector2& point) const = 0;

		virtual bool CanPassFromBellow() const = 0;
		virtual void SetCanPassFromBellow(const bool canPass) = 0;

		//virtual Shape GetDimensions() const = 0;
		virtual ShapeType GetShapeType() const = 0;
		virtual Vector2 GetMidPoint() const = 0;

		// Editor GUI
		virtual void DrawGUI() = 0;
		virtual const std::string& GetID() const = 0;

	};
}
