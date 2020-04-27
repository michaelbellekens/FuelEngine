#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "BaseComponent.h"
	
namespace fuel
{
	class Transform : public BaseComponent
	{
	public:
		Transform();
		~Transform();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void OnStart() override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;
		
		const Vector3& GetPosition() const;
		void SetPosition(const float x, const float y);
		void SetPosition(const float x, const float y, const float z);
		void SetPosition(const Vector3& newPosition);
		void SetPosition(const Vector2& newPosition);

		// Editor GUI
		void DrawGUI() override;
		const std::string& GetID() const override;
		
	private:
		GameObject* m_pGameObject;
		Vector3 m_Position;
		std::string m_ID;
	};

	
}
