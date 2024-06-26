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
 * @file mct_command_bis.c
 * @brief File handling the mct command
*/

static int compute_stock_buffer_size(int item_counter[EGG], int x, int y)
{
    int size = snprintf(NULL, 0,
        "bct %d %d %d %d %d %d %d %d %d\n",
        x, y, item_counter[0], item_counter[1],
        item_counter[2], item_counter[3],
        item_counter[4], item_counter[5], item_counter[6]);

    return size;
}

static char *compute_tile_stock(items_t *item_start, int x, int y)
{
    int item_counter[MAX_ITEMS];
    items_t *item = item_start;
    char *message;
    int size;
    int i;

    for (i = 0; i < MAX_ITEMS; i++)
        item_counter[i] = 0;
    while (item) {
        item_counter[item->type] += 1;
        item = item->next;
    }
    size = compute_stock_buffer_size(item_counter, x, y);
    message = malloc(sizeof(char) * size + 1);
    snprintf(message, size + 1,
        "bct %d %d %d %d %d %d %d %d %d\n",
        x, y, item_counter[0], item_counter[1],
        item_counter[2], item_counter[3],
        item_counter[4], item_counter[5], item_counter[6]);
    return message;
}

static void send_tile_stock(int gui_socket, items_t *item, int x, int y)
{
    char *message = compute_tile_stock(item, x, y);

    if (message != NULL) {
        dprintf(gui_socket, "%s", message);
        free(message);
    }
}

int cmd_mct(char *command_type, int gui_socket)
{
    map_t *map = get_map_instance();
    int x;
    int y;
    items_t *item;

    for (x = 0; x < map->width; x++) {
        for (y = 0; y < map->height; y++) {
            item = map->tiles[x + y * map->width]->items;
            send_tile_stock(gui_socket, item, x, y);
        }
    }
    (void)command_type;
    return 0;
}
