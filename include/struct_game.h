/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct_game.h
*/

#ifndef STRUCT_GAME_H_
    #define STRUCT_GAME_H_
/**
* @file struct_game.h
* @brief defines data structures used in the project for the game
*/

#define DENSITY_FOOD 0.5
#define DENSITY_LINEMATE 0.3
#define DENSITY_DERAUMERE 0.15
#define DENSITY_SIBUR 0.1
#define DENSITY_MENDIANE 0.1
#define DENSITY_PHIRAS 0.08
#define DENSITY_THYSTAME 0.05

typedef struct game_s {
    int width;
    int height;
    int freq;
    int cycle;
} game_t;

#endif /* !STRUCT_GAME_H_ */