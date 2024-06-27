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
#include "../../include/commands_entry_gui.h"

Test(cmd_mct_test, cmd_mct)
{
    map_t *map = get_map_instance();
    items_t *item = malloc(sizeof(items_t));
    item->type = 0;
    item->next = NULL;
    map->tiles[0]->items = item;
    cr_assert_eq(cmd_mct("mct", 1), 0);
}
