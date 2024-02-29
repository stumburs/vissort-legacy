#include "Sorter.h"
#include <thread>
#include <stdexcept>

Sorter::Sorter(DataGenerator& data_generator) : data_generator(data_generator)
{
	data_generator.Initialize(data, 100);
};

std::vector<Element>& Sorter::GetData()
{
	return this->data;
}

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
			if (!sorting_active)
				return;
			if (data[j].value > data[j + 1].value)
			{
				std::swap(data[j], data[j + 1]);
				WaitTime(sorting_delay);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
	sorting_active = false;
}

void Sorter::ShellSort()
{
	int n = data.size();

	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			// Stop execution if sorting stopped
			if (!sorting_active)
				return;

			Element temp = data[i];

			int j;
			for (j = i; j >= gap && data[j - gap].value > temp.value; j -= gap)
			{
				data[j] = data[j - gap];
				WaitTime(sorting_delay);
			}

			data[j] = temp;
		}
	}
	sorting_active = false;
}

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

		swapped = false;

		for (int i = start; i < end; ++i)
		{
			// Stop execution if sorting stopped
			if (!sorting_active)
				return;
			if (data[i].value > data[i + 1].value)
			{
				WaitTime(sorting_delay);
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;

		swapped = false;

		--end;

		for (int i = end - 1; i >= start; --i)
		{
			// Stop execution if sorting stopped
			if (!sorting_active)
				return;
			if (data[i].value > data[i + 1].value)
			{
				WaitTime(sorting_delay);
				std::swap(data[i], data[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
	sorting_active = false;
}

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
		WaitTime(sorting_delay);
	}
	sorting_active = false;
}

void Sorter::CycleSort()
{
	int n = data.size();
	int writes = 0;

	for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
	{
		Element item = data[cycle_start];

		int pos = cycle_start;
		for (int i = cycle_start + 1; i < n; i++)
			if (data[i].value < item.value)
				pos++;

		if (pos == cycle_start)
			continue;

		while (item.value == data[pos].value)
			pos += 1;

		if (pos != cycle_start)
		{
			std::swap(item, data[pos]);
			writes++;
		}

		while (pos != cycle_start)
		{
			pos = cycle_start;

			WaitTime(sorting_delay);

			// Stop execution if sorting stopped
			if (!sorting_active)
				return;

			for (int i = cycle_start + 1; i < n; i++)
			{
				if (data[i].value < item.value)
					pos += 1;
			}

			while (item.value == data[pos].value)
				pos += 1;

			if (item.value != data[pos].value)
			{
				std::swap(item, data[pos]);
				writes++;
			}
		}
	}
	sorting_active = false;
}

// Quicksort helper function
int Sorter::Partition(int low, int high)
{
	int pivot = data[high].value;

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		// Break if sorting stopped
		if (!sorting_active)
			break;

		WaitTime(sorting_delay);
		if (data[j].value < pivot)
		{
			i++;
			std::swap(data[i], data[j]);
		}
	}
	std::swap(data[i + 1], data[high]);
	return (i + 1);
}

void Sorter::QuickSort(int low, int high)
{
	// Ugly mutex shenanigans
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

		int pi = Partition(low, high);

		QuickSort(low, pi - 1);
		QuickSort(pi + 1, high);
	}

	quicksort_thread_mutex.lock();
	quick_sort_thread_depth.pop();
	quicksort_thread_mutex.unlock();

	if (quick_sort_thread_depth.size() == 0)
		sorting_active = false;
}

// Comb sort helper function
int Sorter::GetNextGap(int gap)
{
	gap = (gap * 10) / 13;

	if (gap < 1)
		return 1;
	return gap;
}

void Sorter::CombSort()
{
	int n = data.size();
	int gap = n;

	bool swapped = true;
	
	while (gap != 1 || swapped == true)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		gap = GetNextGap(gap);

		swapped = false;

		for (int i = 0; i < n - gap; i++)
		{
			// Stop execution if sorting stopped
			if (!sorting_active)
				return;
			if (data[i].value > data[i + gap].value)
			{
				WaitTime(sorting_delay);
				std::swap(data[i], data[i + gap]);
				swapped = true;
			}
		}
	}
	sorting_active = false;
}

// Pancake sort helper function
void Sorter::Flip(int i)
{
	Element temp;
	int start = 0;
	while (start < i)
	{
		temp = data[start];
		data[start] = data[i];
		data[i] = temp;
		start++;
		i--;
	}
}

// Pancake sort helper function
int Sorter::FindMax(int n)
{
	int mi, i;
	for (mi = 0, i = 0; i < n; ++i)
		if (data[i].value > data[mi].value)
			mi = i;
	return mi;
}

void Sorter::PancakeSort()
{
	int n = data.size();
	
	for (int curr_size = n; curr_size > 1; --curr_size)
	{
		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		int mi = FindMax(curr_size);
		
		if (mi != curr_size - 1)
		{
			WaitTime(sorting_delay);
			Flip(mi);
			Flip(curr_size - 1);
		}
	}
	sorting_active = false;
}

Sorter::SortingAlgorithms Sorter::GetActiveAlgorithm() const
{
	return active_algorithm;
}

void Sorter::SetActiveAlgorithm(SortingAlgorithms active_algorithm)
{
	this->active_algorithm = active_algorithm;
}

std::string Sorter::SortingEnumToString(SortingAlgorithms algorithm)
{
	std::string text;
	switch (algorithm)
	{
	case SortingAlgorithms::BubbleSort:
		text = "Bubble Sort";
		break;
	case SortingAlgorithms::CocktailSort:
		text = "Cocktail Sort";
		break;
	case SortingAlgorithms::CombSort:
		text = "Comb Sort";
		break;
	case SortingAlgorithms::GnomeSort:
		text = "Gnome Sort";
		break;
	case SortingAlgorithms::QuickSort:
		text = "Quick Sort";
		break;
	case SortingAlgorithms::ShellSort:
		text = "Shell Sort";
		break;
	case SortingAlgorithms::CycleSort:
		text = "Cycle Sort";
		break;
	case SortingAlgorithms::PancakeSort:
		text = "Pancake Sort";
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

	if (active_algorithm == Sorter::SortingAlgorithms::QuickSort)
		th = std::thread(&Sorter::QuickSort, this, 0, data.size() - 1);
	if (active_algorithm == Sorter::SortingAlgorithms::BubbleSort)
		th = std::thread(&Sorter::BubbleSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CocktailSort)
		th = std::thread(&Sorter::CocktailSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CombSort)
		th = std::thread(&Sorter::CombSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::GnomeSort)
		th = std::thread(&Sorter::GnomeSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::ShellSort)
		th = std::thread(&Sorter::ShellSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::CycleSort)
		th = std::thread(&Sorter::CycleSort, this);
	if (active_algorithm == Sorter::SortingAlgorithms::PancakeSort)
		th = std::thread(&Sorter::PancakeSort, this);

	sorting_active = true;
	th.detach();
}

void Sorter::SetSortingDelay(double delay)
{
	this->sorting_delay = delay;
}
