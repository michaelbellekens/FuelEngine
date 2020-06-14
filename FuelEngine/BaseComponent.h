#pragma once

namespace fuel
{
	enum class ComponentType
	{
		FPS,
		TRANSFORM,
		RIGIDBODY,
		BOXCOLLIDER,
		SPHERECOLLIDER,
		TEXTRENDERER,
		RENDERER,
		SPRITERENDERER,
		CONTROLLER,
		VIBRATION,
		AICONTROLLER,
		BUBBLE,
		HEALTH
	};
	
	class BaseCollider;
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

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

		// Loading and Saving
		virtual ComponentType GetCompType() const = 0;
		virtual void Safe(std::ofstream& binStream) const = 0;
		virtual void Load(std::ifstream& binStream) = 0;

		// Physics
		virtual void OnCollisionEnter(BaseCollider* other) = 0;
		virtual void OnCollisionStay(BaseCollider* other) = 0;
		virtual void OnCollisionExit(BaseCollider* other) = 0;

		virtual void OnTriggerEnter(BaseCollider* other) = 0;
		virtual void OnTriggerStay(BaseCollider* other) = 0;
		virtual void OnTriggerExit(BaseCollider* other) = 0;
		
		// Editor GUI
		virtual void DrawGUI() = 0;
		virtual const std::string& GetID() const = 0;
		
	};
}
