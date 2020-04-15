#pragma once
namespace fuel
{
	class Scene;
	class SceneObject
	{
	public:
		virtual void Initialize() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		virtual void AttachScene(Scene* scene) = 0;

		virtual void SetName(const std::string& name) = 0;
		virtual std::string& GetName() = 0;

		// Editor GUI
		virtual void DrawComponents() = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
