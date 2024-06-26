/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map_cmd
*/
#include "my.h"
#include "get_instance.h"
#include "server.h"

/**
 * @file map_cmd.c
 * @brief File handling the map commands
*/

int cmd_msz(char *command_type, int gui_socket)
{
    game_t *game = get_game_instance();
    client_t *cli = get_client_by_socket(gui_socket);

    (void)command_type;
    dprintf(cli->socket, "msz %d %d\n", game->width, game->height);
    return 0;
}

int *construct_message(items_t *item_start, int *items_counter)
{
    items_t *item = item_start;

    for (int i = 0; i < MAX_ITEMS; i++) {
        items_counter[i] = 0;
    }
    while (item) {
        items_counter[item->type] += 1;
        item = item->next;
    }
    return items_counter;
}

static int set_up_x_y(char *command, int *x_int, int *y_int)
{
    char *x = strtok(command, " ");
    char *y;

    x = strtok(NULL, " ");
    y = strtok(NULL, " ");
    if (x == NULL || y == NULL)
        return 84;
    *x_int = atoi(x);
    *y_int = atoi(y);
    return 0;
}

int cmd_bct(char *command, int gui_socket)
{
    map_t *map = get_map_instance();
    client_t *cli = get_client_by_socket(gui_socket);
    int x_int = 0;
    int y_int = 0;
    int ret = set_up_x_y(command, &x_int, &y_int);
    items_t *item = map->tiles[x_int + y_int * map->width]->items;
    items_t *item_start = item;
    int item_counter[MAX_ITEMS];

    if (ret == 84) {
        dprintf(gui_socket, "sbp\n");
        return 84;
    }
    construct_message(item_start, item_counter);
    dprintf(cli->socket, "bct %d %d %d %d %d %d %d %d %d\n",
        x_int, y_int, item_counter[0], item_counter[1],
        item_counter[2], item_counter[3],
        item_counter[4], item_counter[5], item_counter[6]);
    return 0;
}
