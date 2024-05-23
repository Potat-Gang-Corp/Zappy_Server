/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_x_y
*/

#include "../../include/my.h"
#include "../../include/handle_flags.h"
#include "../../include/get_instance.h"

/**
* @file handle_p_x_y.c
* @brief handle the p, x and y flags
*/
void handle_p(char *av)
{
    int port;
    server_t *server = get_instance();

    port = atoi(av);
    if (port < 1 || port > 65535) {
        fprintf(stderr, "Error: port number must be between 1 and 65535\n");
        exit(84);
    }
    server->port = port;
    printf("port: %d\n", server->port);
}

void handle_x(char *av)
{
    int x = atoi(av);
    game_t *game = get_game_instance();

    if (x <= 0) {
        printf("Error: width should be greater than 0\n");
        exit(84);
    }
    game->width = x;
    printf("width: %d\n", game->width);
}

void handle_y(char *av)
{
    int y = atoi(av);
    game_t *game = get_game_instance();

    if (y <= 0) {
        printf("Error: height should be greater than 0\n");
        exit(84);
    }
    game->height = y;
    printf("height: %d\n", game->height);
    return;
}

void handle_x_y(int ac, int *i, char **av, int *fp)
{
    if (strcmp(av[(*i)], "-x") == 0) {
            check_av((*i), ac, av);
            handle_x(av[(*i) + 1]);
            (*fp) |= 1 << 1;
            if ((*i) + 1 >= ac)
                exit(84);
    }
    if (strcmp(av[(*i)], "-y") == 0) {
        check_av((*i), ac, av);
        handle_y(av[(*i) + 1]);
        (*fp) |= 1 << 2;
        if ((*i) + 1 >= ac)
            exit(84);
    }
}
