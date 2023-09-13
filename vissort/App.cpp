#include "App.h"
#include <raylib.h>

App::App() : sorter(data_generator), gui(sorter, data_generator) {}

void App::Run()
{
	while (!WindowShouldClose())
	{
		gui.Render();
	}
	CloseWindow();
}
