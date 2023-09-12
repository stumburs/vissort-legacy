#pragma once
#include "GUI.h"
#include "Sorter.h"
#include "Element.h"
#include "DataGenerator.h"
#include <vector>

class App
{
public:
	App();
	void Run();

private:
	Sorter sorter;
	DataGenerator data_generator;
	GUI gui;
};

