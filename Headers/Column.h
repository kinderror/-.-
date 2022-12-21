#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include "Particle.h"

class Column final 
{
private:
    std::vector<Particle*> interior;
public:
    Column();
    ~Column();
    void clear(); 
    void add(Particle *particle); 
    void check_collisions(Column *next); 
};

#endif
