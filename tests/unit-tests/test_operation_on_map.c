#include <criterion/criterion.h>
#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "map.h"

Test(tile_tests, remove_middle_item) {
    
    tile_t tile = {0};
    tile.items = NULL;

    add_item_to_tiles(&tile, LINEMATE);
    add_item_to_tiles(&tile, EGG);
    add_item_to_tiles(&tile, FOOD);

    delete_item_from_tiles(&tile, EGG);

    cr_assert_not_null(tile.items);
    cr_assert_eq(tile.items->type, FOOD);
    cr_assert_eq(tile.items->next->type, LINEMATE);
    cr_assert_null(tile.items->next->next);

}

Test(tile_tests, remove_non_existent_item) {
    tile_t tile = {0};
    tile.items = NULL;
    add_item_to_tiles(&tile, FOOD);
    delete_item_from_tiles(&tile, EGG);
    cr_assert_not_null(tile.items);
    cr_assert_eq(tile.items->type, FOOD);
    cr_assert_null(tile.items->next);
}

Test(tile_tests, remove_only_item) {
    tile_t tile = {0};
    tile.items = NULL;
    add_item_to_tiles(&tile, EGG);
    delete_item_from_tiles(&tile, EGG);
    cr_assert_null(tile.items);
}

Test(operation_on_map, checking_item_existence)
{
    items_t item1 = {FOOD, NULL};
    items_t item2 = {LINEMATE, &item1};

    cr_assert_eq(checking_item_existence(&item2, LINEMATE), 0);
    cr_assert_eq(checking_item_existence(&item2, DERAUMERE), 1);
}