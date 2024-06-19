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

int follow(client_t *cli, char *msg, size_t msg_size, int index)
{
    map_t *map = get_map_instance();
    size_t i = 0;
    unsigned int x = 0;

    for (; x < cli->level; x++) {
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
    map->display(map);
    printf("pos.x = %d, pos.y = %d\n", cli->pos.x, cli->pos.y);
    printf("orientation = %d\n", cli->pos.orientation);
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

static void delete_egg(egg_t **egg, egg_t **prev_egg, egg_t **curr_egg)
{
    map_t *map = get_map_instance();

    notice_graphic_egg_destruction((*curr_egg)->egg_id);
    delete_item_from_tiles(map->tiles[(*curr_egg)->x_pos +
        (*curr_egg)->y_pos * map->width], EGG);
    if (*prev_egg == NULL) {
        *egg = (*curr_egg)->next;
    } else {
        (*prev_egg)->next = (*curr_egg)->next;
    }
    free(*curr_egg);
    *curr_egg = (*prev_egg == NULL) ? *egg : (*prev_egg)->next;
}

static void destroy_eggs(egg_t *egg, int x, int y)
{
    egg_t *tmp = egg;
    egg_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->x_pos != x || tmp->y_pos != y) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        delete_egg(&egg, &prev, &tmp);
    }
}

static void move_and_restore_orientation(client_t *tmp, game_t *game,
    int new_orientation)
{
    int old_orientation = tmp->pos.orientation;

    tmp->pos.orientation = new_orientation;
    move_player(tmp, game);
    tmp->pos.orientation = old_orientation;
}

static void push_players_to_tile(client_t *cli, int x, int y)
{
    server_t *server = get_instance();
    client_t *tmp = server->clients;
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    int new_index;

    while (tmp != NULL) {
        if (tmp->pos.x == x && tmp->pos.y == y &&
            tmp->socket != cli->socket &&
            tmp->graphic == false && tmp->logged == true) {
            dprintf(tmp->socket, "eject: %d\n", cli->pos.orientation);
            delete_item_from_tiles(map->tiles[tmp->pos.x +
                tmp->pos.y * game->width], PLAYER);
            move_and_restore_orientation(tmp, game, cli->pos.orientation);
            new_index = tmp->pos.x + tmp->pos.y * game->width;
            add_item_to_tiles(map->tiles[new_index], PLAYER);
        }
        tmp = tmp->next;
    }
}

int cmd_eject(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    game_t *game = get_game_instance();
    egg_t *egg = NULL;

    for (int i = 0; i < game->nb_teams; i++) {
        egg = game->teams[i]->egg;
        destroy_eggs(egg, cli->pos.x, cli->pos.y);
    }
    push_players_to_tile(cli, cli->pos.x, cli->pos.y);
    dprintf(cli->socket, "ok\n");
    cli->cd = 7 / get_game_instance()->freq;
    (void)command_type;
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
