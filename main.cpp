#include <iostream>
#include <cmath>
#include <random>

// ......const values......
const float delta = 0.001;
const int a = 10, r = 1, v_mean = 1;

// ......functions and structures......
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
    void wall() {
        if (x <= r or x >= 10 * a - r) {
            vx = -vx;
        }
        if (y <= r or y >= 10 * a - r) {
            vy = -vy;
        }
    }
    void motion() {
        x += vx * delta;
        y += vy * delta;
    }
};

void calc_coll(Particle *p, Particle *m) {
    float xp = p->x, yp = p->y, vxp = p->vx, vyp = p->vy;
    float xm = m->x, ym = m->y, vxm = m->vx, vym = m->vy;
    float cs = (xm - xp) / (2 * r), sn = (ym - yp) / (2 * r);
    p->vx = vxp * sn * sn + vxm * cs * cs + (vym - vyp) * cs * sn;
    p->vy = vyp * cs * cs + vym * sn * sn + (vxm - vxp) * cs * sn;
    m->vx = vxm * sn * sn + vxp * cs * cs + (vyp - vym) * cs * sn;
    m->vy = vym * cs * cs + vyp * sn * sn + (vxp - vxm) * cs * sn;
}

struct Cell {
    int inner_size;
    int outer_size;
    Particle **inner;
    Particle **outer;
    Cell() {
        inner_size = 0;
        outer_size = 0;
        inner = new Particle *[0];
        outer = new Particle *[0];
    }
    void clear() {
        inner_size = 0;
        outer_size = 0;
        delete [] inner;
        delete [] outer;
        inner = new Particle *[0];
        outer = new Particle *[0];
    }
    void push_inner(Particle *p) {
        Particle **temp = new Particle *[inner_size + 1];
        for (int i = 0; i < inner_size; i++) {
            temp[i] = inner[i];
        }
        temp[inner_size] = p;
        delete [] inner;
        inner = temp;
        inner_size++;
    }
    void push_outer(Particle *p) {
        Particle **temp = new Particle *[outer_size + 1];
        for (int i = 0; i < outer_size; i++) {
            temp[i] = outer[i];
        }
        temp[outer_size] = p;
        delete [] outer;
        outer = temp;
        outer_size++;
    }
    bool intersect(int i, int j) {
        float dx, dy;
        dx = inner[j]->x - inner[i]->x;
        dy = inner[j]->y - inner[i]->y;
        return dx * dx + dy * dy <= r * r;
    }
    void colission() {
        for (int i = 0; i < inner_size; i++) {
            for (int j = i + 1; j < inner_size; j++) {
                if (intersect(i, j)) {
                    calc_coll(inner[i], inner[j]);
                }
            }
            for (int j = 0; j < outer_size; j++) {
                if (intersect(i, j) and inner[i]->index < outer[j]->index) {
                    calc_coll(inner[i], inner[j]);
                }
            }
        }
    }
};

void create(Cell **cell_p, Particle **part_p) {
    float x, y, vx, vy;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-v_mean, v_mean);
    for (int i = 0; i < a * a; i++) {
        Cell *p = new Cell();
        cell_p[i] = p;
        x = 10 * (1 + i % a) - 5;
        y = 10 * (1 + i / a) - 5;
        vx = dist(gen);
        vy = pow(v_mean * v_mean - vx * vx, 0.5);
        Particle *q = new Particle(i, x, y, vx, vy);
        part_p[i] = q;
    }
}

void inner_outer(Cell **cell_p, Particle *p) {
    int cell_inner, cell_outer;
    float x = p->x, y = p->y, x0, y0;
    cell_inner = floor(x / 10) + a * floor(y / 10);
    (*cell_p[cell_inner]).push_inner(p);
    x0 = 10 * (cell_inner % a);
    y0 = 10 * (cell_inner / a);
    if (x <= x0 + r) {
        cell_outer = cell_inner - 1;
        if (cell_outer >= 0) (*cell_p[cell_outer]).push_outer(p);
    } else if (x >= x0 + 10 - r) {
        cell_outer = cell_inner + 1;
        if (cell_outer <= a * a) (*cell_p[cell_outer]).push_outer(p);
    }
    if (y <= y0 + r) {
        cell_outer = cell_inner - a;
        if (cell_outer >= 0) (*cell_p[cell_outer]).push_outer(p);
    } else if (y >= y0 + 10 - r) {
        cell_outer = cell_inner + a;
        if (cell_outer <= a * a) (*cell_p[cell_outer]).push_outer(p);
    }
    
    if (pow(x - x0, 2) + pow(y - y0, 2) <= r * r) {
        cell_outer = cell_inner - a - 1;
        if (cell_outer >= 0) (*cell_p[cell_outer]).push_outer(p);
    } else if (pow(x - x0, 2) + pow(y - y0 - 10, 2) <= r * r) {
        cell_outer = cell_inner + a - 1;
        if (cell_outer <= a * a) (*cell_p[cell_outer]).push_outer(p);
    } else if (pow(x - x0 - 10, 2) + pow(y - y0 - 10, 2) <= r * r) {
        cell_outer = cell_inner + a + 1;
        if (cell_outer <= a * a) (*cell_p[cell_outer]).push_outer(p);
    } else if (pow(x - x0 - 10, 2) + pow(y - y0, 2) <= r * r) {
        cell_outer = cell_inner - a + 1;
        if (cell_outer >= 0) (*cell_p[cell_outer]).push_outer(p);
    }
}

void iteration(Cell **cell_p, Particle **part_p) {
    for (int i = 0; i < a * a; i++) {
        inner_outer(cell_p, part_p[i]);
    }
    for (int i = 0; i < a * a; i++) {
        (*cell_p[i]).colission();
    }
    for (int i = 0; i < a * a; i++) {
        (*part_p[i]).wall();
    }
    for (int i = 0; i < a * a; i++) {
        (*part_p[i]).motion();
    }
    for (int i = 0; i < a * a; i++) {
        (*cell_p[i]).clear();
    }
}

// ......main......
int main() {
    Cell **cell_p = new Cell *[a * a];
    Particle **part_p = new Particle *[a * a];
    create(cell_p, part_p);
    iteration(cell_p, part_p);
    float t = 0, vx, vy, v;
    while (t < 10) {
        iteration(cell_p, part_p);
        t += delta;
    }
    for (int i = 0; i < a * a; i++) {
        vx = part_p[i]->vx;
        vy = part_p[i]->vy;
        v = pow(vx * vx + vy * vy, 0.5);
        std::cout << v << std::endl;
    }
    return 0;
}

