/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_init_server
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

int is_positive(int value) {
    return value > 0;
}

void setup_server() {
    server_t *server = get_instance();
    server->socket = -1;
    srand(time(NULL));
    server->port = 1024 + rand() % (65535 - 1024);
}

Test(server_tests, test_init_socket_success) {
    setup_server();
    server_t *server = get_instance();
    
    cr_assert_eq(init_socket(), 0, "init_socket should return 0 on success");
    cr_assert_neq(server->socket, -1, "socket should be initialized");
}

Test(server_tests, test_init_server_launch_success) {
    int opt = 1;

    setup_server();
    server_t *server = get_instance();
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    server->sockaddr.sin_family = AF_INET;
    server->sockaddr.sin_addr.s_addr = INADDR_ANY;
    server->sockaddr.sin_port = htons(server->port);

    cr_assert_eq(init_server_launch(), 0, "init_server_launch should return 0 on success");
}

Test(server_tests, test_init_server_listen_success) {
    setup_server();
    server_t *server = get_instance();
    server->socket = socket(AF_INET, SOCK_STREAM, 0);

    cr_assert_eq(init_server_listen(), 0, "init_server_listen should return 0 on success");
}

Test(server_tests, test_init_server_bis_success) {
    setup_server();
    server_t *server = get_instance();

    cr_assert_eq(init_server_bis(), 0, "init_server_bis should return 0 on success");
    cr_assert_neq(server->port, 0, "port should be set to a non-zero value");
}

Test(server_tests, test_init_server_success) {
    setup_server();
    server_t *server = get_instance();

    cr_assert_eq(init_server(), 0, "init_server should return 0 on success");
    cr_assert_eq(server->maxfd, 0, "maxfd should be initialized to 0");
    cr_assert_eq(server->nb_players, 0, "nb_players should be initialized to 0");
    cr_assert_null(server->clients, "clients should be initialized to NULL");
    cr_log_info("Server started on port %d", server->port);
}
