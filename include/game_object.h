#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

enum object_state {
    NORMAL,
    ANGRY
};

class GameObject {
   public:
    GameObject(double, double, int, int);
    void doSomething();
    bool updatePositionByGravity();
    void draw();
    int getCounter();

   private:
    const ALLEGRO_COLOR OBJ_COLOR = al_map_rgb(10, 200, 20);
    const double radius = 50;

    int screen_w, screen_h;
    double x, y;
    object_state current_state = NORMAL;
    int angry_counter = 0;

    bool updatePosition(double, double);
};

#endif