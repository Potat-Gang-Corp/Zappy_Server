/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_game_command
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

void handle_msz_command(client_t *cli)
{
    game_t *game = get_game_instance();

    dprintf(cli->socket, "%d %d\n", game->width, game->height);
}

void handle_left_command(client_t *cli)
{
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\r\n");
}

void handle_right_command(client_t *cli)
{
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\n");
}

void handle_connect_nbr_command(client_t *cli)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, cli->team) == 0) {
            dprintf(cli->socket, "%d\n", game->teams[i]->max_clients);
            return;
        }
    }
}

void handle_ppo_command(client_t *cli, char *command)
{
    server_t *server = get_instance();
    char *player_nb = strtok(command, " ");
    int socket_nb;
    
    player_nb = strtok(NULL, " #");
    socket_nb = atoi(player_nb);
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (socket_nb == cli->socket) {
            dprintf(cli->socket, "ppo #%d %d %d %d\n", cli->socket, cli->pos.x,
                cli->pos.y, (cli->pos.orientation + 1));
            return;
        }
    }
}

void handle_plv_command(client_t *cli, char *command)
{
    server_t *server = get_instance();
    char *player_nb = strtok(command, " ");
    int socket_nb;
    
    player_nb = strtok(NULL, " #");
    socket_nb = atoi(player_nb);
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (socket_nb == cli->socket) {
            dprintf(cli->socket, "plv #%d %d\n", cli->socket, cli->level);
            return;
        }
    }
}

void delete_item_from_tiles(tile_t *tile, item_type_t type)
{
    items_t *item = tile->items;
    items_t *prev = NULL;

    while (item != NULL) {
        if (item->type == type) {
            if (prev == NULL) {
                tile->items = item->next;
            } else {
                prev->next = item->next;
            }
            free(item);
            return;
        }
        prev = item;
        item = item->next;
    }
}

void move_player(client_t *cli, game_t *game)
{
    int dx = 0, dy = 0;

    switch (cli->pos.orientation) {
        case NORTH: dy = -1; break;
        case SOUTH: dy = 1; break;
        case EAST:  dx = 1; break;
        case WEST:  dx = -1; break;
    }
    cli->pos.x = (cli->pos.x + dx + game->width) % game->width;
    cli->pos.y = (cli->pos.y + dy + game->height) % game->height;
}

void handle_forward_command(client_t *cli)
{
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    item_type_t type = PLAYER;
    int current_index = cli->pos.x + cli->pos.y * game->width;
    int new_index = cli->pos.x + cli->pos.y * game->width;

    delete_item_from_tiles(map->tiles[current_index], type);
    move_player(cli, game);
    add_item_to_tiles(map->tiles[new_index], type);
    dprintf(cli->socket, "ok\n");
}

void handle_tna_command(client_t *cli)
{
    int char_count = 0;
    game_t *game = get_game_instance();
    char *buffer;

    for (int i = 0; i < game->nb_teams; i++) {
        char_count += strlen(game->teams[i]->name);
        char_count += strlen("tna \n");
    }
    
    buffer = malloc(sizeof(char) * char_count + 1);
    buffer[0] = '\0';
    for (int i = 0; i < game->nb_teams; i++) {
        strcat(buffer, "tna ");
        strcat(buffer, game->teams[i]->name);
        strcat(buffer, "\n");
    }
    dprintf(cli->socket, "%s", buffer);
    
}

char *construct_message(char *x, char *y, items_t *item_start) {
    items_t *item = item_start;
    char *message = malloc(sizeof(char) * (strlen("bct \n") + strlen(x) + strlen(y) + strlen("   ") + 1));
    
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

int calculate_char_count(char *x, char *y, items_t *item_start) {
    int char_count = strlen("bct \n") + strlen(x) + strlen(y) + strlen("   ");
    items_t *item = item_start;

    while (item) {
        char_count += strlen(get_items(item->type));
        char_count += 2;
        item = item->next;
    }
    return char_count;
}

void handle_bct_command(client_t *cli, char *command)
{
    map_t *map = get_map_instance();
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
}

void handle_inventory_command(client_t *cli)
{
    dprintf(cli->socket, "[food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        cli->inventory.food, cli->inventory.linemate,
        cli->inventory.deraumere, cli->inventory.sibur,
        cli->inventory.mendiane, cli->inventory.phiras,
        cli->inventory.thystame);
}

void handle_pin_command(client_t *cli, char *command)
{
    server_t *server = get_instance();
    client_t *player = NULL;
    char *command_type = strtok(command, " ");
    char *player_nb = strtok(NULL, " #");
    int socket_nb = atoi(player_nb);

    command_type = command_type;
    for (player = server->clients; player != NULL; player = player->next) {
        if (socket_nb == player->socket) {
            dprintf(cli->socket, "pin %d %d %d %d %d %d %d %d %d %d\n",
                player->socket, player->pos.x, player->pos.y,
                player->inventory.food, player->inventory.linemate,
                player->inventory.deraumere, player->inventory.sibur,
                player->inventory.mendiane, player->inventory.phiras,
                player->inventory.thystame);
            return;
        }
    }
}

void add_item_to_inventory(client_t *cli, item_type_t type)
{
    if (type == FOOD) {
        cli->inventory.food += 1;
    }
    if (type == LINEMATE) {
        cli->inventory.linemate += 1;
    }
    if (type == DERAUMERE) {
        cli->inventory.deraumere += 1;
    }
    if (type == SIBUR) {
        cli->inventory.sibur += 1;
    }
    if (type == MENDIANE) {
        cli->inventory.mendiane += 1;
    }
    if (type == PHIRAS) {
        cli->inventory.phiras += 1;
    }
    if (type == THYSTAME) {
        cli->inventory.thystame += 1;
    }
}

int checking_item_existence(items_t *item, item_type_t type)
{
    while (item) {
        if (item->type == type) {
            return 0;
        }
        item = item->next;
    }
    return 1;
}

void notice_player_take_object(client_t *cli, item_type_t type)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->is_graphical == true) {
            dprintf(graphic->socket, "pgt %d %d\n", cli->socket, type);
        }
    }
}

void handle_take_command(client_t *cli, char *command)
{
    map_t *map = get_map_instance();
    char *command_type = strtok(command, " ");
    char *item_type = strtok(NULL, " ");
    int current_index = cli->pos.x + cli->pos.y * map->width;
    item_type_t type = get_item_type(item_type);

    command_type = command_type;
    if (checking_item_existence(map->tiles[current_index]->items, type) == 1) {
        dprintf(cli->socket, "ko\n");
        return;
    }
    add_item_to_inventory(cli, type);
    delete_item_from_tiles(map->tiles[current_index], type);
    notice_player_take_object(cli, type);
    dprintf(cli->socket, "ok\n");
}

int delete_item_inventory(client_t *cli, item_type_t type)
{
    if (type == FOOD && cli->inventory.food > 0) {
        cli->inventory.food -= 1;
        return 0;
    }
    if (type == LINEMATE && cli->inventory.linemate > 0) {
        cli->inventory.linemate -= 1;
        return 0;
    }
    if (type == DERAUMERE && cli->inventory.deraumere > 0) {
        cli->inventory.deraumere -= 1;
        return 0;
    }
    if (type == SIBUR && cli->inventory.sibur > 0) {
        cli->inventory.sibur -= 1;
        return 0;
    }
    if (type == MENDIANE && cli->inventory.mendiane > 0) {
        cli->inventory.mendiane -= 1;
        return 0;
    }
    if (type == PHIRAS && cli->inventory.phiras > 0) {
        cli->inventory.phiras -= 1;
        return 0;
    }
    if (type == THYSTAME && cli->inventory.thystame > 0) {
        cli->inventory.thystame -= 1;
        return 0;
    }
    return 1;
}

void notice_player_set_object(client_t *cli, item_type_t type)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->is_graphical == true) {
            dprintf(graphic->socket, "pdr %d %d\n", cli->socket, type);
        }
    }
}

void handle_set_command(client_t *cli, char *command)
{
    map_t *map = get_map_instance();
    char *command_type = strtok(command, " ");
    const char *item_type = strtok(NULL, " ");
    int current_index = cli->pos.x + cli->pos.y * map->width;
    item_type_t type = get_item_type(item_type);

    command_type = command_type;
    if (delete_item_inventory(cli, type) == 1) {
        dprintf(cli->socket, "ko\n");
        return;
    }
    add_item_to_tiles(map->tiles[current_index], type);
    notice_player_set_object(cli, type);

}

int comp_cmd(char *command_type, client_t *cli, char *command)
{
    command = command;
    if (strcmp(command_type, "Left") == 0) {
        handle_left_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Look") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Broadcast") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Eject") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Take") == 0) {
        handle_take_command(cli, command);
        return 0;
    }
    if (strcmp(command_type, "Set") == 0) {
        handle_set_command(cli, command);
        return 0;
    }
    return 1;
}

int comp_cmd_bis(char *command_type, client_t *cli, char *command)
{
    command = command;
    cli = cli;
    if (strcmp(command_type, "Forward") == 0) {
        handle_forward_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Right") == 0) {
        handle_right_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Fork") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Incantation") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Connect_nbr") == 0) {
        handle_connect_nbr_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Inventory") == 0) {
        handle_inventory_command(cli);
        return 0;
    }
    return 1;
}

int handle_gui_command(char *command_type, client_t *cli, char *command)
{
    if (strcmp(command_type, "msz") == 0 && cli->is_graphical == true) {
        handle_msz_command(cli);
        return 0;
    }
    if (strcmp(command_type, "ppo") == 0 && cli->is_graphical == true) {
        handle_ppo_command(cli, command);
        return 0;
    }
    if (strcmp(command_type, "plv") == 0 && cli->is_graphical == true) {
        handle_plv_command(cli, command);
        return 0;
    }
    if (strcmp(command_type, "tna") == 0 && cli->is_graphical == true) {
        handle_tna_command(cli);
        return 0;
    }
    if (strcmp(command_type, "bct") == 0 && cli->is_graphical == true) {
        handle_bct_command(cli, command);
        return 0;
    }
    if (strcmp(command_type, "pin") == 0 && cli->is_graphical == true) {
        handle_pin_command(cli, command);
        return 0;
    }
    return 1;
}

void execute_cli_cmd_g(client_t *cli, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(buffer, " \r\n");
    int result = -1;

    result = comp_cmd_bis(command_type, cli, command);
    if (result == 1)
        result = comp_cmd(command_type, cli, command);
    if (result == 1)
        result = handle_gui_command(command_type, cli, command);
    if (result == 1 && cli->is_graphical == true)
        dprintf(cli->socket, "suc\n");
    free(buffer);
}

//beurky