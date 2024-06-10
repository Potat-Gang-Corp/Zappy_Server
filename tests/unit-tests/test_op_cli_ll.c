/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_op_cli_ll
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

void setup_remove_cli(void) {
    server_t *server = get_instance();
    client_t *client1 = malloc(sizeof(client_t));
    client1->socket = 101;
    client1->team = strdup("Team1");
    client1->next = NULL;

    client_t *client2 = malloc(sizeof(client_t));
    client2->socket = 102;
    client2->team = strdup("Team2");
    client2->next = NULL;

    client_t *client3 = malloc(sizeof(client_t));
    client3->socket = 103;
    client3->team = strdup("Team3");
    client3->next = NULL;

    client1->next = client2;
    client2->next = client3;
    server->clients = client1;
}

Test(client_management, find_client, .init = setup_remove_cli) {
    client_t *prev = NULL;
    client_t *found = find_client_and_prev(101, &prev);

    cr_assert_not_null(found, "Client should be found.");
    cr_assert_null(prev, "Prev should be NULL for the first client.");
    cr_assert(found->socket == 101, "Found client socket should be 101.");
}

Test(client_management, remove_client, .init = setup_remove_cli) {
    server_t *server = get_instance();
    int result = remove_client(101);

    cr_assert_eq(result, 0, "Remove client should return 0 on success.");
    cr_assert_not_null(server->clients, "Clients list should not be empty.");
    cr_assert_eq(server->clients->socket, 102, "Next client should now be the first client.");

    result = remove_client(103);
    cr_assert_eq(result, 0, "Remove client should return 0 on success.");
    cr_assert_not_null(server->clients, "Clients list should still not be empty after removing the last client.");
    cr_assert_eq(server->clients->socket, 102, "Remaining client should be 102 after removing 103.");
}

Test(client_management, remove_last_client, .init = setup_remove_cli) {
    clean_client_struct();
    int result = remove_client(103);

    cr_assert_eq(result, 0, "Remove client should return 0 on success.");
}


