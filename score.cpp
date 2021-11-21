#include "score.h"

using namespace std;

int Score::DrawScore()
{
    srand(time(0));

    return rand()% 6;
}

