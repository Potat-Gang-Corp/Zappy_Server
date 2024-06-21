/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include "my.h"
/**
* @file my.h
* @brief defines the data structures used in the project for the
* client/player, such as inventory, position, etc.
*/

/**
 * @enum orientation_t
 * @brief enum that holds all the orientation
 */
typedef enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
} orientation_t;

/**
 * @struct struct position_t
 * @brief struct for the position as well as orientation of the player
 */
typedef struct position_s {
    int x;
    int y;
    orientation_t orientation;
} position_t;

/**
* @struct inventory_t
* @brief struct that holds the inventory of the player
*/
typedef struct inventory_s {
    unsigned int food;
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
} inventory_t;

/**
* @struct client_t
* @brief struct that holds the client/player data
*/
typedef struct client_s {
    int socket;
    int id;
    position_t pos;
    char *team;
    bool evolving;
    unsigned int cd;
    inventory_t inventory;
    unsigned int level;
    int time_to_live;
    bool logged;
    int nb_commands;
    bool graphic;
    bool is_laying;
    int egg_id_laying;
    struct client_s *next;
    int cycle;
} client_t;

#endif /* !STRUCT_H_ */
