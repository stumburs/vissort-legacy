#include "App.h"
#include <raylib.h>

App::App() : renderer(sorter, data_generator) {}

void App::Run()
{
	while (!WindowShouldClose())
	{
		// Logic
		
		// Drawing
		renderer.Render();
	}
	CloseWindow();
}
