#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>

#include <iostream>
#include <sstream>

#include "game_object.h"

using namespace std;

// Constants for game configuration
const float FPS = 30;                                        // Frames per second
const int SCREEN_W = 800;                                    // Screen width in pixels
const int SCREEN_H = 600;                                    // Screen height in pixels
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);  // Background color (black)
const string FONT_FILEPATH = "assets/arial.ttf";             // Path to the font file

int main(int argc, char **argv) {
    // Pointers for Allegro components
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    // Initialize Allegro library
    if (!al_init()) {
        cout << "ERROR:" << "failed to initialize allegro" << endl;
        return -1;
    }

    // Initialize Allegro primitives addon
    if (!al_init_primitives_addon()) {
        cout << "ERROR:" << "failed to initialize allegro primitives" << endl;
        return -1;
    }

    // Initialize Allegro font and TTF addons
    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        cout << "ERROR:" << "failed to initialize fonts" << endl;
        al_destroy_timer(timer);
        return -1;
    }

    // Load the font from the specified file
    ALLEGRO_FONT *font_arial = al_load_font(FONT_FILEPATH.c_str(), 32, 0);
    if (font_arial == nullptr) {
        cout << "ERROR:" << "failed to load font" << endl;
        return -1;
    }

    // Create an event queue to handle events
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "ERROR:" << "failed to create event_queue" << endl;
        return -1;
    }

    // Install keyboard input support
    if (!al_install_keyboard()) {
        cout << "ERROR:" << "failed to initialize keyboard" << endl;
        return -1;
    }

    // Create the display window
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        cout << "ERROR:" << "failed to create display" << endl;
        return -1;
    }

    // Create a timer to control the game loop
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cout << "ERROR:" << "failed to initialize timer" << endl;
        al_destroy_display(display);
        return -1;
    }

    // Register event sources for the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Start the timer to control game speed
    al_start_timer(timer);

    // Main game loop
    bool playing = true;
    GameObject ball = GameObject(100, 10, SCREEN_W, SCREEN_H);  // Initialize the game object (ball)
    while (playing) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);  // Wait for an event to occur

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Timer event: update and redraw the game state
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));  // Clear the screen with white color

            // Display elapsed time in seconds
            al_draw_textf(font_arial,
                          al_map_rgb(255, 0, 255),
                          SCREEN_W - 80,
                          20,
                          ALLEGRO_ALIGN_CENTRE,
                          "%d seconds",
                          (int)(al_get_timer_count(timer) / FPS));

            // Display the number of hits
            al_draw_textf(font_arial,
                          al_map_rgb(255, 0, 255),
                          SCREEN_W - 80,
                          50,
                          ALLEGRO_ALIGN_CENTRE,
                          "%u hits",
                          ball.getCounter());

            // Log elapsed time to the console every second
            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            ball.updatePositionByGravity();  // Update the ball's position
            ball.draw();                     // Draw the ball

            al_flip_display();  // Update the display with the new frame
        }
        // Handle key press events
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was pressed" << endl;
                    ball.doSomething();  // Perform an action when space is pressed
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    playing = false;  // Exit the game when escape is pressed
                    break;
            }
        }
        // Handle key release events
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was released" << endl;
                    break;
            }
        }
        // Handle window close event
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            playing = false;  // Exit the game when the window is closed
        }
    }

    // Cleanup resources
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}