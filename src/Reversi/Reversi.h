#include "GameBoard.h"
#include "Agent.h"

class Reversi
{
public:
    Reversi();

    static float compete(Agent *a1, Agent *a2, uint16_t n_games = 100u, bool verbose = true);

private:
    
};
