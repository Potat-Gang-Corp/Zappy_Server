/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map_cmd
*/
#include "my.h"
#include "get_instance.h"
#include "server.h"

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

int cmd_bct(char *command, int gui_socket)
{
    map_t *map = get_map_instance();
    client_t *cli = get_client_by_socket(gui_socket);
    char *command_type = strtok(command, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    int x_int = atoi(x);
    int y_int = atoi(y);
    items_t *item = map->tiles[x_int + y_int * map->width]->items;
    items_t *item_start = item;
    int item_counter[MAX_ITEMS];

    construct_message(item_start, item_counter);
    command_type = command_type;
    dprintf(cli->socket, "bct %d %d %d %d %d %d %d %d %d\n",
        x_int, y_int, item_counter[0], item_counter[1],
        item_counter[2], item_counter[3],
        item_counter[4], item_counter[5], item_counter[6]);
    return 0;
}
