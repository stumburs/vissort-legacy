#pragma once
#include "Element.h"
#include <vector>
#include <string>

class Sorter
{
public:
	Sorter();
	void InitVector(int size);
	std::vector<Element>& GetData();

	// Sorting algorithms
	void BubbleSort();
	void ShellSort();
	void CocktailSort();
	void GnomeSort();
	void CycleSort();

	enum SortingAlgorithms
	{
		BubbleSortEnum = 0,
		QuickSortEnum,
		CombSortEnum,
		ShellSortEnum,
		CocktailSortEnum,
		GnomeSortEnum,
		CycleSortEnum
	};

	void SetActiveAlgorithm(SortingAlgorithms active_algorithm);
	std::string SortingEnumToString();

private:
	std::vector<Element> data;
	SortingAlgorithms active_algorithm = SortingAlgorithms::BubbleSortEnum;
};

