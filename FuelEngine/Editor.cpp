#include "FuelEnginePCH.h"
#include "Editor.h"
#include "Logger.h"
#include "SceneManager.h"
#include "EngineSettings.h"

fuel::Editor::Editor()
{
}

fuel::Editor::~Editor()
{
}

void fuel::Editor::IInitialze()
{
	
}

void fuel::Editor::IDrawEditor()
{
	CreateDockingSpaces();
	DrawConsole();
	DrawHierarchy();
	DrawInspector();
}

void fuel::Editor::CreateDockingSpaces()
{
	const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
	const ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

	// Left Dock ------------------------------------------------
	const Vector2 leftDockPos{ static_cast<float>(EngineSettings::GetGameWidth()), 0 };
	const Vector2 leftDockSize{ 450, static_cast<float>(EngineSettings::GetWindowHeight()) };
	
	ImGui::SetNextWindowPos({ leftDockPos.x, leftDockPos.y }, ImGuiCond_Always);
	ImGui::SetNextWindowSize({ leftDockSize.x, leftDockSize.y }, ImGuiCond_Always);

	ImGui::Begin("##DOCKLEFT", nullptr, windowFlags);

	const ImGuiID leftDockSpace = ImGui::GetID("LeftDockSpace");
	ImGui::DockSpace(leftDockSpace, {}, dockSpaceFlags);

	ImGui::End();
	// ----------------------------------------------------------

	// Right Dock -----------------------------------------------
	const Vector2 rightDockPos{ static_cast<float>(EngineSettings::GetGameWidth()) + leftDockSize.x, 0 };
	const Vector2 rightDockSize{ leftDockSize };
	
	ImGui::SetNextWindowPos({ rightDockPos.x, rightDockPos.y }, ImGuiCond_Always);
	ImGui::SetNextWindowSize({ rightDockSize.x, rightDockSize.y }, ImGuiCond_Always);

	ImGui::Begin("##DOCKRIGHT", nullptr, windowFlags);

	const ImGuiID rightDockSpace = ImGui::GetID("RightDockSpace");
	ImGui::DockSpace(rightDockSpace, {}, dockSpaceFlags);

	ImGui::End();
	// -----------------------------------------------------------

	// Bottom Dock -----------------------------------------------
	const Vector2 dockBottomPos{ 0, static_cast<float>(EngineSettings::GetGameHeight()) };
	const Vector2 dockBottomSize{ static_cast<float>(EngineSettings::GetGameWidth()), static_cast<float>(EngineSettings::GetWindowHeight() - EngineSettings::GetGameHeight()) };
	ImGui::SetNextWindowPos({dockBottomPos.x, dockBottomPos.y }, ImGuiCond_Always);
	ImGui::SetNextWindowSize({ dockBottomSize.x, dockBottomSize.y }, ImGuiCond_Always);

	ImGui::Begin("##DOCKBOTTOM", nullptr, windowFlags);

	const ImGuiID bottomDockSpace = ImGui::GetID("BottomDockSpace");
	ImGui::DockSpace(bottomDockSpace, {}, dockSpaceFlags);

	ImGui::End();
	// -----------------------------------------------------------

	ImGui::Begin("Test Window 1");
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "This is colored text");
	ImGui::Text("This is window 1.");
	ImGui::End();

	ImGui::Begin("Test Window 2");
	ImGui::Text("This is window 2.");
	ImGui::End();

	ImGui::Begin("Test Window 3");
	ImGui::Text("This is window 3.");
	ImGui::End();
}

void fuel::Editor::DrawConsole()
{
	Logger::Draw();
}

void fuel::Editor::DrawHierarchy()
{
	ImGui::Begin("Hierarchy");
	SceneManager::DrawGameObjects();
	ImGui::End();
}

void fuel::Editor::DrawInspector()
{
	ImGui::Begin("Inspector");
	SceneManager::DrawComponents();
	ImGui::End();
}
