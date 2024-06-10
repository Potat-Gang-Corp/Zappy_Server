/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_clean_client
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

void setup_clean_client(void) {
    server_t *server = get_instance();
    server->clients = malloc(sizeof(client_t));
    server->clients->team = strdup("TeamName");
    server->clients->next = malloc(sizeof(client_t));
    server->clients->next->team = strdup("TeamName");
    server->clients->next->next = NULL;
}

Test(clean_client, clean_client_struct, .init = setup_clean_client) {
    clean_client_struct();
    server_t *server = get_instance();
    cr_assert_null(server->clients);
}
