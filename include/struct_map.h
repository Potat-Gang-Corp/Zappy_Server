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

typedef struct items_s {
    char *name;
    struct items_s *next;
} items_t;

typedef struct tile_s {
    int x;
    int y;
    struct items_s *items;
    struct tile_s *next;
} tile_t;

typedef struct map_s {
    int width;
    int height;
    struct tile_s *tiles;
} map_t;

#endif /* !STRUCT_MAP_H_ */