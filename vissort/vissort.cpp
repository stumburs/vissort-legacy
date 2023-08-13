#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

const int window_width = 1280;
const int window_height = 720;
const char* window_title = "vissort";
const int max_fps = 60;

std::mutex mutex;

struct Element
{
	int value;
	Color color;
};

std::vector<Element> vec;
int element_count = 640;

int Max(const std::vector<Element>& vec)
{
	int max = 0;
	for (const auto& elem : vec)
	{
		if (elem.value > max)
			max = elem.value;
	}
	return max;
}

void DrawVec(const std::vector<Element>& vec)
{
	int scale_x = window_width / vec.size();
	int scale_y = window_height / Max(vec);
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		DrawRectangle(
			0 + scale_x * i,
			window_height - vec[i].value * scale_y,
			scale_x,
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
		swapped = false;
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

		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = Partition(vec, low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSort(vec, low, pi - 1);
		QuickSort(vec, pi + 1, high);
	}
}

int main()
{
	InitWindow(window_width, window_height, window_title);
	SetTargetFPS(max_fps);
	srand(time(NULL));

	for (int i = 1; i < element_count + 1; i++)
	{
		Element elem{};
		elem.value = i;
		elem.color = WHITE;
		vec.push_back(elem);
	}

	while (!WindowShouldClose())
	{
		// Update
		{
			if (IsKeyPressed(KEY_R))
				RandomizeVec(vec);
			if (IsKeyDown(KEY_LEFT_SHIFT))
			{
				if (IsKeyPressed(KEY_B))
				{
					std::thread th(BubbleSort, std::ref(vec));
					th.detach();
				}
				if (IsKeyPressed(KEY_Q))
				{
					std::thread th(QuickSort, std::ref(vec), 0, vec.size() - 1);
					th.detach();
				}
			}
			if (IsKeyPressed(KEY_LEFT))
				std::reverse(vec.begin(), vec.end());
		}

		// Draw
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawVec(vec);
			DrawFPS(20, 20);
		}
		EndDrawing();
	}
	CloseWindow();
}
