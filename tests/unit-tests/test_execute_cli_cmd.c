/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_execute_cli_cmd
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

void setup_cmd_exec(void)
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

Test(client_management, test_client_getter, .init = setup_cmd_exec)
{
    server_t *server = get_instance();
    client_t *client1 = server->clients;

    cr_assert_eq(get_client_by_socket(101), client1, "Client1 should be found.");
    cr_assert_eq(get_client_by_socket(102), client1->next, "Client2 should be found.");
    cr_assert_eq(get_client_by_socket(103), client1->next->next, "Client3 should be found.");
    cr_assert_eq(get_client_by_socket(104), NULL, "Client4 should not be found.");
}
