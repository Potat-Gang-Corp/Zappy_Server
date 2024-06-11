/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** main
*/
#include "../include/my.h"
#include "../include/handle_flags.h"
#include "../include/struct_map.h"
#include "struct_server.h"
#include "get_instance.h"
#include "server.h"

/**
* @file main.c
* @brief just brief main
*/
int main(int argc, char **argv)
{
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();

    if (handle_flags(argc, argv) == 84) {
        fprintf(stderr, "Error: In the flags can't launch server\n");
        return 84;
    }
    if (init_server() == 84) {
        fprintf(stderr, "Error: In the server can't launch server\n");
        return 84;
    }
    if (initialize_map(game->width, game->height) == 84) {
        fprintf(stderr, "Error: In the initialize_map can't launch server\n");
        return 84;
    }
    if (run_server() == 84) {
        fprintf(stderr, "Error: In the run_server can't launch server\n");
        return 84;
    }
    return 0;
}
