/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_eject
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include <time.h>

client_t *create_and_add_client(server_t *server, int x, int y, orientation_t orientation) {
    client_t *new_client = malloc(sizeof(client_t));
    if (new_client == NULL) {
        cr_log_error("Failed to allocate memory for new client.");
        return NULL;
    }
    new_client->socket = server->client_id++;
    new_client->pos.x = x;
    new_client->pos.y = y;
    new_client->pos.orientation = orientation;

    new_client->next = server->clients;
    server->clients = new_client;

    return new_client;
}

Test(server_operations, move_and_restore_orientation_for_multiple_clients) {
    server_t *server = get_instance();
    game_t *game = get_game_instance();

    game->width = 10;
    game->height = 10;

    client_t *client1 = create_and_add_client(server, 5, 5, NORTH);
    client_t *client2 = create_and_add_client(server, 6, 5, EAST);


    move_and_restore_orientation(client1, game, SOUTH);
    move_and_restore_orientation(client2, game, WEST);

    cr_assert(client1->pos.x == 5 && client1->pos.y == 6, "Client 1 should move SOUTH.");
    cr_assert(client2->pos.x == 5 && client2->pos.y == 5, "Client 2 should move WEST.");
    cr_assert(client1->pos.orientation == NORTH, "Client 1's orientation should be restored to NORTH.");
    cr_assert(client2->pos.orientation == EAST, "Client 2's orientation should be restored to EAST.");

}

Test(server_operations, orientation_changes_and_boundary_conditions) {
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    game->width = 10;
    game->height = 10;

    int edge_positions[4][2] = {{0, 0}, {0, 9}, {9, 0}, {9, 9}};
    orientation_t orientations[4] = {NORTH, EAST, SOUTH, WEST};
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    int expected_x[4], expected_y[4];

    for (int i = 0; i < 4; i++) {
        client_t *client = create_and_add_client(server, edge_positions[i][0], edge_positions[i][1], orientations[i]);

        int new_orientation_index = (i + 1) % 4;
        move_and_restore_orientation(client, game, orientations[new_orientation_index]);

        expected_x[i] = (edge_positions[i][0] + dx[new_orientation_index] + game->width) % game->width;
        expected_y[i] = (edge_positions[i][1] + dy[new_orientation_index] + game->height) % game->height;

        cr_assert(client->pos.x == expected_x[i], "X position did not wrap correctly at the edge.");
        cr_assert(client->pos.y == expected_y[i], "Y position did not wrap correctly at the edge.");
        cr_assert(client->pos.orientation == orientations[i], "Orientation was not restored correctly after moving.");

        free(client);
        server->clients = NULL;
    }
}

Test(server_operations, complex_movement_sequences) {
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    game->width = 15;
    game->height = 15;

    client_t *client = create_and_add_client(server, 7, 7, NORTH);

    orientation_t move_sequence[6] = {EAST, EAST, SOUTH, WEST, WEST, NORTH};
    for (int i = 0; i < 6; i++) {
        move_and_restore_orientation(client, game, move_sequence[i]);
    }

    cr_assert(client->pos.x == 7 && client->pos.y == 7, "Client did not return to the original position after complex movements.");
    cr_assert(client->pos.orientation == NORTH, "Client's original orientation was not restored after complex movements.");

    free(client);
    server->clients = NULL;
}

Test(server_operations, high_load_simultaneous_movements) {
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    game->width = 20;
    game->height = 20;

    const int num_clients = 100;
    client_t *clients[num_clients];
    for (int i = 0; i < num_clients; i++) {
        clients[i] = create_and_add_client(server, i % 20, i / 20, (orientation_t)(i % 4));
    }
    for (int i = 0; i < num_clients; i++) {
        move_and_restore_orientation(clients[i], game, (orientation_t)((clients[i]->pos.orientation + 1) % 4));
    }
    for (int i = 0; i < num_clients; i++) {
        cr_assert(clients[i]->pos.orientation == (orientation_t)(i % 4), "Client orientation was not restored correctly under high load.");
    }
    for (int i = 0; i < num_clients; i++) {
        free(clients[i]);
    }
    server->clients = NULL;
}

