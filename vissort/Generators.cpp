#include "Generators.h"
#include "GenAscending.h"
#include "GenRandom.h"
#include "Randomize.h"
#include "GenDescending.h"
#include "GenSin.h"

Generators::Generators()
{
    srand(time(NULL));
    generators["Ascending"] = std::make_unique<GenAscending>();
    generators["Descending"] = std::make_unique<GenDescending>();
    generators["Sin"] = std::make_unique<GenSin>();
    generators["Random"] = std::make_unique<GenRandom>();
    generators["Randomize"] = std::make_unique<Randomize>(); // Randomizes already existing data.
}
