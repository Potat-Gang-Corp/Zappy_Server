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
typedef enum item_type_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} item_type_t;

typedef struct items_s {
    item_type_t type;
    struct items_s *next;
} items_t;

typedef struct tile_s {
    int x;
    int y;
    items_t *items;
} tile_t;

typedef struct map_s {
    int width;
    int height;
    tile_t **tiles;
    void (*display)(struct map_s *map);
} map_t;

#endif /* !STRUCT_MAP_H_ */
