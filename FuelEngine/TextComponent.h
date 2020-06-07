#pragma once
#include "Transform.h"

namespace fuel
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent();
		virtual ~TextComponent() = default;

		void Initialize() override;
		void OnStart() override;
		
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetPosition(float x, float y) const;
		void SetSize(unsigned int fontSize);
		void SetColor(const Color4& color);
		void SetColor(const float r, const float g, const float b, const float a);

		void SetGameObject(GameObject* parent) override;
		GameObject* GetGameObject() const override;

		size_t GetType() override;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

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
		bool m_NeedsUpdate;
		std::string m_Text;
		Color4 m_Color;
		std::shared_ptr<Font> m_Font;
		std::string m_FontName;
		int m_FontSize;
		std::shared_ptr<Texture2D> m_Texture;
		Transform* m_pTransform;
		GameObject* m_pGameObject;
		std::string m_ID;
	};
}
