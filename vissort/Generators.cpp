#include "Generators.h"
#include "GenAscending.h"
#include "GenRandom.h"
#include "Randomize.h"

Generators::Generators()
{
    generators["Ascending"] = std::make_unique<GenAscending>();
    generators["Random"] = std::make_unique<GenRandom>();
    generators["Randomize"] = std::make_unique<Randomize>();
}
