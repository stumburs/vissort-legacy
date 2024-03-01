#pragma once
#include "GUI.h"
#include "Sorter.h"
#include "DataGenerator.h"
#include <vector>
#include "Generators.h"

class App
{
public:
	App();
	void Run();

private:
	// DataGenerator data_generator;
	Generators generators;
	Sorter sorter;
	GUI gui;
};

