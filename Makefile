all: main

src/game_object.o: include/game_object.h src/game_object.cpp
	g++ -o src/game_object.o -c src/game_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

src/main.o: src/main.cpp
	g++ -o src/main.o -c src/main.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

main: src/main.o src/game_object.o
	g++ src/main.o src/game_object.o -o main `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`