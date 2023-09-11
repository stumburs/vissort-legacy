#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>

#include <stack>

#include "App.h"

std::mutex mutex;

std::stack<int> quick_sort_finished;

//Sound sound;

std::atomic<bool> sorting_active(false);
bool started_thread = false;

// Quicksort
//int Partition(std::vector<Element>& vec, int low, int high)
//{
//	// Choosing the pivot
//	int pivot = vec[high].value;
//
//	// Index of smaller element and indicates
//	// the right position of pivot found so far
//	int i = (low - 1);
//
//	for (int j = low; j <= high - 1; j++) {
//		//SetSoundPitch(sound, (float)j / high + 0.2);
//		//PlaySound(sound);
//		WaitTime(0.001);
//		// If current element is smaller than the pivot
//		if (vec[j].value < pivot) {
//
//			// Increment index of smaller element
//			i++;
//			Swap(&vec[i], &vec[j]);
//		}
//	}
//	Swap(&vec[i + 1], &vec[high]);
//	return (i + 1);
//}
//
//// The main function that implements QuickSort
//// arr[] --> Array to be sorted,
//// low --> Starting index,
//// high --> Ending index
//void QuickSort(std::vector<Element>& vec, int low, int high)
//{
//	mutex.lock();
//	quick_sort_finished.push(1);
//	mutex.unlock();
//
//	if (low < high) {
//
//		// Stop execution if sorting stopped
//		if (!sorting_active)
//		{
//			mutex.lock();
//			quick_sort_finished.pop();
//			mutex.unlock();
//			return;
//		}
//
//		// pi is partitioning index, arr[p]
//		// is now at right place
//		int pi = Partition(vec, low, high);
//
//		// Separately sort elements before
//		// partition and after partition
//		QuickSort(vec, low, pi - 1);
//		QuickSort(vec, pi + 1, high);
//	}
//
//	mutex.lock();
//	quick_sort_finished.pop();
//	mutex.unlock();
//
//	if (quick_sort_finished.size() == 0)
//		sorting_active = false;
//}


// Comb sort
// To find gap between elements
//int getNextGap(int gap)
//{
//	// Shrink gap by Shrink factor
//	gap = (gap * 10) / 13;
//
//	if (gap < 1)
//		return 1;
//	return gap;
//}
//
//// Function to sort a[0..n-1] using Comb Sort
//void CombSort(std::vector<Element>& vec)
//{
//	// Initialize gap
//	int n = vec.size();
//	int gap = n;
//
//	// Initialize swapped as true to make sure that
//	// loop runs
//	bool swapped = true;
//
//	// Keep running while gap is more than 1 and last
//	// iteration caused a swap
//	while (gap != 1 || swapped == true)
//	{
//
//		if (!sorting_active)
//			return;
//
//		// Find next gap
//		gap = getNextGap(gap);
//
//		// Initialize swapped as false so that we can
//		// check if swap happened or not
//		swapped = false;
//
//		// Compare all elements with current gap
//		for (int i = 0; i < n - gap; i++)
//		{
//			if (vec[i].value > vec[i + gap].value)
//			{
//				WaitTime(0.001);
//				Swap(&vec[i], &vec[i + gap]);
//				swapped = true;
//			}
//		}
//	}
//	sorting_active = false;
//}




int main()
{
	App app;
	app.Run();
	return 0;
}
