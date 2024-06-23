/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications_incantation
*/

#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

void notice_gui_incantation(int x, int y, int level, int *tab)
{
    client_t *cli = get_instance()->clients;
    size_t msg_size = 128;
    char *message = malloc(msg_size);
    size_t needed;
    int length = snprintf(message, msg_size, "pic %d %d %d", x, y, level);
    int i;

    for (i = 0; tab[i] != -1; i++) {
        needed = length + snprintf(NULL, 0, " %d", tab[i]) + 1;
        if (needed > msg_size) {
            msg_size = needed;
            message = realloc(message, msg_size);
        }
        length += snprintf(message + length, msg_size - length, " %d", tab[i]);
    }
    snprintf(message + length, msg_size - length, "\n");
    for (; cli != NULL; cli = cli->next)
        if (cli->graphic == true)
            dprintf(cli->id, "%s", message);
    free(message);
}
