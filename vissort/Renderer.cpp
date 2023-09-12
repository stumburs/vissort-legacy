#include "Renderer.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <thread>
#include <iostream>

Renderer::Renderer(Sorter& sorter, DataGenerator& data_generator) : sorter(sorter), data_generator(data_generator)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "vissort");
	SetWindowSize(GetMonitorWidth(0) / 2, GetMonitorHeight(0) / 2);
	SetTargetFPS(60);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

	// Background
	GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt({ 76, 82, 99, 255 }));
	GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt({ 92, 99, 112, 255 }));
	GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt({ 108, 116, 125, 255 }));
	GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt({ 76, 82, 99, 255 }));

	// Text
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
	GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 229, 192, 123, 255 }));
	GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt({ 229, 192, 123, 255 }));

	// Border
	GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
	GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 209, 154, 102, 255 }));
	GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt({ 209, 154, 102, 255 }));
}

void Renderer::Render()
{
	// Draw
	BeginDrawing();
	{
		ClearBackground({ 40, 44, 52, 255 });

		DrawData(sorter.GetData());

		if (GuiButton({ 20, 20, 40, 40 }, ""))
			settings_open = !settings_open;
		if (CheckCollisionPointRec(GetMousePosition(), { 20, 20, 40, 40 }))
			GuiDrawIcon(GuiIconName::ICON_GEAR, 24, 24, 2, { 229, 192, 123, 255 });
		else
			GuiDrawIcon(GuiIconName::ICON_GEAR, 24, 24, 2, { 171, 178, 191, 255 });

		if (settings_open)
		{
			if (!dropdown_edit_mode)
			{
				std::string sorting_text = sorter.GetSortingActive() ? "Stop" : "Start";
				if (sorter.GetSortingActive())
				{
					GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 224, 108, 117, 255 }));
					GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 224, 108, 117, 255 }));
					GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 190, 80, 70, 255 }));
					GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 190, 80, 70, 255 }));
				}
				if (GuiButton({ 20, 120, 120, 40 }, sorting_text.c_str()))
				{
					if (!sorter.GetSortingActive())
					{
						sorter.StartThread();
						std::cout << "Thread started!\n";
					}
				}
				GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
				GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 229, 192, 123, 255 }));
				GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
				GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 209, 154, 102, 255 }));

				if (GuiButton({ 20, 270, 120, 40 }, "Apply") && !sorter.GetSortingActive())
					sorter.InitVector(new_vec_size);

				if (GuiButton({ 20, 170, 120, 40 }, "Randomize") && !sorter.GetSortingActive())
					data_generator.Randomize(sorter.GetData());

				new_vec_size = (int)GuiSlider({ 20, 220, 200, 40 }, "", TextFormat("%d", new_vec_size), new_vec_size, 4, GetScreenWidth());
			}

			if (GuiDropdownBox({ 20, 70, 200, 40 }, "Bubble Sort;Quick Sort;Comb Sort;Shell Sort;Cocktail Sort;Gnome Sort;Cycle Sort", &active, dropdown_edit_mode))
			{
				dropdown_edit_mode = !dropdown_edit_mode;
				sorter.SetActiveAlgorithm(Sorter::SortingAlgorithms(active));
			}
		}

	}
	EndDrawing();
}

void Renderer::DrawData(const std::vector<Element>& vec)
{
	// Find largest element in vec
	int max = vec.begin()->value;
	for (const auto& elem : vec)
	{
		if (elem.value > max)
			max = elem.value;
	}

	float scale_x = GetScreenWidth() / (float)vec.size();
	float scale_y = GetScreenHeight() / (float)max;
	for (int i = 0; i < vec.size(); i++)
	{
		DrawRectangle(
			scale_x * i,
			GetScreenHeight() - vec[i].value * scale_y,
			ceilf(scale_x),
			vec[i].value * scale_y + 1,
			vec[i].color
		);
	}
}
