/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
/**
* @file my.h
* @brief defines the prototypes of the functions used in the project
* as well as the includes of the libs needed
*/
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <sys/socket.h>
    #include <sys/queue.h>
    #include <sys/select.h>
    #include <sys/types.h>
    #include "struct_map.h"
    #include <errno.h>
    #include <stdio.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <time.h>
    #include "struct_game.h"
    #include "struct_client.h"
    #include "struct_server.h"
    #include "struct_map.h"

int add_func(int a, int b);
void second_init_map(map_t *map, int x, int y, int width);
void init_map(map_t *map, int width, int height);
map_t *initialize_map(int width, int height);
void display(struct map_s *map);
void display_suite(items_t *item);

//add_item_to_map.c
const char *get_items(item_type_t item);
void display_item(items_t *item);
void place_randomly_items(map_t *map);
void add_item_to_tiles(tile_t *tile, item_type_t type);

//items
const char *get_food(void);
const char *get_linemate(void);
const char *get_deraumere(void);
const char *get_sibur(void);
const char *get_mendiane(void);

//items_bis
const char *get_phiras(void);
const char *get_thystame(void);
const char *get_egg(void);
const char *get_player(void);
const char *get_unknown(void);

#endif /* !MY_H_ */
