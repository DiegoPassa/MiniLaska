all: main.c src/colors/colors.c src/game_engine/game_engine.c src/ia/ia.c src/memory_management/memory_management.c src/movement/movement.c src/user_interaction/user_interaction.c
	gcc main.c src/colors/colors.c src/game_engine/game_engine.c src/ia/ia.c src/memory_management/memory_management.c src/movement/movement.c src/user_interaction/user_interaction.c -o laska.exe -ansi -pedantic -Wall -lm