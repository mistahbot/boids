#include "Boid.h"

class System
{
public:
    // list of boids
    std::vector <Boid> b;

    System(int n, double r_);
    void PrintPositions();
    void SimulateFrame();
};