#include "Headers/Column.h"

// CONSTRUCTOR
Column::Column(): interior() {}

// DESTRUCTOR
Column::~Column() {}

// METHODS
void Column::clear() 
{
    interior.clear();
}

void Column::add(Particle *particle) 
{
    interior.push_back(particle);
} 

void Column::check_collisions(Column *next) 
{
    int size = interior.size();
    int next_size = (next->interior).size();
 
    for(int i = 0; i < size; i++) 
    {
        for(int j = i + 1; j < size; j++) 
        {
            (interior[i])->collide_with_particle(interior[j]); 
        }
        for(int j = 0; j < next_size; j++) 
        {
            (interior[i])->collide_with_particle((next->interior)[j]);
        }
    }
}

