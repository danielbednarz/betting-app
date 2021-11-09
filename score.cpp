#include "score.h"
#include <chrono> //For system_clock
#include <random>

using namespace std;

int Score::DrawScore()
{
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::default_random_engine generator(seed);

//    std::uniform_int_distribution<int> distributionInteger(0, 6); // Set the numbers for int.

//    return distributionInteger(generator);

    srand(time(0));

    return rand()% 6;
}

