#include <iostream>
#include <cmath>

using namespace std;

// ......const values......
const float delta = 0.001;
const int a = 10, r = 1, v_mean = 1;

// ......forward declaration......
struct Cell;
struct Particle;
void create(Cell **cell_p, Particle **part_p);
void iteration(Cell **cell_p, Particle **part_p);

// ......main......
int main() {
    Cell **cell_p = new Cell *[a * a];
    Particle **part_p = new Particle *[a * a];
    create(cell_p, part_p, a, v_mean);
    iteration(cell_p, part_p, a, delta);
}

// ......structures.......
struct Cell {
    Particle **inner;
    Particle **outer;
    Cell() {
        inner = new Particle *[0];
        outer = new Particle *[0];
    }
};

struct Particle {
    int index;
    float x;
    float y;
    float vx;
    float vy;
    Particle(int i, float val_x, float val_y, float val_vx, float val_vy) {
        index = i;
        x = val_x;
        y = val_y;
        vx = val_vx;
        vy = val_vy;
    }
    
};

// ......functions......
void create(Cell **cell_p, Particle **part_p) {
    float x, y, vx, vy;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-v_mean, v_mean);
    for (int i = 0; i < a * a; i++) {
        Cell *p = new Cell();
        cell_p[i] = p;
        x = 10 * (1 + i % a) - 5;
        y = 10 * (1 + i / a) - 5;
        vx = dist(gen);
        vy = pow(v_mean * v_mean - vx * vx, 0.5);
        Particle *p = new Particle(i, x, y, vx, vy);
        part_p[i] = p;
    }
}

void iteration(Cell **cell_p, Particle **part_p) {
    int cell_index;
    for (int i = 0; i < a * a; i++) {
        cell_index = floor(x / 10) + a * floor(y / 10);
        cell_p[cell_index] 
    }
}

