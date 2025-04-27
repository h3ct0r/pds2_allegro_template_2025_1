#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>

#include <iostream>
#include <sstream>

#include "game_object.h"

using namespace std;

const float FPS = 30;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(0, 0, 0);
const string FONT_FILEPATH = "assets/arial.ttf";

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    // Initialization routines
    if (!al_init()) {
        cout << "ERROR:" << "failed to initialize allegro" << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cout << "ERROR:" << "failed to initialize allegro primitives" << endl;
        return -1;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        cout << "ERROR:" << "failed to initialize fonts" << endl;
        al_destroy_timer(timer);
        return -1;
    }

    // load the font type arial.ttf with size of 32 pixels
    ALLEGRO_FONT *font_arial = al_load_font(FONT_FILEPATH.c_str(), 32, 0);
    if (font_arial == nullptr) {
        cout << "ERROR:" << "failed to load font" << endl;
        return -1;
    }

    // create event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "ERROR:" << "failed to create event_queue" << endl;
        return -1;
    }

    if (!al_install_keyboard()) {
        cout << "ERROR:" << "failed to initialize keyboard" << endl;
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        cout << "ERROR:" << "failed to create display" << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cout << "ERROR:" << "failed to initialize timer" << endl;
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // start timer: important to keep the game speed controlled
    al_start_timer(timer);

    bool playing = true;
    GameObject ball = GameObject(100, 10, SCREEN_W, SCREEN_H);
    while (playing) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // draw scenario
            // al_clear_to_color(BACKGROUND_COLOR);
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));

            al_draw_textf(font_arial,
                          al_map_rgb(255, 0, 255),
                          SCREEN_W - 80,
                          20,
                          ALLEGRO_ALIGN_CENTRE,
                          "%d seconds",
                          (int)(al_get_timer_count(timer) / FPS));

            al_draw_textf(font_arial,
                          al_map_rgb(255, 0, 255),
                          SCREEN_W - 80,
                          50,
                          ALLEGRO_ALIGN_CENTRE,
                          "%u hits",
                          ball.getCounter());

            if (al_get_timer_count(timer) % (int)FPS == 0) {
                cout << al_get_timer_count(timer) / FPS << " second..." << endl;
            }

            ball.updatePositionByGravity();
            ball.draw();

            // draw the screen
            al_flip_display();
        }
        // pressed keys event
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was pressed" << endl;
                    ball.doSomething();
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    playing = false;
                    break;
            }
        }
        // released keys event
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    cout << "space key was released" << endl;
                    break;
            }

        }
        // if the event was to close the game window (using the x button)
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            playing = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}