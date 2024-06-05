/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_clean_map
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

void setup_map(void) {
    srand(time(NULL));
    map_t *map = get_map_instance();
    map->width = 100;
    map->height = 100;
    map->tiles = malloc(sizeof(tile_t *) * map->height);

    for (int i = 0; i < map->height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t) * map->width);
        for (int j = 0; j < map->width; j++) {
            map->tiles[i][j].x = j;
            map->tiles[i][j].y = i;
            map->tiles[i][j].items = NULL;

            if (rand() % 3 == 0) {
                items_t *head = NULL, *new_item;
                int num_items = rand() % 4;
                for (int k = 0; k < num_items; k++) {
                    new_item = malloc(sizeof(items_t));
                    new_item->type = rand() % PLAYER;
                    new_item->next = head;
                    head = new_item;
                }
                map->tiles[i][j].items = head;
            }
        }
    }
}

Test(clean_map, clean_item_linked_list, .init = setup_map) {
    map_t *map = get_map_instance();
    tile_t *tile = &map->tiles[0][0];
    items_t *items = tile->items;

    clean_item_linked_list(&items);
    cr_assert_null(tile->items);
}

Test(clean_map, checking_existence_tile_element, .init = setup_map) {
    map_t *map = get_map_instance();
    tile_t *tile = &map->tiles[0][0];

    checking_existence_tile_element(tile);
    cr_assert_null(tile->items);
}

Test(clean_map, clean_tiles_struct, .init = setup_map) {
    map_t *map = get_map_instance();

    clean_tiles_struct();
    cr_assert_null(map->tiles);
}

Test(clean_map, clean_map_struct, .init = setup_map) {
    map_t *map = get_map_instance();

    clean_map_struct();
    cr_assert_null(map->tiles);
}
