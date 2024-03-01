#pragma once
#include "GUI.h"
#include "Sorter.h"
#include "Generators.h"

class App
{
public:
	App();
	void Run();

private:
	Generators generators;
	Sorter sorter;
	GUI gui;
};

