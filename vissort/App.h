#pragma once
#include "GUI.h"
#include "Sorter.h"
#include "DataGenerator.h"
#include <vector>

class App
{
public:
	App();
	void Run();

private:
	DataGenerator data_generator;
	Sorter sorter;
	GUI gui;
};

