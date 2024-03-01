#pragma once
#include <vector>
#include "Element.h"
#include "Sorter.h"
#include "Generators.h"

class GUI
{
public:
	GUI(Sorter& sorter, Generators& generators);
	void Render();
private:
	Sorter& sorter;
	Generators& generators;

	void DrawData(const std::vector<Element>& vec);
	void DrawMenu();
	std::string GenerateSortingAlgorithmDropdownOptions();
	std::string GenerateGeneratorDropdownOptions();

	bool settings_open = false;
	bool shuffle_dropdown_edit = false;
	int shuffle_selected = 0;
	bool sorting_dropdown_edit = false;
	int sorting_selected = 0;
	int new_vec_size = 100;
	double new_sorting_delay = 0.001;
};

