/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** fill_tab_incantation
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "elevation.h"

/**
 * @file fill_tab_incantation.c
 * @brief File handling the incantation
*/
int create_new_tab(int **tab, int cpt, int *nb)
{
    int *new_tab = NULL;

    if (cpt >= *nb) {
        *nb *= 2;
        new_tab = realloc(*tab, (*nb + 1) * sizeof(int));
        if (new_tab == NULL) {
            free(*tab);
            perror("realloc");
            return -1;
        }
        *tab = new_tab;
    }
    return 0;
}

int fill_tab(int **tab, int *nb, client_t *s, int cpt)
{
    client_t *cli = get_instance()->clients;

    for (; cli != NULL; cli = cli->next) {
        if (cli->pos.x == s->pos.x && cli->pos.y == s->pos.y
            && cli->level == s->level && cli != s) {
            create_new_tab(tab, cpt, nb);
            cpt++;
            (*tab)[cpt] = cli->id;
        }
    }
    return cpt;
}
