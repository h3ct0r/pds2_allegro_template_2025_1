#include "game_object.h"

/**
 * @class GameObject
 * @brief Represents a game object with position, state, and behavior.
 */

/**
 * @brief Constructs a new GameObject.
 *
 * @param x Initial x-coordinate of the object.
 * @param y Initial y-coordinate of the object.
 * @param screen_w Width of the screen (used for boundary checks).
 * @param screen_h Height of the screen (used for boundary checks).
 */
GameObject::GameObject(double x, double y, int screen_w, int screen_h) {
    this->x = x;
    this->y = y;
    this->screen_w = screen_w;
    this->screen_h = screen_h;
}

/**
 * @brief Performs an action on the object (e.g., moves it upward).
 */
void GameObject::doSomething() {
    this->y -= 100;
}

/**
 * @brief Gets the counter for the number of times the object has been "angry."
 *
 * @return The angry counter value.
 */
int GameObject::getCounter() {
    return this->angry_counter;
}

/**
 * @brief Updates the position of the object.
 *
 * @param x New x-coordinate of the object.
 * @param y New y-coordinate of the object.
 * @return True if the position was updated successfully.
 */
bool GameObject::updatePosition(double x, double y) {
    this->x = x;
    this->y = y;

    return true;
}

/**
 * @brief Updates the object's position based on gravity.
 *
 * @return True if the object is still falling, false if it has hit the ground.
 */
bool GameObject::updatePositionByGravity() {
    if (this->y < this->screen_h - this->radius) {
        this->updatePosition(this->x, this->y + 10);
        this->current_state = NORMAL;
        return true;
    }

    // If the previous state was NORMAL, the object just hit something.
    if (this->current_state == NORMAL) {
        this->angry_counter++;
    }

    this->current_state = ANGRY;
    return false;
}

/**
 * @brief Draws the object on the screen.
 *
 * The object is represented as a circle with eyes and a mouth. The appearance
 * changes based on the object's state (e.g., angry or normal).
 */
void GameObject::draw() {
    // Draw the body
    al_draw_filled_circle(this->x, this->y, this->radius, this->OBJ_COLOR);

    // Draw the left eye
    al_draw_filled_circle(this->x - 10, this->y - 10, 10, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(this->x - 10, this->y - 10, 4, al_map_rgb(0, 0, 0));

    // Draw the right eye
    al_draw_filled_circle(this->x + 20, this->y - 10, 10, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(this->x + 20, this->y - 10, 4, al_map_rgb(0, 0, 0));

    if (this->current_state == ANGRY) {
        // Draw angry eyebrows
        al_draw_line(this->x - 15, this->y - 20, this->x + 5, this->y - 10, al_map_rgb(0, 0, 0), 6);
        al_draw_line(this->x + 25, this->y - 20, this->x + 10, this->y - 10, al_map_rgb(0, 0, 0), 6);

        // Draw angry mouth
        al_draw_filled_rounded_rectangle(this->x - 15, this->y + 15, this->x + 23, this->y + 25, 3, 3, al_map_rgb(255, 255, 255));
    } else {
        // Draw normal mouth
        al_draw_filled_circle(this->x + 5, this->y + 25, 12, al_map_rgb(255, 255, 255));
    }
}