/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_mct
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
int cmd_mct(char *command_type, int gui_socket);

Test(cmd_mct_test, simple_return_test) {
    int mock_socket = 1;
    int result = cmd_mct("mct", mock_socket);
    cr_assert_eq(result, 0, "cmd_mct devrait retourner 0");
}