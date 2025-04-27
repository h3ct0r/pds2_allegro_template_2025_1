#include "game_object.h"

GameObject::GameObject(double x, double y, int screen_w, int screen_h) {
    this->x = x;
    this->y = y;
    this->screen_w = screen_w;
    this->screen_h = screen_h;
}

void GameObject::doSomething() {
    this->y -= 100;
}

int GameObject::getCounter() {
    return this->angry_counter;
}

bool GameObject::updatePosition(double x, double y) {
    this->x = x;
    this->y = y;

    return true;
}

bool GameObject::updatePositionByGravity() {
    if (this->y < this->screen_h - this->radius) {
        this->updatePosition(this->x, this->y + 10);
        this->current_state = NORMAL;
        return true;
    }

    // if previous state was normal
    // means that this object just hit something
    if (this->current_state == NORMAL) {
        this->angry_counter++;
    }

    this->current_state = ANGRY;
    return false;
}

void GameObject::draw() {
    // body
    al_draw_filled_circle(this->x, this->y, this->radius, this->OBJ_COLOR);

    // left eye
    al_draw_filled_circle(this->x - 10, this->y - 10, 10, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(this->x - 10, this->y - 10, 4, al_map_rgb(0, 0, 0));
    // right eye
    al_draw_filled_circle(this->x + 20, this->y - 10, 10, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(this->x + 20, this->y - 10, 4, al_map_rgb(0, 0, 0));

    if (this->current_state == ANGRY) {
        al_draw_line(this->x - 15, this->y - 20, this->x + 5, this->y - 10, al_map_rgb(0, 0, 0), 6);
        al_draw_line(this->x + 25, this->y - 20, this->x + 10, this->y - 10, al_map_rgb(0, 0, 0), 6);

        al_draw_filled_rounded_rectangle(this->x - 15, this->y + 15, this->x + 23, this->y + 25, 3, 3, al_map_rgb(255, 255, 255));
    } else {
        al_draw_filled_circle(this->x + 5, this->y + 25, 12, al_map_rgb(255, 255, 255));
    }
}
