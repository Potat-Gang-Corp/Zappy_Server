/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** main
*/
#include "../include/my.h"
#include "../include/handle_flags.h"
#include "../include/struct_map.h"

/**
* @file main.c
* @brief just brief main
*/
int main(int argc, char **argv)
{
    map_t *map = initialize_map(10, 10);

    handle_flags(argc, argv);
    map->display(map);
    return 0;
}
