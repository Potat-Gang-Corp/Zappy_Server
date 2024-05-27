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
int handle_n(int ac, int *i, char **av, int *fp)
{
    game_t *game = get_game_instance();
    int save = *i;
    int k;

    game->nb_teams = 0;
    if (*i + 1 < ac) {
        if (av[*i + 1][0] == '-')
            return 84;
    }
    (*fp) |= 1 << 3;
    while (*i + 1 < ac && av[*i + 1][0] != '-') {
        (*i)++;
        game->nb_teams++;
    }
    game->teams = malloc(sizeof(team_t *) * game->nb_teams);
    for (k = 0; k < game->nb_teams; k++) {
        game->teams[k] = malloc(sizeof(team_t));
        game->teams[k]->name = strdup(av[save + k + 1]);
    }
    return 0;
}

int handle_c(char *av, int *fp)
{
    int nb;
    int i;
    game_t *game = get_game_instance();

    (*fp) |= 1 << 4;
    for (i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            fprintf(stderr, "Error: flag -c must be a number\n");
            return 84;
        }
    }
    nb = atoi(av);
    for (int i = 0; i < game->nb_teams; i++)
        game->teams[i]->max_clients = nb;
    return 0;
}

int handle_f(char *av, int *fp)
{
    int nb;
    game_t *game = get_game_instance();

    (*fp) |= 1 << 5;
    for (int i = 0; av[i]; i++) {
        if (av[i] < '0' || av[i] > '9') {
            fprintf(stderr, "Error: flag -f must be a number\n");
            return 84;
        }
    }
    nb = atoi(av);
    game->freq = nb;
    return 0;
}

int n_flag_detection(int ac, int *i, char **av, int *fp)
{
    game_t *game = get_game_instance();
    int status = 0;

    if (strcmp(av[(*i)], "-n") == 0) {
        check_av((*i), ac, av);
        status = handle_n(ac, i, av, fp);
        if (game->nb_teams == 0 || (*i) + 1 > ac || status == 84) {
            fprintf(stderr, "Error: flag -n TEAM1 TEAM2 TEAM3\n");
            return 84;
        }
    }
    return 0;
}

int handle_n_c_f(int ac, int *i, char **av, int *fp)
{
    if (n_flag_detection(ac, i, av, fp) == 84)
        return 84;
    if (strcmp(av[(*i)], "-c") == 0) {
        check_av((*i), ac, av);
        if (handle_c(av[(*i) + 1], fp) == 84) {
            fprintf(stderr, "Error: flag -c GRU\n");
            return 84;
        }
    }
    if (strcmp(av[(*i)], "-f") == 0) {
        check_av((*i), ac, av);
        if (handle_f(av[(*i) + 1], fp) == 84) {
            return 84;
        }
    }
    return 0;
}
