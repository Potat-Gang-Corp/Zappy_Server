/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_check_cli
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

void setup_checking_client(void)
{
    server_t *server = get_instance();
    client_t *client1 = malloc(sizeof(client_t));
    client1->socket = 101;
    client1->team = strdup("Team1");
    client1->cd = 0;
    client1->next = NULL;

    client_t *client2 = malloc(sizeof(client_t));
    client2->socket = 102;
    client2->team = strdup("Team2");
    client2->next = NULL;

    client_t *client3 = malloc(sizeof(client_t));
    client3->socket = 103;
    client3->graphic = true;
    client3->next = NULL;

    client1->next = client2;
    client2->next = client3;
    server->clients = client1;
}

Test(client_checking, test_gui_client, .init = setup_checking_client)
{
    server_t *server = get_instance();

    client_t *client1 = server->clients;

    cr_assert_eq(is_gui(client1->socket), false, "Client1 is not a GUI client.");

    client1->graphic = true;

    cr_assert_eq(is_gui(client1->socket), true, "Client1 is a GUI client.");
}

Test(waiting_list, retrieves_and_removes_client) {
    server_t server;
    TAILQ_INIT(&server.waiting_list);
    waiting_client_t client1 = {.team = "TeamA"}, client2 = {.team = "TeamB"};
    TAILQ_INSERT_TAIL(&server.waiting_list, &client1, entries);
    TAILQ_INSERT_TAIL(&server.waiting_list, &client2, entries);

    waiting_client_t *retrieved_client = get_waiting_client(&server, "TeamA");
    cr_assert_not_null(retrieved_client, "Should retrieve the client for TeamA");
    cr_assert_str_eq(retrieved_client->team, "TeamA", "Should match the team name");
    
    // Verify removal from list
    cr_assert(TAILQ_EMPTY(&server.waiting_list) == false, "List should not be empty after one removal");
    cr_assert_null(get_waiting_client(&server, "TeamA"), "Should not find TeamA after removal");
}
