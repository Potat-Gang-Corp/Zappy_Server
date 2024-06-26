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

char *compute_tile_stock(items_t *item_start, int x, int y)
{
    int item_counter[MAX_ITEMS];
    items_t *item = item_start;
    char *message;
    int size;

    for (int i = 0; i < MAX_ITEMS; i++)
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

char *process_tile_and_get_message(map_t *map, int x, int y, int *message_len)
{
    items_t *item = map->tiles[x + y * map->width]->items;
    char *message = compute_tile_stock(item, x, y);
    char *result = strdup(message ? message : "");

    *message_len += strlen(result);
    if (message)
        free(message);
    return result;
}

char **build_bct_dict(map_t *map, int *message_len)
{
    int total_tiles = map->width * map->height;
    char **bct_dict = malloc(sizeof(char *) * total_tiles + 1);

    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            bct_dict[x + y * map->width] = process_tile_and_get_message(
                map, x, y, message_len);
        }
    }
    return bct_dict;
}

char *build_message(char **bct_dict, map_t *map, int message_len)
{
    char *message = malloc(sizeof(char) * (message_len + 1));
    int x = 0;
    int y = 0;
    char *current_str;

    if (message == NULL) {
        return NULL;
    }
    message[0] = '\0';
    for (x = 0; x < map->width; x++) {
        for (y = 0; y < map->height; y++) {
            current_str = bct_dict[x + y * map->width];
            strcat(message, current_str ? current_str : "");
            free(current_str);
        }
    }
    return message;
}

int cmd_mct(char *command_type, int gui_socket)
{
    map_t *map = get_map_instance();
    client_t *cli = get_client_by_socket(gui_socket);
    int message_len = 0;
    char **bct_dict = build_bct_dict(map, &message_len);
    char *message = build_message(bct_dict, map, message_len);

    dprintf(cli->socket, "%s", message);
    free(message);
    free(bct_dict);
    (void)command_type;
    return 0;
}
