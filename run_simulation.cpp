#include "Headers/run_simulation.h"

void run_simulation()
{
    std::vector<Column*> columns;
    std::vector<Particle*> particles;

    create_gas(columns, particles);

    std::ofstream distribution, random_walk;
    distribution.open("distribution.txt");
    random_walk.open("random_walk.txt");
    
    for(float time = 0; time < DURATION; time += DELTA)
    {
        random_walk 
            << time << " "
            << (particles[0])->get_x() << " "
            << (particles[0])->get_y() << "\n";  
        iterate(columns, particles);
    }

    float velocity_squared, energy = 0;
    for(int i = 0; i < AMOUNT; i++)
    {
        velocity_squared = pow((particles[i])->get_vx(), 2) +
            pow((particles[i])->get_vy(), 2);
        distribution << pow(velocity_squared, 0.5) << "\n";
        energy += velocity_squared;
    }
    std::cout << "Mean energy: " << energy / AMOUNT << std::endl;
    
    for(int i = 0; i < COLUMNS; i++)
    {
        delete columns[i];
    }
    for(int i = 0; i < AMOUNT; i++)
    {
        delete particles[i];
    }
}
