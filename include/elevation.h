/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** elevation
*/

#ifndef ELEVATION_H_
    #define ELEVATION_H_

    #include "struct_client.h"

/**
* @file elevation.h
* @brief File for elevation functions
*/

/**
 * @struct elevation_requirements_s
 * @brief Structure for the elevation requirements
 */
typedef struct elevation_requirements_s {
    int nb_players;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} elevation_requirements_t;

/**
 * @brief Function to check if the incantation is possible
 * @param client_t *cli the client
 * @param int flag the flag to send notice to GUI
 * @return int 1 if the incantation is possible, 0 otherwise
 */
int check_condition_incantation(client_t *cli, int flag);

/**
 * @brief Function to set the incantation boolean
 * @param int level the level of the incantation
 * @param int x the x coordinate
 * @param int y the y coordinate
 * @return nothing
 */
void set_bool_incantation(int level, int x, int y);

/**
 * @brief Function to get the items on a tile
 * @param int x the x coordinate
 * @param int y the y coordinate
 * @param elevation_requirements_t *elevation_tab the elevation requirements
 * @return nothing
 */
void get_items_on_tile(int x, int y, elevation_requirements_t *elevation_tab);

/**
 * @brief Function to compare the structs
 * @param elevation_requirements_t *elevation_tab the elevation requirements
 * @param int level the level
 * @return int 1 if the structs are the same, 0 otherwise
 */
bool compare_structs(elevation_requirements_t *elevation_tab, int level);

/**
 * @brief Function to check the level of the players
 * @param client_t *s the client
 * @param int level the level
 * @param int nb the number of players
 * @param int flag the flag to send notice to GUI
 * @return int 1 if the level is correct, 0 otherwise
 */
bool check_level_players(client_t *s, int level, int nb, int flag);

/**
 * @brief Function to fill struct that will be compared later
 * @param elevation_requirements_t *lvl_tab the struct to fill
 * @param item_type_t type the type of the item
 * @return nothing
 */
void increment_item(elevation_requirements_t *lvl_tab, item_type_t type);

/**
 * @brief Function to create a new tab that will containt clients ids
 * @param int **tab the tab to fill
 * @param int cpt the counter
 * @param int *nb the number of players
 * @return int 1 if the tab is created, 0 otherwise
 */
int create_new_tab(int **tab, int cpt, int *nb);

/**
 * @brief Function to fill the tab
 * @param int **tab the tab to fill
 * @param int *nb the number of players
 * @param client_t *s the client
 * @param int cpt the counter
 * @return int 1 if the tab is filled, 0 otherwise
 */
int fill_tab(int **tab, int *nb, client_t *s, int cpt);

extern const elevation_requirements_t elevation_table[];

#endif /* !ELEVATION_H_ */
