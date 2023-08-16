#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>

int window_width = 800;
int window_height = 600;
const char* window_title = "vissort";
const int max_fps = 60;

std::mutex mutex;

//Sound sound;

std::atomic<bool> sorting_active(false);
bool started_thread = false;


enum SortingAlgorithms
{
	BubbleSortEnum,
	QuickSortEnum,
	CombSortEnum,
	ShellSortEnum,
	CocktailSortEnum,
	GnomeSortEnum
};

struct Element
{
	int value;
	Color color;
};

std::vector<Element> vec;
int element_count = 0;

int Max(const std::vector<Element>& vec)
{
	int max = vec[0].value;
	for (const auto& elem : vec)
	{
		if (elem.value > max)
			max = elem.value;
	}
	return max;
}

void DrawVec(const std::vector<Element>& vec)
{
	float scale_x = GetScreenWidth() / (float)vec.size();
	float scale_y = GetScreenHeight() / (float)Max(vec);
	for (int i = 0; i < vec.size(); i++)
	{
		DrawRectangle(
			scale_x * i,
			GetScreenHeight() - vec[i].value * scale_y,
			ceilf(scale_x),
			vec[i].value * scale_y,
			vec[i].color
		);
	}
}

void RandomizeVec(std::vector<Element>& vec)
{
	for (std::size_t i = 0; i < vec.size(); i++)
		std::swap(vec[i], vec[rand() % vec.size()]);
}

void Swap(Element* xp, Element* yp)
{
	Element temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// An optimized version of Bubble Sort
void BubbleSort(std::vector<Element>& vec)
{
	int i, j;
	bool swapped;
	int n = vec.size();
	for (i = 0; i < n - 1; i++) {

		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		swapped = false;
		//SetSoundPitch(sound, (float)i / n + 0.5);
		//PlaySound(sound);
		for (j = 0; j < n - i - 1; j++) {
			if (vec[j].value > vec[j + 1].value) {
				Swap(&vec[j], &vec[j + 1]);
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
}

// Quicksort
int Partition(std::vector<Element>& vec, int low, int high)
{
	// Choosing the pivot
	int pivot = vec[high].value;

	// Index of smaller element and indicates
	// the right position of pivot found so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		//SetSoundPitch(sound, (float)j / high + 0.2);
		//PlaySound(sound);
		WaitTime(0.001);
		// If current element is smaller than the pivot
		if (vec[j].value < pivot) {

			// Increment index of smaller element
			i++;
			Swap(&vec[i], &vec[j]);
		}
	}
	Swap(&vec[i + 1], &vec[high]);
	return (i + 1);
}

// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void QuickSort(std::vector<Element>& vec, int low, int high)
{
	if (low < high) {

		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = Partition(vec, low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSort(vec, low, pi - 1);
		QuickSort(vec, pi + 1, high);
	}

}


void ShellSort(std::vector<Element>& vec)
{
	int n = vec.size();
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
			Element temp = vec[i];

			// shift earlier gap-sorted elements up until the correct 
			// location for a[i] is found
			int j;
			for (j = i; j >= gap && vec[j - gap].value > temp.value; j -= gap)
			{
				vec[j] = vec[j - gap];
				WaitTime(0.001);
			}

			//  put temp (the original a[i]) in its correct location
			vec[j] = temp;
		}
	}
}

// Comb sort
// To find gap between elements
int getNextGap(int gap)
{
	// Shrink gap by Shrink factor
	gap = (gap * 10) / 13;

	if (gap < 1)
		return 1;
	return gap;
}

// Function to sort a[0..n-1] using Comb Sort
void CombSort(std::vector<Element>& vec)
{
	// Initialize gap
	int n = vec.size();
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
		gap = getNextGap(gap);

		// Initialize swapped as false so that we can
		// check if swap happened or not
		swapped = false;

		// Compare all elements with current gap
		for (int i = 0; i < n - gap; i++)
		{
			if (vec[i].value > vec[i + gap].value)
			{
				WaitTime(0.001);
				Swap(&vec[i], &vec[i + gap]);
				swapped = true;
			}
		}
	}
}

// Cocktail sort
void CocktailSort(std::vector<Element>& vec)
{
	int n = vec.size();
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) {

		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		// reset the swapped flag on entering
		// the loop, because it might be true from
		// a previous iteration.
		swapped = false;

		// loop from left to right same as
		// the bubble sort
		for (int i = start; i < end; ++i) {
			if (vec[i].value > vec[i + 1].value) {
				WaitTime(0.0001);
				Swap(&vec[i], &vec[i + 1]);
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
		for (int i = end - 1; i >= start; --i) {
			if (vec[i].value > vec[i + 1].value) {
				WaitTime(0.0001);
				Swap(&vec[i], &vec[i + 1]);
				swapped = true;
			}
		}

		// increase the starting point, because
		// the last stage would have moved the next
		// smallest number to its rightful spot.
		++start;
	}
}

// A function to sort the algorithm using gnome sort
void GnomeSort(std::vector<Element>& vec)
{
	int n = vec.size();
	int index = 0;

	while (index < n) {

		// Stop execution if sorting stopped
		if (!sorting_active)
			return;

		if (index == 0)
			index++;
		if (vec[index].value >= vec[index - 1].value)
			index++;
		else {
			Swap(&vec[index], &vec[index - 1]);
			index--;
		}
		WaitTime(0.0001);
	}
	return;
}

void DrawActiveAlgorithmText(SortingAlgorithms active_algorithm)
{
	std::string text;
	switch (active_algorithm)
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
	default:
		text = "Unknown algorithm";
		break;
	}

	DrawText(text.c_str(), 20, 40, 20, LIME);
}

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(window_width, window_height, window_title);
	InitAudioDevice();
	SetWindowSize(GetMonitorWidth(0) / 2, GetMonitorHeight(0) / 2);
	element_count = GetScreenWidth();
	SetTargetFPS(max_fps);
	srand(time(NULL));
	//sound = LoadSound("sound.wav");

	SortingAlgorithms active_algorithm = SortingAlgorithms::BubbleSortEnum;

	for (int i = 1; i < element_count + 1; i++)
	{
		Element elem{};
		elem.value = i;
		elem.color = ColorFromHSV((float)i / element_count * 360.0f, 0.3f, 1.0f);
		vec.push_back(elem);
	}

	while (!WindowShouldClose())
	{
		// Update
		{

			// Randomize data
			if (IsKeyPressed(KEY_R) && !sorting_active)
				RandomizeVec(vec);

			// Start/Stop sorting
			if (IsKeyPressed(KEY_P))
			{
				sorting_active = !sorting_active;
				if (sorting_active)
				{
					std::thread th;
					
					if (active_algorithm == SortingAlgorithms::QuickSortEnum)
						th = std::thread(QuickSort, std::ref(vec), 0, vec.size() - 1);
					if (active_algorithm == SortingAlgorithms::BubbleSortEnum)
						th = std::thread(BubbleSort, std::ref(vec));
					if (active_algorithm == SortingAlgorithms::CocktailSortEnum)
						th = std::thread(CocktailSort, std::ref(vec));
					if (active_algorithm == SortingAlgorithms::CombSortEnum)
						th = std::thread(CombSort, std::ref(vec));
					if (active_algorithm == SortingAlgorithms::GnomeSortEnum)
						th = std::thread(GnomeSort, std::ref(vec));
					if (active_algorithm == SortingAlgorithms::ShellSortEnum)
						th = std::thread(ShellSort, std::ref(vec));

					std::cout << "Thread started!\n";
					
					th.detach();
				}
			}

			// Select sorting algorithm
			if (IsKeyDown(KEY_LEFT_SHIFT))
			{
				if (IsKeyPressed(KEY_B))
					active_algorithm = SortingAlgorithms::BubbleSortEnum;
				if (IsKeyPressed(KEY_Q))
					active_algorithm = SortingAlgorithms::QuickSortEnum;
				if (IsKeyPressed(KEY_S))
					active_algorithm = SortingAlgorithms::ShellSortEnum;
				if (IsKeyPressed(KEY_C))
					active_algorithm = SortingAlgorithms::CombSortEnum;
				if (IsKeyPressed(KEY_V))
					active_algorithm = SortingAlgorithms::CocktailSortEnum;
				if (IsKeyPressed(KEY_G))
					active_algorithm = SortingAlgorithms::GnomeSortEnum;
			}

			// Flip data left to right
			if (IsKeyPressed(KEY_LEFT))
				std::reverse(vec.begin(), vec.end());
		}

		// Draw
		BeginDrawing();
		{
			ClearBackground(BLANK);
			DrawVec(vec);
			DrawFPS(20, 20);
			DrawActiveAlgorithmText(active_algorithm);
			DrawText(sorting_active ? "Running" : "Stopped", 20, 60, 20, LIME);
		}
		EndDrawing();
	}
	CloseWindow();
	CloseAudioDevice();
}
