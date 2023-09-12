#pragma once
#include <vector>
#include "Element.h"
#include "Sorter.h"
#include "DataGenerator.h"

class GUI
{
public:
	GUI(Sorter& sorter, DataGenerator& data_generator);
	void Render();
private:
	Sorter& sorter;
	DataGenerator& data_generator;

	void DrawData(const std::vector<Element>& vec);
	void DrawMenu();
	std::string GenerateDropdownOptions();

	bool settings_open = false;
	int active = 0;
	bool dropdown_edit_mode = false;
	int new_vec_size = 100;
};

