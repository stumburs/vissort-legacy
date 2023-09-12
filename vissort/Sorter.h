#pragma once
#include "Element.h"
#include <vector>
#include <string>
#include <functional>

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
	int Partition(int low, int high);
	void QuickSort(int low, int high);
	int GetNextGap(int gap);
	void CombSort();

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

	SortingAlgorithms GetActiveAlgorithm();
	void SetActiveAlgorithm(SortingAlgorithms active_algorithm);
	std::string SortingEnumToString();
	bool GetSortingActive();
	void SetSortingActive(bool active);
	void StartThread();

private:
	std::vector<Element> data;
	SortingAlgorithms active_algorithm = SortingAlgorithms::BubbleSortEnum;
	bool sorting_active = false;
};

