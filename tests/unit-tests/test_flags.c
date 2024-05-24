/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_flags
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/handle_flags.h"

Test(handle_flags, flags_test)
{
    char *av[] = { "./zappy_server", "-p", "1234", "-x", "100", "-y", "100", "-n", "team1", "-c", "10", "-f", "50" };
    int ac = 11;

    int result = handle_flags(ac, av);
    cr_assert_eq(result, 0);
}

Test(handle_flags, display_help_tests)
{
    cr_redirect_stdout();
    char *av[] = {"./zappy_server", "-help" };
    int ac = 2;

    int result = handle_flags(ac, av);
    cr_assert_stdout_eq_str("Displaying help...\n");
    cr_assert_eq(result, 84);
}
Test(handle_flags_bis, handle_p_flag)
{
    int flags_present = 0;
    char *av[] = {"./zappy_server", "-p", "1234"};
    int ac = 3;
    int i = 1;

    int result = handle_flags_bis(ac, av, i, &flags_present);
    cr_assert_eq(result, 0);
    cr_assert_eq(flags_present, 1 << 0);
}