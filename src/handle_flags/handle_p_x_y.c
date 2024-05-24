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
int handle_p(char *av)
{
    int port;
    server_t *server = get_instance();

    port = atoi(av);
    if (port < 1 || port > 65535) {
        fprintf(stderr, "Error: port number must be between 1 and 65535\n");
        return 84;
    }
    server->port = port;
    return 0;
}

int handle_x(char *av)
{
    int x = atoi(av);
    game_t *game = get_game_instance();

    if (x <= 0) {
        fprintf(stderr, "Error: width should be greater than 0\n");
        return 84;
    }
    game->width = x;
    return 0;
}

int handle_y(char *av)
{
    int y = atoi(av);
    game_t *game = get_game_instance();

    if (y <= 0) {
        fprintf(stderr, "Error: height should be greater than 0\n");
        return 84;
    }
    game->height = y;
    return 0;
}

int handle_x_y(int ac, int *i, char **av, int *fp)
{
    if (strcmp(av[(*i)], "-x") == 0) {
            check_av((*i), ac, av);
            handle_x(av[(*i) + 1]);
            (*fp) |= 1 << 1;
            if ((*i) + 1 >= ac)
                return 84;
    }
    if (strcmp(av[(*i)], "-y") == 0) {
        check_av((*i), ac, av);
        handle_y(av[(*i) + 1]);
        (*fp) |= 1 << 2;
        if ((*i) + 1 >= ac)
            return 84;
    }
    return 0;
}
