#pragma once
#include <map>

#include "BaseComponent.h"

namespace fuel
{
	class Texture2D;
	class Transform;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent();
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Initialize() override;
		void OnStart() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		void SetAnimation(const int animID);
		void SetColumns(const int col);
		void SetRows(const int row);
		void SetTexture(const std::string& filename);
		void AddAnimation(const int animID, const int numFrames);
		void SetAnimTime(const float animTime);
		void SetScale(const float x, const float y);
		void SetDirectionIDs(int leftDirID, int rightDirID);
		void LookLeft(const bool lookLeft);

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
		std::map<int, int> m_AnimationLoops;
		int m_Cols;
		int m_Rows;
		int m_CurrentAnimFrame;
		int m_CurrentAnimation;
		float m_AnimTime;
		float m_CurrentAnimTime;
		Vector2 m_Scale;
		int m_LookLeftID;
		int m_LookRightID;
	};
}