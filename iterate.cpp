#include "Headers/iterate.h"

// ITERATE
void iterate(std::vector<Column*> &columns, std::vector<Particle*> &particles) 
{
    for(int i = 0; i < AMOUNT; i++)
    {
        (columns[static_cast<int>((particles[i])->get_x()) / 
            (2 * RADIUS)])->add(particles[i]);
        (particles[i])->collide_with_wall();
    }

    for(int i = 0; i < COLUMNS; i++) 
    {
        (columns[i])->check_collisions(columns[i + 1]);
        (columns[i])->clear();
    }

    for (int i = 0; i < AMOUNT; i++) {
        (particles[i])->move();
    }
}
