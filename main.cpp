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
    int size;
    Particle **inner;
    Cell() {
        size = 0;
        inner = new Particle *[0];
    }
    void clear() {
        delete [] inner;
        inner = new Particle *[0];
        size = 0;
    }
    void push(Particle *p) {
        Particle **temp = new Particle *[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = inner[i];
        }
        temp[size] = p;
        delete [] inner;
        inner = temp;
        size++;
    }
    bool intersect(int i, int j) {
        float dx, dy;
        dx = inner[j]->x - inner[i]->x;
        dy = inner[j]->y - inner[i]->y;
        return dx * dx + dy * dy <= r * r;
    }
    void colission() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (intersect(i, j)) {
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

void iteration(Cell **cell_p, Particle **part_p) {
    int cell_index;
    float x, y;
    for (int i = 0; i < a * a; i++) {
        x = part_p[i]->x;
        y = part_p[i]->y;
        cell_index = floor(x / 10) + a * floor(y / 10);
        (*cell_p[cell_index]).push(part_p[i]); 
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

