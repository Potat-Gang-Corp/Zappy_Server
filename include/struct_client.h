/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_
/**
* @file my.h
* @brief defines the data structures used in the project for the
* client/player, such as inventory, position, etc.
*/
typedef enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct position_s {
    int x;
    int y;
    orientation_t orientation;
} position_t;

typedef struct inventory_s {
    unsigned int food;
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
} inventory_t;

typedef struct client_s {
    int socket;
    position_t pos;
    char *team;
    bool evolving;
    unsigned int cool_down;
    inventory_t inventory;
    unsigned int level;
    int time_to_live;
    bool status;
    int nb_commands;
    struct client_s *next;
} client_t;

#endif /* !STRUCT_H_ */
