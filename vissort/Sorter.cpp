#include "Sorter.h"
#include <thread>
#include <stdexcept>

Sorter::Sorter()
{
	InitVector(100);
}

void Sorter::InitVector(int size)
{
	data.clear();
	for (int i = 1; i < size + 1; i++)
	{
		Element elem{};
		elem.value = i;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}

std::vector<Element>& Sorter::GetData()
{
	return this->data;
}

// An optimized version of Bubble Sort
void Sorter::BubbleSort()
{
	int i, j;
	bool swapped;
	int n = data.size();
	for (i = 0; i < n - 1; i++)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (data[j].value > data[j + 1].value)
			{
				std::swap(data[j], data[j + 1]);
				WaitTime(0.0001);
				//return;
				swapped = true;
			}
		}

		// If no two elements were swapped by inner loop,
		// then break
		if (swapped == false)
			break;
	}
	sorting_active = false;
}

void Sorter::ShellSort()
{
	int n = data.size();
	// Start with a big gap, then reduce the gap
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is
		// gap sorted 
		for (int i = gap; i < n; i += 1)
		{
			// Stop execution if sorting stopped
			if (!sorting_active)
				return;

			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			Element temp = data[i];

			// shift earlier gap-sorted elements up until the correct 
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && data[j - gap].value > temp.value; j -= gap)
			{
				data[j] = data[j - gap];
				WaitTime(0.001);
			}

			//  put temp (the original a[i]) in its correct location
			data[j] = temp;
		}
	}
	 sorting_active = false;
}

// Cocktail sort
void Sorter::CocktailSort()
{
	int n = data.size();
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		// reset the swapped flag on entering
		// the loop, because it might be true from
		// a previous iteration.
		swapped = false;

		// loop from left to right same as
		// the bubble sort
		for (int i = start; i < end; ++i)
		{
			if (data[i].value > data[i + 1].value)
			{
				WaitTime(0.0001);
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}

		// if nothing moved, then array is sorted.
		if (!swapped)
			break;

		// otherwise, reset the swapped flag so that it
		// can be used in the next stage
		swapped = false;

		// move the end point back by one, because
		// item at the end is in its rightful spot
		--end;

		// from right to left, doing the
		// same comparison as in the previous stage
		for (int i = end - 1; i >= start; --i)
		{
			if (data[i].value > data[i + 1].value)
			{
				WaitTime(0.0001);
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}

		// increase the starting point, because
		// the last stage would have moved the next
		// smallest number to its rightful spot.
		++start;
	}
	sorting_active = false;
}

// A function to sort the algorithm using gnome sort
void Sorter::GnomeSort()
{
	int n = data.size();
	int index = 0;

	while (index < n)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		if (index == 0)
			index++;
		if (data[index].value >= data[index - 1].value)
			index++;
		else
		{
			std::swap(data[index], data[index - 1]);
			index--;
		}
		WaitTime(0.0001);
	}
	sorting_active = false;
}

// Function sort the array using Cycle sort
void Sorter::CycleSort()
{
	int n = data.size();
	// count number of memory writes
	int writes = 0;

	// traverse array elements and put it to on
	// the right place
	for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
	{
		// initialize item as starting point
		Element item = data[cycle_start];

		// Find position where we put the item. We basically
		// count all smaller elements on right side of item.
		int pos = cycle_start;
		for (int i = cycle_start + 1; i < n; i++)
			if (data[i].value < item.value)
				pos++;

		// If item is already in correct position
		if (pos == cycle_start)
			continue;

		// ignore all duplicate  elements
		while (item.value == data[pos].value)
			pos += 1;

		// put the item to it's right position
		if (pos != cycle_start)
		{
			std::swap(item, data[pos]);
			writes++;
		}

		// Rotate rest of the cycle
		while (pos != cycle_start)
		{
			pos = cycle_start;

			WaitTime(0.005);

			// Stop execution if sorting stopped
			if (!sorting_active)
				return;

			// Find position where we put the element
			for (int i = cycle_start + 1; i < n; i++)
			{
				if (data[i].value < item.value)
					pos += 1;
			}

			// ignore all duplicate  elements
			while (item.value == data[pos].value)
				pos += 1;

			// put the item to it's right position
			if (item.value != data[pos].value)
			{
				std::swap(item, data[pos]);
				writes++;
			}
		}
	}
	sorting_active = false;
}

int Sorter::Partition(int low, int high)
{
	// Choosing the pivot
	int pivot = data[high].value;

	// Index of smaller element and indicates
	// the right position of pivot found so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		WaitTime(0.001);
		// If current element is smaller than the pivot
		if (data[j].value < pivot)
		{
			// Increment index of smaller element
			i++;
			std::swap(data[i], data[j]);
		}
	}
	std::swap(data[i + 1], data[high]);
	return (i + 1);
}

void Sorter::QuickSort(int low, int high)
{
	quicksort_thread_mutex.lock();
	quick_sort_thread_depth.push(1);
	quicksort_thread_mutex.unlock();

	if (low < high)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
		{
			quicksort_thread_mutex.lock();
			quick_sort_thread_depth.pop();
			quicksort_thread_mutex.unlock();
			return;
		}

		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = Partition(low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSort(low, pi - 1);
		QuickSort(pi + 1, high);
	}

	quicksort_thread_mutex.lock();
	quick_sort_thread_depth.pop();
	quicksort_thread_mutex.unlock();

	if (quick_sort_thread_depth.size() == 0)
		sorting_active = false;
}

int Sorter::GetNextGap(int gap)
{
	// Shrink gap by Shrink factor
	gap = (gap * 10) / 13;

	if (gap < 1)
		return 1;
	return gap;
}

void Sorter::CombSort()
{
	// Initialize gap
	int n = data.size();
	int gap = n;

	// Initialize swapped as true to make sure that
	// loop runs
	bool swapped = true;

	// Keep running while gap is more than 1 and last
	// iteration caused a swap
	while (gap != 1 || swapped == true)
	{
		if (!sorting_active)
			return;

		// Find next gap
		gap = GetNextGap(gap);

		// Initialize swapped as false so that we can
		// check if swap happened or not
		swapped = false;

		// Compare all elements with current gap
		for (int i = 0; i < n - gap; i++)
		{
			if (data[i].value > data[i + gap].value)
			{
				WaitTime(0.001);
				std::swap(data[i], data[i + gap]);
				swapped = true;
			}
		}
	}
	 sorting_active = false;
}

Sorter::SortingAlgorithms Sorter::GetActiveAlgorithm()
{
	return active_algorithm;
}

void Sorter::SetActiveAlgorithm(SortingAlgorithms active_algorithm)
{
	this->active_algorithm = active_algorithm;
}

std::string Sorter::SortingEnumToString()
{
	std::string text;
	switch (this->active_algorithm)
	{
	case SortingAlgorithms::BubbleSortEnum:
		text = "Bubble Sort";
		break;
	case SortingAlgorithms::CocktailSortEnum:
		text = "Cocktail Sort";
		break;
	case SortingAlgorithms::CombSortEnum:
		text = "Comb Sort";
		break;
	case SortingAlgorithms::GnomeSortEnum:
		text = "Gnome Sort";
		break;
	case SortingAlgorithms::QuickSortEnum:
		text = "Quick Sort";
		break;
	case SortingAlgorithms::ShellSortEnum:
		text = "Shell Sort";
		break;
	case SortingAlgorithms::CycleSortEnum:
		text = "Cycle Sort";
		break;
	default:
		text = "Unknown algorithm";
		break;
	}

	return text;
}

bool Sorter::GetSortingActive()
{
	return sorting_active;
}

void Sorter::SetSortingActive(bool active)
{
	sorting_active = active;
}

void Sorter::StartThread()
{
	std::thread th;

	if (active_algorithm == Sorter::SortingAlgorithms::QuickSortEnum)
		th = std::thread(&Sorter::QuickSort, this, 0, data.size() - 1);
	if (active_algorithm == Sorter::SortingAlgorithms::BubbleSortEnum)
		th = std::thread(&Sorter::BubbleSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CocktailSortEnum)
		th = std::thread(&Sorter::CocktailSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CombSortEnum)
		th = std::thread(&Sorter::CombSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::GnomeSortEnum)
		th = std::thread(&Sorter::GnomeSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::ShellSortEnum)
		th = std::thread(&Sorter::ShellSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CycleSortEnum)
		th = std::thread(&Sorter::CycleSort, this);

	sorting_active = true;
	th.detach();
}