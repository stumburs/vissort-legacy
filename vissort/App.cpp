#include "App.h"
#include <raylib.h>

App::App() : sorter(), gui(sorter, generators) {}

void App::Run()
{
	while (!WindowShouldClose())
	{
		gui.Render();
	}
	CloseWindow();
}
