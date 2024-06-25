/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "struct_map.h"

/**
 * @brief delete item from tiles
 * @param team_index Index of the team
 * @param map Map structure where eggs will be placed
 *
 * @details this function will place the eggs on the map
 * @return nothing.
 */
void delete_item_from_tiles(tile_t *tile, item_type_t type);
/**
 * @brief checking item existence
 * @param item Pointer to the item structure
 * @param type Type of the item
 *
 * @details this function will check if the item exists
 * @return 1 if the item exists, 0 otherwise.
 */
int checking_item_existence(items_t *item, item_type_t type);
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
 * @brief handle initial map
 * @param map Pointer to the map structure
 * @param x X-coordinate where the map will be placed
 * @param y Y-coordinate where the map will be placed
 * @param width Width of the map
 * 
 * @details this function will initialize the map
 * @return nothing.
 */
void second_init_map(map_t *map, int x, int y, int width);
/**
 * @brief initialize map
 * @param map Pointer to the map structure
 * @param width Width of the map
 * @param height Height of the map
 *
 * @details this function will initialize the map
 * @return 1 if the map is initialized, 0 otherwise.
 */

void init_map(map_t *map, int width, int height);
/**
 *@brief initialize map
 *@param width Width of the map
 *@param height Height of the map
 *
 *@details this function will initialize the map
 *@return 1 if the map is initialized, 0 otherwise.
*/
int initialize_map(int width, int height);

/**
 *@brief place mendiane on map
 *@param map Pointer to the map structure
 *
 * @details this function will place mendiane on the map
 * @return 1 if mendiane is placed, 0 otherwise.
*/
int place_mendiane_on_map(map_t *map);
/**
 *@brief place sibur on map
 *@param map Pointer to the map structure
 *
 * @details this function will place sibur on the map
 * @return 1 if sibur is placed, 0 otherwise.
*/
int place_sibur_on_map(map_t *map);
/**
 *@brief place deraumere on map
 *@param map Pointer to the map structure
 *
 * @details this function will place deraumere on the map
 * @return 1 if deraumere is placed, 0 otherwise.
*/
int place_deraumere_on_map(map_t *map);
/**
 *@brief place linemate on map
 *@param map Pointer to the map structure
 *
 * @details this function will place linemate on the map
 * @return 1 if linemate is placed, 0 otherwise.
*/
int place_linemate_on_map(map_t *map);
/**
 *@brief place food on map
 *@param map Pointer to the map structure
 *
 * @details this function will place food on the map
 * @return 1 if food is placed, 0 otherwise.
*/
int place_food_on_map(map_t *map);
/**
 *@brief place phiras on map
 *@param map Pointer to the map structure
 *
 * @details this function will place phiras on the map
 * @return 1 if phiras is placed, 0 otherwise.
*/
int place_phiras_on_map(map_t *map);
/**
 *@brief place thystame on map
 *@param map Pointer to the map structure
 *
 * @details this function will place thystame on the map
 * @return 1 if thystame is placed, 0 otherwise.
*/
int place_thystame_on_map(map_t *map);

const char *get_food(void);
const char *get_linemate(void);
const char *get_deraumere(void);
const char *get_sibur(void);
const char *get_mendiane(void);
const char *get_phiras(void);
const char *get_thystame(void);
const char *get_egg(void);
const char *get_player(void);
const char *get_unknown(void);

/**
 *@brief add item to tiles
 *@param tile Pointer to the tile structure
 *@param type Type of the item
 *
 * @details this function will add the item to the tiles
 * @return nothing.
*/
void add_item_to_tiles(tile_t *tile, item_type_t type);
/**
 *@brief place randomly items
 *@param map Pointer to the map structure
 *
 * @details this function will place randomly items on the map
 * @return nothing.
*/
void place_randomly_items(map_t *map);
/**
 *@brief place randomly items
 *@param map Pointer to the map structure
 *
 * @details this function will place randomly items on the map
 * @return nothing.
*/
const char *get_items(item_type_t item);
/**
 *@brief get item type
 *@param item_name Name of the item
 *
 * @details this function will get the item type
 * @return item type.
*/
item_type_t get_item_type(const char *item_name);
/**
 *@brief get item type
 *@param item_name Name of the item
 *
 * @details this function will get the item type
 * @return item type.
*/
void delete_item_from_tiles(tile_t *tile, item_type_t type);
/**
 *@brief delete item from tiles
 *@param tile Pointer to the tile structure
 *@param type Type of the item
 *
 * @details this function will delete the item from the tiles
 * @return nothing.
*/
int checking_item_existence(items_t *item, item_type_t type);
/**
 *@brief checking item existence
 *@param item Pointer to the items structure
 *@param type Type of the item
 *
 * @details this function will check if the item exists
 * @return 1 if the item exists, 0 otherwise.
*/
void handle_renew_items(void);
/**
 *@brief handle renew items
 *
 * @details this function will handle the renew of the items
 * @return nothing.
*/
void refill_deraumere(map_t *map, int *counter_items);
/**
 *@brief refill deraumere
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill deraumere
 * @return nothing.
*/
void refill_linemate(map_t *map, int *counter_items);
/**
 *@brief refill linemate
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill linemate
 * @return nothing.
*/
void refill_food(map_t *map, int *counter_items);
/**
 *@brief refill food
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill food
 * @return nothing.
*/
void count_items_on_map(int *counter_items, tile_t *tile);
/**
 *@brief count items on map
 *@param counter_items Counter of the items
 *@param tile Pointer to the tile structure
 *
 * @details this function will count the items on the map
 * @return nothing.
*/
void refill_mendiane(map_t *map, int *counter_items);
/**
 *@brief refill mendiane
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill mendiane
 * @return nothing.
*/
void refill_phiras(map_t *map, int *counter_items);
/**
 *@brief refill phiras
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill phiras
 * @return nothing.
*/
void refill_thystame(map_t *map, int *counter_items);
/**
 *@brief refill thystame
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill thystame
 * @return nothing.
*/
void handle_renew_items_bis(map_t *map, int *counter_items);
/**
 *@brief handle renew items bis
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will handle the renew of the items
 * @return nothing.
*/
void refill_sibur(map_t *map, int *counter_items);
/**
 *@brief refill sibur
 *@param map Pointer to the map structure
 *@param counter_items Counter of the items
 *
 * @details this function will refill sibur
 * @return nothing.
*/
void push_players_to_tile(client_t *cli, int x, int y);
/**
 *@brief push players to tile
 *@param cli Pointer to the client structure
 *@param x X position
 *@param y Y position
 *
 * @details this function will push the players to the tile
 * @return nothing.
*/

#endif /* !MAP_H_ */
