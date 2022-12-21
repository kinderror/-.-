#include "Headers/create_gas.h"

// CREATE GAS
void create_gas(std::vector<Column*> &columns, std::vector<Particle*> &particles) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-INITIAL_VELOCITY, INITIAL_VELOCITY);

    Column *column_pointer = nullptr;
    Particle *particle_pointer = nullptr;
    
    for(int i = 0; i < COLUMNS; i++) 
    {
        column_pointer = new Column();
        columns.push_back(column_pointer);
    }

    float x, y, vx, vy;
    for(int i = 0; i < WIDTH / 4; i++)
    {
        x = 2 + i * 4;
        for(int j = 0; j < HEIGHT / 4; j++)
        {
            y = 2 + j * 4;
            vx = dist(gen);
            vy = pow(INITIAL_VELOCITY * INITIAL_VELOCITY - vx * vx, 0.5);
            particle_pointer = new Particle(x, y, vx, vy);
            particles.push_back(particle_pointer);
        }
    }
}
