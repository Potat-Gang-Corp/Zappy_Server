/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** get_instance.c
*/

#include "../../include/my.h"
#include "../../include/struct_server.h"
#include "../../include/struct_map.h"
#include "../../include/struct_client.h"
#include "../../include/struct_game.h"

server_t *get_instance(void)
{
    static server_t server;

    return &server;
}

map_t *get_map_instance(void)
{
    static map_t map;

    return &map;
}

game_t *get_game_instance(void)
{
    static game_t game;

    return &game;
}
