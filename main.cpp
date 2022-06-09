#include <iostream>

struct Cell;
struct Particle;
void create_cells(Cell **cell_pointers, int cell_number);
void create_particles(Particle **particle_pointers, int particle_number);

int main() {
    int cell_number = 100, particle_number = 100;
    Cell **cell_pointers = new Cell *[cell_number];
    create_cells(cell_pointers, cell_number);
    Particle **particle_pointers = new Particle *[particle_number];
    create_particles(particle_pointers, particle_number);
}

struct Cell {
    int x;
    int y;
    Particle **particles;
    Cell(int val_x, int val_y) {
        x = val_x;
        y = val_y;
        particles = new Particle *[0];
    }
};

struct Particle {
    float x;
    float y;
    float vx;
    float vy;
    Cell **cells;
    Particle(float val_x, float val_y, float val_vx, float val_vy) {
        x = val_x;
        y = val_y;
        vx = val_vx;
        vy = val_vy;
        cells = new Cell *[0];
    }
};

void create_cells(Cell **cell_pointers, int cell_number) {
    for (int i = 0; i < cell_number; i++) {
        Cell *p = new Cell()
    }
}

void create_particles(Particle **particle_pointers, int particle_number) {
    
}

