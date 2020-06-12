#pragma once
#include "Font.h"
#include "SceneObject.h"

namespace fuel
{
	enum ButtonAction
	{
		OnePlayer,
		COOP,
		VS,
		QUIT
	};
	
	class Texture2D;
	class BaseComponent;
	class RenderComponent;
	class TextComponent;
	class Transform;
	class Button : public SceneObject
	{
	public:
		Button();
		virtual ~Button();
		Button(const Button& other) = delete;
		Button(Button&& other) = delete;
		Button& operator=(const Button& other) = delete;
		Button& operator=(Button&& other) = delete;

		void Initialize() override;
		void Start() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void AttachScene(Scene* scene) override;
		Scene* GetScene() const;

		Transform* GetTransform() const;

		void SetName(const std::string& name) override;
		std::string& GetName() override;

		void SetTag(const std::string& tagName);
		std::string GetTag() const;
		bool CompareTag(const std::string& tagName) const;

		void SetActive(const bool isActive);
		bool GetIsActive() const;
		bool GetIsTriggered() const;

		// Saving and Loading
		ObjectType GetObjectType() const override;
		void Safe(std::ofstream& binStream) const;
		void Load(std::ifstream& binStream);

		// Button specific
		void ExecuteButtonAction() const;
		
		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetFontSize(const int size);
		void SetTextOffset(const Vector2& offset);
		void SetTexture(const std::string fileName);

		void SetSelected(bool isSelected);
		void SetButtonID(const int id);
		int GetButtonID() const;
		bool IsSelected() const;
		void SetButtonAction(const ButtonAction action);

		// Editor GUI
		void DrawComponents() override;

	private:
		std::string m_Name;
		std::string m_Tag;
		Transform* m_pTransform;
		RenderComponent* m_pRenderComponent;
		TextComponent* m_pTextComponent;
		Scene* m_pLinkedScene;
		bool m_IsActive;
		bool m_IsTriggered;

		int m_ButtonID;
		bool m_IsSelected;
		ButtonAction m_ButtonAction;
	};
}
