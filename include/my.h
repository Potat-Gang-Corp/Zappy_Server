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
int initialize_map(int width, int height);
void display(struct map_s *map);

int place_mendiane_on_map(map_t *map);
int place_sibur_on_map(map_t *map);
int place_deraumere_on_map(map_t *map);
int place_linemate_on_map(map_t *map);
int place_food_on_map(map_t *map);

int place_phiras_on_map(map_t *map);
int place_thystame_on_map(map_t *map);

const char *get_north_pos(void);
const char *get_east_pos(void);
const char *get_south_pos(void);
const char *get_south_pos(void);
void player_spawn(client_t *cli);

#endif /* !MY_H_ */
