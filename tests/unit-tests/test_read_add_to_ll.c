/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_read_add_to_ll
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

void setup_cli_cmd_check(void)
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

Test(command_management, test_cooldown_decrementation, .init = setup_cli_cmd_check)
{
    client_t *client1 = malloc(sizeof(client_t));
    client1->socket = 101;
    client1->team = strdup("Team1");
    client1->cd = 10;
    client1->next = NULL;

    lower_cli_cd(client1);
    cr_assert_eq(client1->cd, 9, "Cooldown should be 9.");

    client1->cd = 0;
    lower_cli_cd(client1);
    cr_assert_eq(client1->cd, 0, "Cooldown should be 0.");
}
