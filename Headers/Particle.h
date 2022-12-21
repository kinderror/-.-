#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include "CONSTANTS.h"

class Particle final 
{
private:
    float x, y, vx, vy;
public:
    Particle(float x = 0, float y = 0, float vx = 0, float vy = 0);
    ~Particle();
    float get_x() const;
    float get_y() const;
    float get_vx() const;
    float get_vy() const;
    void collide_with_wall(); 
    void collide_with_particle(Particle *particle);
    void move();
};

#endif
