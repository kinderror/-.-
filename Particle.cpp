#include "Headers/Particle.h"

// CONSTRUCTOR
Particle::Particle(float x, float y, float vx, float vy):
    x(x), y(y), vx(vx), vy(vy) {}

// DESTRUCTOR
Particle::~Particle() {}

// RETURN PRIVATE PARAMETERS
float Particle::get_x() const { return x; }

float Particle::get_y() const { return y; }

float Particle::get_vx() const { return vx; }

float Particle::get_vy() const { return vy; }

// MOTION METHODS
void Particle::collide_with_wall() 
{
    if (x < RADIUS or x > WIDTH - RADIUS) 
    {
        vx = -vx;
    }
    if (y < RADIUS or y > HEIGHT - RADIUS) 
    {
        vy = -vy;
    }
}

void Particle::collide_with_particle(Particle *particle)
{
    float dx, dy, dr;
    dx = particle->x - x;
    dy = particle->y - y;
    dr = pow(dx * dx + dy * dy, 0.5);
    if(dr > 2 * RADIUS) return;

    float dvx, dvy, cs, sn;
    dvx = particle->vx - vx;
    dvy = particle->vy - vy;
    cs = dx / dr;
    sn = dy / dr;

    vx += dvx * cs * cs + dvy * cs * sn;
    vy += dvx * cs * sn + dvy * sn * sn;
    particle->vx -= dvx * cs * cs + dvy * cs * sn;
    particle->vy -= dvx * cs * sn + dvy * sn * sn;
}

void Particle::move() 
{
    x += vx * DELTA;
    y += vy * DELTA;
}


