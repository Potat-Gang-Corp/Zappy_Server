/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** handle_n_c_f.c
*/

#include "../../include/my.h"
#include "../../include/handle_flags.h"
#include "../../include/get_instance.h"
/**
* @file handle_n_c_f.c
* @brief handle the n, c and f flags
*/
void handle_n(int ac, int *i, char **av, int *fp)
{
    game_t *game = get_game_instance();
    int k;

    game->nb_teams = 0;
    (*fp) |= 1 << 3;
    while (*i + 1 < ac && av[*i + 1][0] != '-') {
        (*i)++;
        game->nb_teams++;
    }
    game->teams = malloc(sizeof(team_t) * (game->nb_teams + 1));
    for (k = 0; k < game->nb_teams; k++) {
        game->teams[k] = malloc(sizeof(team_t));
        game->teams[k]->name = strdup(av[*i + k + 1]);
    }
}

void handle_c(char *av, int *fp)
{
    int nb;
    int i;
    game_t *game = get_game_instance();

    (*fp) |= 1 << 4;
    for (i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            fprintf(stderr, "Error: flag -c has no definition\n");
            exit(84);
        }
    }
    nb = atoi(av);
    if (nb <= 0) {
        fprintf(stderr, "Error: clients per team should be greater than 0\n");
        exit(84);
    }
    for (int i = 0; i < game->nb_teams; i++)
        game->teams[i]->max_clients = nb;
}

void handle_f(char *av, int *fp)
{
    int nb;
    game_t *game = get_game_instance();

    (*fp) |= 1 << 5;
    for (int i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            fprintf(stderr, "Error: flag -f has no definition\n");
            exit(84);
        }
    }
    nb = atoi(av);
    if (nb < 0) {
        fprintf(stderr, "Error: frequency should be greater than 0\n");
        exit(84);
    }
    game->freq = nb;
    return;
}

void handle_n_c_f(int ac, int *i, char **av, int *fp)
{
    if (strcmp(av[(*i)], "-n") == 0) {
        check_av((*i), ac, av);
        handle_n(ac, i, av, fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
    if (strcmp(av[(*i)], "-c") == 0) {
        check_av((*i), ac, av);
        handle_c(av[(*i) + 1], fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
    if (strcmp(av[(*i)], "-f") == 0) {
        check_av((*i), ac, av);
        handle_f(av[(*i) + 1], fp);
        if ((*i) + 1 >= ac)
            exit(84);
    }
}
