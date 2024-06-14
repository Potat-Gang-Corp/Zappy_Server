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

char *construct_message(char *x, char *y, items_t *item_start)
{
    items_t *item = item_start;
    char *message = malloc(sizeof(char) * (strlen("bct \n")
    + strlen(x) + strlen(y) + strlen("   ") + 1));

    message[0] = '\0';
    strcat(message, "bct ");
    strcat(message, x);
    strcat(message, " ");
    strcat(message, y);
    strcat(message, " ");
    while (item) {
        strcat(message, get_items(item->type));
        strcat(message, " ");
        item = item->next;
    }
    strcat(message, "\n");
    return message;
}

int calculate_char_count(char *x, char *y, items_t *item_start)
{
    int char_count = strlen("bct \n") + strlen(x) + strlen(y) + strlen("   ");
    items_t *item = item_start;

    while (item) {
        char_count += strlen(get_items(item->type));
        char_count += 2;
        item = item->next;
    }
    return char_count;
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
    int char_count = calculate_char_count(x, y, item_start);
    char *message = construct_message(x, y, item_start);

    char_count = char_count;
    command_type = command_type;
    dprintf(cli->socket, "%s", message);
    free(message);
    return 0;
}

int cmd_mct(char *command_type, int gui_socket)
{
    (void)command_type;
    (void)gui_socket;
    return 0;
}
