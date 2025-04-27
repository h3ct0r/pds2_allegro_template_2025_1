CC=g++
CFLAGS=-std=c++11 -Wall
SRC_DIR=src
INCLUDE_DIR=include
ALLEGRO_INCLUDE_DIR=/opt/homebrew/Cellar/allegro/5.2.10.1_1/include
OBJ_DIR=build

all: main

$(OBJ_DIR)/game_object.o: $(INCLUDE_DIR)/game_object.h $(SRC_DIR)/game_object.cpp
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/game_object.o -c $(SRC_DIR)/game_object.cpp  -I$(INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/main.o -c $(SRC_DIR)/main.cpp  -I$(INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR)

main: $(OBJ_DIR)/main.o $(OBJ_DIR)/game_object.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/game_object.o -o main `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`

clean:
	rm -f main $(OBJ_DIR)/*.o