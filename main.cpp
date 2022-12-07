#include <iostream>
#include <cmath>
#include <random>

// ......const values......
const float DELTA = 0.01;
const int WIDTH = 400, HEIGHT = 40, RADIUS = 1, AMOUNT = 1000, COLUMNS = 200 + 1, INITIAL_VELOCITY = 1;

// ......functions and structures......
template<typename T>
class Particle final 
{
private:
    T x;
    T y;
    T vx;
    T vy;
public:
    Particle(T x, T y, T vx, T vy):
        x(x), y(y), vx(vx), vy(vy) {}
    T get_vx() { return vx; }
    T get_vy() { return vy; }
    void wall() 
    {
        if (x < RADIUS or x > WIDTH - RADIUS) 
        {
            vx = -vx;
        }
        if (y < RADIUS or y > WIDTH - RADIUS) 
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
    bool intersect(Particle *particle)
    {
        T dx, dy;
        dx = particle->x - x;
        dy = particle->y - y;
        return dx * dx + dy * dy < 4 * RADIUS * RADIUS; 
    }
};

class Column final 
{
private:
    Particle *interior;
    size_t amount;
public:
    Column():
        interior(new Particle [0]), amount(0) {}
    ~Column() { delete [] interior; }
    void clear() 
    {
        delete [] interior;
        interior = new Particle [0];
        amount = 0;
    }
    void push(Particle *particle) 
    {
        Particle *temp = new Particle [amount];
        for(int idx = 0; idx < amount; idx++) 
        {
            temp + idx = interior + idx;
        }
        temp + amount = particle;
        delete [] interior;
        interior = temp;
        amount++;
    } 
    void colissions() 
    {
        for(int i = 0; i < amount; i++) 
        {
            for(int j = i + 1; j < amount; j++) 
            {
                if((interior + i)->intersect(interior + j)) 
                {
                    (interior + i)->collision(interior + j);
                }
            }
            for(int j = 0; j < (this + 1)->amount; j++) 
            {
                if((interior + i)->intersect((this + 1)->interior + j)) 
                {
                    (interior + i)->collision((this + 1)->interior + j);
                }
            }
        }
    }
};

template<typename T>
void create_gas(Column *columns, Particle *particles) 
{
    T x, y, vx, vy;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-INITIAL_VELOCITY, INITIAL_VELOCITY);
    for(int i = 0; i < COLUMNS; i++) 
    {
        columns + i = Column();
    }
    for(int i = 0; i < WIDTH / 4; i++)
    {
        x = 2 + i * 4;
        for(int j = 0; j < HEIGHT / 4; j++)
        {
            y = 2 + j * 4;
            vx = dist(gen);
            vy = pow(INITIAL_VELOCITY * INITIAL_VELOCITY - vx * vx, 0.5);
            particles + idx = Particle(x, y, vx, vy);
        }
    }

}

template<typename T>
void iteration(Column *columns, Particle *particles) 
{
    for(int i = 0; i < AMOUNT; i++)
    {
        (columns + (particles + i)->x / (2 * RADIUS))->push(particles + i);
        (particles + i)->wall();
    }
    for(int i = 0; i < COLUMNS; i++) 
    {
        (columns + i)->collisions();
        (columns + i)->clear();
    }
    for (int i = 0; i < AMOUNT; i++) {
        (particles + i)->motion();
    }
}

template<typename T>
void run_simulation(Column *columns, Particle *particles, T period)
{
    create_gas<T>(columns, particles);
    for(time = 0; time < period; time += DELTA)
    {
        iteration<T>(columns, particles);
    }
    T v, sum = 0;
    for(int i = 0; i < AMOUNT; i++)
    {
        v = pow((particles + i)->get_vx(), 2) +
            pow((particles + i)->get_vy(), 2);
        std::cout << pow(v, 0.5) << std::endl;
        sum += v;
    }
    std::cout << "Mean: " << sum / AMOUNT << std::endl;
}

// ......main......
int main() {
    Column *columns = new Column [COLUMNS];
    Particle *particles = new Particle [AMOUNT];
    run_simulation<float>(columns, particles);
    return 0;
}

