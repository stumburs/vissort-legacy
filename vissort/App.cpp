#include "App.h"
#include <raylib.h>

App::App() : gui(sorter, data_generator) {}

void App::Run()
{
	while (!WindowShouldClose())
	{
		// Drawing
		gui.Render();
	}
	CloseWindow();
}
