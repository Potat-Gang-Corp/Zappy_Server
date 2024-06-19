/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** action_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"
#include "look.h"

int append_to_msg(char **msg, size_t *current_size, const char *new_content)
{
    size_t new_content_length = strlen(new_content);
    size_t current_length = strlen(*msg);
    size_t new_size = current_length + new_content_length + 1;

    if (new_size > *current_size) {
        *msg = realloc(*msg, new_size);
        if (*msg == NULL) {
            perror("realloc");
            return -1;
        }
        *current_size = new_size;
    }
    strcat(*msg, new_content);
    return 0;
}

int lvl_zero(char **msg, size_t *msg_size, position_t pos)
{
    items_t *item;
    map_t *map = get_map_instance();

    item = map->tiles[pos.y * map->width + pos.x]->items;
    while (item) {
        if (append_to_msg(msg, msg_size, get_items(item->type)) == -1) {
            return -1;
        }
        if (item->next != NULL)
            append_to_msg(msg, msg_size, " ");
        item = item->next;
    }
    return 0;
}

int follow(client_t *cli, char *msg, size_t msg_size, int index)
{
    map_t *map = get_map_instance();
    size_t i = 0;
    unsigned int x = 0;

    for (; x < cli->level ; x++) {
        if (table_level[index].command_func(&msg, map, cli->pos) == 84) {
            free(msg);
            return 84;
        }
        index++;
    }
    if (append_to_msg(&msg, &msg_size, "]\n") == -1) {
        free(msg);
        return 84;
    }
    for (; i < strlen(msg); i++)
        msg[i] = tolower(msg[i]);
    write(cli->socket, msg, strlen(msg));
    return 0;
}

int cmd_look(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    size_t msg_size = 1;
    char *msg = malloc(sizeof(char) * 1000);
    int index = 0;

    (void)command_type;
    if (!msg) {
        perror("malloc");
        return 84;
    }
    msg[0] = '[';
    msg[1] = '\0';
    if (lvl_zero(&msg, &msg_size, cli->pos) == -1) {
        free(msg);
        return 84;
    }
    follow(cli, msg, msg_size, index);
    return 0;
}

int cmd_eject(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Eject command\n");
    return 0;
}

int cmd_take(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    map_t *map = get_map_instance();
    char *command_t = strtok(command_type, " ");
    char *item_type = strtok(NULL, " ");
    int current_index = cli->pos.x + cli->pos.y * map->width;
    item_type_t type = get_item_type(item_type);

    command_t = command_t;
    if (checking_item_existence(map->tiles[current_index]->items, type) == 1) {
        dprintf(cli->socket, "ko\n");
        return 84;
    }
    add_item_to_inventory(cli, type);
    delete_item_from_tiles(map->tiles[current_index], type);
    notice_player_take_object(cli, type);
    dprintf(cli->socket, "ok\n");
    cli->cd = 7 / get_game_instance()->freq;
    return 0;
}

int cmd_set(char *command, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    map_t *map = get_map_instance();
    char *command_type = strtok(command, " ");
    const char *item_type = strtok(NULL, " ");
    int current_index = cli->pos.x + cli->pos.y * map->width;
    item_type_t type = get_item_type(item_type);

    command_type = command_type;
    if (delete_item_inventory(cli, type) == 1) {
        dprintf(cli->socket, "ko\n");
        return 84;
    }
    add_item_to_tiles(map->tiles[current_index], type);
    notice_player_set_object(cli, type);
    cli->cd = 7 / get_game_instance()->freq;
    return 0;
}
