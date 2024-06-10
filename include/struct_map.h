/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct_map.h
*/

#ifndef STRUCT_MAP_H_
    #define STRUCT_MAP_H_
/**
* @file my.h
* @brief defines data structures used in the project for the map
*/
/**
* @enum items_type_t
* @brief enum that holds all the items type
*/
typedef enum item_type_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG,
    PLAYER,
    MAX_ITEMS
} item_type_t;

/**
* @struct items_t
* @brief struct that holds the items
*/
typedef struct items_s {
    item_type_t type;
    struct items_s *next;
} items_t;

/**
* @struct tile_t
* @brief struct that holds the tile
*/
typedef struct tile_s {
    int x;
    int y;
    items_t *items;
} tile_t;

/**
* @struct map_t
* @brief struct that holds the map
*/
typedef struct map_s {
    int width;
    int height;
    tile_t **tiles;
    void (*display)(struct map_s *map);
} map_t;

#endif /* !STRUCT_MAP_H_ */
