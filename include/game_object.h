#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

/**
 * @enum object_state
 * @brief Represents the state of the game object.
 */
enum object_state {
    NORMAL,  ///< The object is in its normal state.
    ANGRY    ///< The object is in its angry state.
};

/**
 * @class GameObject
 * @brief Represents a game object with position, state, and behavior.
 */
class GameObject {
   public:
    GameObject(double x, double y, int screen_w, int screen_h);
    void doSomething();
    bool updatePositionByGravity();
    void draw();
    int getCounter();

   private:
    const ALLEGRO_COLOR OBJ_COLOR = al_map_rgb(10, 200, 20);  ///< The color of the object.
    const double radius = 50;                                 ///< The radius of the object.

    int screen_w;                         ///< The width of the screen (used for boundary checks).
    int screen_h;                         ///< The height of the screen (used for boundary checks).
    double x;                             ///< The x-coordinate of the object.
    double y;                             ///< The y-coordinate of the object.
    object_state current_state = NORMAL;  ///< The current state of the object.
    int angry_counter = 0;                ///< Counter for the number of times the object has been "angry."

    bool updatePosition(double x, double y);
};

#endif