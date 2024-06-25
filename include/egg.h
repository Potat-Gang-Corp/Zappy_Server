/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map
*/

#ifndef EGG_H
    #define EGG_H
/**
 * @brief Handling the display of eggs
 * @param team_index Index of the team
 * @param map Map structure where eggs will be placed
 *
 * @details this function will place the eggs on the map
 * @return nothing.
 */
void place_egg_on_map_bis(int team_index, map_t *map);

/**
 * @brief Function to handle the add of egg in the linked list
 * @param team Pointer to the team structure
 * @param x X-coordinate where the egg will be placed
 * @param y Y-coordinate where the egg will be placed
 * @param egg_id ID of the egg to be added
 *
 * @details will add the egg into the linked list
 * @return nothing.
 */
void add_egg_to_team_ll(team_t *team, int x, int y, int egg_id);

/**
 * @brief Function to handle egg laying
 *
 * @details will handle and make sure the eggs are well laid
 * @return nothing.
 */
void handle_egg_laying(void);

/**
 * @brief Function to handle the left command
 * @param egg Pointer to the egg structure
 * @param x X-coordinate where the egg is located
 * @param y Y-coordinate where the egg is located
 *
 * @details will handle the destruction of eggs
 * @return nothing.
 */
void destroy_eggs(egg_t *egg, int x, int y);

/**
 * @brief Function that deletes the eggs
 * @param egg Pointer to the current egg structure
 * @param prev_egg Pointer to the previous egg structure in the list
 * @param curr_egg Pointer to the current egg structure in the list
 *
 * @details will handle deleting all the eggs of the list
 * @return nothing.
 */
void delete_egg(egg_t **egg, egg_t **prev_egg, egg_t **curr_egg);

#endif //EGG_H
