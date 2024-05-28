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
#include "../../include/get_instance.h"

Test(handle_flags, flags_test)
{
    char *av[] = { "./zappy_server", "-p", "1234", "-x", "100", "-y", "100", "-n", "team1", "-c", "10", "-f", "50" };
    int ac = 11;

    int result = handle_flags(ac, av);
    cr_assert_eq(result, 0);
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

Test(handle_flags_bis, handle_x_y_flags)
{
    int flags_present = 0;
    char *av[] = {"./zappy_server", "-x", "10", "-y", "10"};
    int ac = 5;
    int i = 1;

    int result = handle_flags_bis(ac, av, i, &flags_present);
    cr_assert_eq(result, 0);
}

Test(handle_flags_bis, handle_n_c_f_flags)
{
    int flags_present = 0;
    char *av[] = {"./zappy_server", "-n", "team", "-c", "5", "-f", "10"};
    char *av_port_error[7] = {"./zappy_server", "-n", "team", "-c", "5", "-p", "a"};
    char *av_x_y_error[7] = {"./zappy_server", "-n", "team", "-c", "5", "-x", "a"};
    char *av_x_y_error_bis[7] = {"./zappy_server", "-n", "team", "-c", "5", "-y", "a"};
    char *av_c_error[7] = {"./zappy_server", "-n", "team", "-x", "10", "-c", "a"};
    char *av_f_error[7] = {"./zappy_server", "-n", "team", "-x", "10", "-f", "a"};
    char *av_n_error[6] = {"./zappy_server", "-n", "-x", "10", "-f", "a"};
    int ac = 7;
    int i = 1;

    int result = handle_flags_bis(ac, av, i, &flags_present);
    cr_assert_eq(result, 0);
    i = 5;
    cr_assert_eq(handle_flags_bis(7, av_port_error, i, &flags_present), 84, "Expected error code 84 because invalid definition of the port");
    cr_assert_eq(handle_flags_bis(7, av_x_y_error, i, &flags_present), 84, "Expected error code 84 because invalid definition of the x parameter");
    cr_assert_eq(handle_flags_bis(7, av_x_y_error_bis, i, &flags_present), 84, "Expected error code 84 because invalid definition of the y parameter");
    cr_assert_eq(handle_flags_bis(7, av_c_error, i, &flags_present), 84, "Expected error code 84 because invalid definition of the c parameter");
    cr_assert_eq(handle_flags_bis(7, av_f_error, i, &flags_present), 84, "Expected error code 84 because invalid definition of the f parameter");
    i = 1;
    cr_assert_eq(handle_flags_bis(7, av_n_error, i, &flags_present), 84, "Expected error code 84 because invalid definition of the n parameter");
}

Test(display_help, checking_display_help_return_value) {
    int result = display_help();
    cr_assert_eq(result, 84, "Expected error code 84 to display the help message");
}

Test(check_av, checking_argument_definition_of_flag) {
    char *no_valid_arg_def[12] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "a", "-n", "the", "potato", "group", "-c"};
    char *no_valid_arg_def_bis[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-f", "a"};
    char *no_valid_arg_def_third[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-f", "-c"};
    char *valid_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-f", "10"};

    int i = 11;

    cr_assert_eq(check_av(i, 12, no_valid_arg_def), 84, "Expected exit code 84 because no arguments after the flag");

    i = 11;

    cr_assert_eq(check_av(i, 13, no_valid_arg_def_bis), 0, "Expected exit code 0 because no valid argument after the flag");


    i = 11;

    cr_assert_eq(check_av(i, 13, no_valid_arg_def_third), 84, "Expected exit code 0 because no valid argument after the flag");

    i = 11;
    int result = check_av(i, 13, valid_def);
    cr_assert_eq(result, 0, "Expected exit code 0 because definition valid argument after the flag");
}

Test(handle_fp, checking_presence_arguments) {
    cr_assert_eq(handle_fp(1), 84);
    cr_assert_eq(handle_fp(2), 84);
    cr_assert_eq(handle_fp(7), 84);
    cr_assert_eq(handle_fp(15), 84);
    cr_assert_eq(handle_fp(31), 0);
}

Test(handle_flags, checking_detection_help_flag) {
    char *av_help[2] = {"./zappy_server", "-h"};

    char *av_bad_arguments[3] = {"./zappy_server", "-p", "a"};

    char *av_not_enougth_args[3] = {"./zappy_server", "-p", "1000"};

    char *valid_def_without_f[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-c", "10"};

    cr_assert_eq(handle_flags(2, av_help), 84);

    cr_assert_eq(handle_flags(3, av_bad_arguments), 84);

    cr_assert_eq(handle_flags(3, av_not_enougth_args), 84);

    cr_assert_eq(handle_flags(13, valid_def_without_f), 0);


    char *args[] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "team1", "-c", "5", "-f", "100"};
    game_t *game = get_game_instance();
    
    int result = handle_flags(12, args);
    
    cr_assert_eq(result, 0, "Expected result to be 0 for valid flags");
    cr_assert_eq(game->freq, 100, "Expected game frequency to be set to 100 when the frequency flag is present");

}
