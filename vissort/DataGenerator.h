#pragma once
#include <vector>
#include "Element.h"
#include <string>

class DataGenerator
{
public:
	DataGenerator();
	void Initialize(std::vector<Element>& data, std::size_t size);
	void Randomize(std::vector<Element>& data);
	void Sin(std::vector<Element>& data);
	void Fuzzy(std::vector<Element>& data);
	void Reverse(std::vector<Element>& data);

	enum ShufflingTypes
	{
		SinShuffle = 0,
		FuzzyShuffle,
		ReverseShuffle,
		END
	};

	void Shuffle(std::vector<Element>& data);
	void SetActiveShuffle(ShufflingTypes type);
	std::string ShufflingTypesToString(ShufflingTypes type);
	ShufflingTypes active_shuffle = SinShuffle;
};
