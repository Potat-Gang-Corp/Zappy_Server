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
    if (handle_flags(argc, argv) == 84) {
        fprintf(stderr, "Error: In the flags can't launch server\n");
        return 84;
    }
    return 0;
}
