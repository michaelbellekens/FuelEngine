#include "FuelEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "FuelEngine.h"

int main(int, char*[]) {
	AllocConsole();
	fuel::FuelEngine engine;
	engine.Run();
    return 0;
}