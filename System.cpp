#include "System.h"
#include <random>

System::System(int n, double r_)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist((double) 0, (double) 1);

    // creating n boids
    Boid::r = r_;
    b.clear();
    for (int i = 1; i <= n; i ++)
        b.push_back(Boid(Vector2(dist(gen) * 10, dist(gen) * 10), Vector2((dist(gen) - 0.5) * 2, (dist(gen) - 0.5) * 2), Vector2(0, 0))); 
}

void System::SimulateFrame()
{
    Vector2 a(0, 0), c(0, 0), s(0, 0), temp(0, 0);
    int nr_flock_mates;
    for (int i = 0; i < b.size(); i ++)
    {
        nr_flock_mates = 0;
        a.x = a.y = c.x = c.y = s.x = s.y = temp.x = temp.y = 0;
        for (int j = 0; j < b.size(); j ++)
            if (i != j && b[i].pos.Distance(b[j].pos) <= Boid::r)
            {
                nr_flock_mates ++;
                a = a + b[j].velocity;
                c = c + b[j].pos;
                
                temp = b[i].pos.DistanceVector(b[j].pos, 10);
                temp.Inverse(Boid::r);
                temp.Flip();
                s = s + temp;
            }

        a = (a - b[i].velocity) / nr_flock_mates / 6.5;
        c = (c / nr_flock_mates - b[i].pos) / 200.0;
        s = s / nr_flock_mates / 12.0;
        
        if (nr_flock_mates == 0)
            b[i].acceleration = b[i].acceleration / 2.0;
        else
            b[i].acceleration = a + c + s;
        b[i].acceleration.Clamped(0.07);
    }

    for (int i = 0; i < b.size(); i ++)
    {
        b[i].velocity = b[i].velocity * 0.98 + b[i].acceleration;
        b[i].velocity.Clamped(0.07);
        b[i].pos = b[i].pos + b[i].velocity;
        b[i].pos.Modulo(10);
    }
}

void System::PrintPositions()
{
    std::cout << "----- POSITIONS -----\n";
    for (int i = 0; i < b.size(); i ++)
        std::cout << i << ' ' << b[i].pos << '\n';
}

