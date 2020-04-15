#pragma once
#include "Singleton.h"

namespace fuel
{
	class Editor : public Singleton<Editor>
	{
	public:
		Editor();
		virtual ~Editor();
		
		Editor(const Editor& other) = delete;
		Editor(Editor&& other) = delete;
		Editor& operator=(const Editor& other) = delete;
		Editor& operator=(Editor&& other) = delete;

		static void Initialize() { GetInstance().IInitialze(); }
		static void DrawEditor() { GetInstance().IDrawEditor(); }

	private:
		void IInitialze();
		
		void IDrawEditor();
		void CreateDockingSpaces();
		void DrawConsole();
		void DrawHierarchy();
		void DrawInspector();
	};
}
