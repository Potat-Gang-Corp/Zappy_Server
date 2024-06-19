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

    for (int i = 0; i < EGG; i++) {
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
    int item_counter[EGG];

    construct_message(item_start, item_counter);
    command_type = command_type;
    dprintf(cli->socket, "bct %d %d %d %d %d %d %d %d %d\n",
        x_int, y_int, item_counter[0], item_counter[1],
        item_counter[2], item_counter[3],
        item_counter[4], item_counter[5], item_counter[6]);
    return 0;
}

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
    int item_counter[EGG];
    items_t *item = item_start;
    char *message;
    int size;

    for (int i = 0; i < EGG; i++)
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

static char **build_bct_dict(map_t *map, int *message_len)
{
    int total_tiles = map->width * map->height;
    char **bct_dict = malloc(sizeof(char *) * total_tiles + 1);
    items_t *item;

    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            item = map->tiles[x + y * map->width]->items;
            bct_dict[x + y * map->width] = strdup(
                compute_tile_stock(item, x, y));
            *message_len += strlen(bct_dict[x + y * map->width]);
        }
    }
    return bct_dict;
}

static char *build_message(char **bct_dict, map_t *map, int message_len)
{
    char *message = malloc(sizeof(char) * (message_len + 1));

    if (message == NULL) {
        return NULL;
    }
    message[0] = '\0';
    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            char *current_str = bct_dict[x + y * map->width];
            if (current_str != NULL) {
                strcat(message, current_str);
                free(current_str);
            }
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
