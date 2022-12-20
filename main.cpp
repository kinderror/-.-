#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

// ......const values......
static const float DELTA = 0.04;
static const int WIDTH = 8000, HEIGHT = 200, RADIUS = 1, AMOUNT = 100000, COLUMNS = 4000 + 1, INITIAL_VELOCITY = 1; 

// ......functions and structures......
template<typename T>
class Particle final 
{
private:
    T x, y, vx, vy;
public:
    Particle(T x = 0, T y = 0, T vx = 0, T vy = 0):
        x(x), y(y), vx(vx), vy(vy) {}
    T get_x() const { return x; }
    T get_y() const { return y; }
    T get_vx() const { return vx; }
    T get_vy() const { return vy; }
    void wall() 
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
    void motion() 
    {
        x += vx * DELTA;
        y += vy * DELTA;
    }
    void collision(Particle *particle)
    {
        if(not intersect(particle)) return;
        T dx, dy, dr, dvx, dvy, cs, sn;
        dx = particle->x - x;
        dy = particle->y - y;
        dr = pow(dx * dx + dy * dy, 0.5);
        dvx = particle->vx - vx;
        dvy = particle->vy - vy;
        cs = dx / dr;
        sn = dy / dr;
        vx += dvx * cs * cs + dvy * cs * sn;
        vy += dvx * cs * sn + dvy * sn * sn;
        particle->vx -= dvx * cs * cs + dvy * cs * sn;
        particle->vy -= dvx * cs * sn + dvy * sn * sn;
    }
    bool intersect(Particle *particle) const
    {
        T dx, dy;
        dx = particle->x - x;
        dy = particle->y - y;
        return dx * dx + dy * dy < 4 * RADIUS * RADIUS; 
    }
};

template<class T>
class Column final 
{
private:
    std::vector<T*> interior;
public:
    Column():
        interior() {}
    ~Column() {}
    void clear() 
    {
        interior.clear();
    }
    void push(T *particle) 
    {
        interior.push_back(particle);
    } 
    void collisions(Column<T> *next) 
    {
        for(int i = 0; i < interior.size(); i++) 
        {
            for(int j = i + 1; j < interior.size(); j++) 
            {
                (interior[i])->collision(interior[j]); 
            }
            for(int j = 0; j < (next->interior).size(); j++) 
            {
                (interior[i])->collision((next->interior)[j]);
            }
        }
    }
};

template<typename T>
void create_gas(std::vector<Column<Particle<T>>*> &columns, std::vector<Particle<T>*> &particles) 
{
    T x, y, vx, vy;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-INITIAL_VELOCITY, INITIAL_VELOCITY);
    Column<Particle<T>> *column_pointer = nullptr;
    Particle<T> *particle_pointer = nullptr;
    for(int i = 0; i < COLUMNS; i++) 
    {
        column_pointer = new Column<Particle<T>>();
        columns.push_back(column_pointer);
    }
    for(int i = 0; i < WIDTH / 4; i++)
    {
        x = 2 + i * 4;
    for(int j = 0; j < HEIGHT / 4; j++)
    {
        y = 2 + j * 4;
        vx = dist(gen);
        vy = pow(INITIAL_VELOCITY * INITIAL_VELOCITY - vx * vx, 0.5);
        particle_pointer = new Particle<T>(x, y, vx, vy);
        particles.push_back(particle_pointer);
    }
}

}

template<typename T>
void iteration(std::vector<Column<Particle<T>>*> &columns, std::vector<Particle<T>*> &particles) 
{
    for(int i = 0; i < AMOUNT; i++)
    {
        (columns[static_cast<int>((particles[i])->get_x()) / (2 * RADIUS)])->push(particles[i]);
        (particles[i])->wall();
    }
    for(int i = 0; i < COLUMNS; i++) 
    {
        (columns[i])->collisions(columns[i + 1]);
        (columns[i])->clear();
    }
    for (int i = 0; i < AMOUNT; i++) {
        (particles[i])->motion();
    }
}

template<typename T>
void run_simulation(T period)
{
    std::vector<Column<Particle<T>>*> columns;
    std::vector<Particle<T>*> particles;
    create_gas<T>(columns, particles);
    std::ofstream distribution, random_walk;
    distribution.open("distribution.txt");
    random_walk.open("random_walk.txt");
    for(T time = 0; time < period; time += DELTA)
    {
        std::cout << time << "\n";
        random_walk 
            << time << " "
            << (particles[0])->get_x() << " "
            << (particles[0])->get_y() << "\n";  
        iteration<T>(columns, particles);
    }
    T v, sum = 0, x, y;
    for(int i = 0; i < AMOUNT; i++)
    {
        v = pow((particles[i])->get_vx(), 2) +
            pow((particles[i])->get_vy(), 2);
        distribution << pow(v, 0.5) << "\n";
        x = particles[i]->get_x();
        y = particles[i]->get_y();
        if(x < RADIUS or x > WIDTH - RADIUS) std::cout << x << "\n";
        if(y < RADIUS or y > HEIGHT - RADIUS) std::cout << y << "\n";
        sum += v;
    }
    std::cout << "Mean: " << sum / AMOUNT << std::endl;
    for(int i = 0; i < COLUMNS; i++)
    {
        delete columns[i];
    }
    for(int i = 0; i < AMOUNT; i++)
    {
        delete particles[i];
    }
}

// ......main......
int main() {
    run_simulation<float>(200);
    return 0;
}

