/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../include/handle_flags.h"

void handle_c_wrapper(char *av, int *fp) {
    if (fork() == 0) {
        handle_c(av, fp);
        exit(0);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            cr_assert_eq(exit_status, 84, "Expected exit status 84, but got %d", exit_status);
        } else {
            cr_assert_fail("handle_c did not exit normally");
        }
    }
}

Test(handle_c, test_exit_84_invalid_flag) {
    int fp = 0;
    char *buffer = "abc";
    cr_redirect_stderr();

    handle_c_wrapper(buffer, &fp);

    cr_assert_stderr_eq_str("Error: flag -c has no definition\n");
}


 Test(handle_c, test_exit_84_invalid_number) {
     char *argv = "-1";
     int fp = 0;
    cr_redirect_stderr();

    handle_c_wrapper(argv, &fp);

    cr_assert_stderr_eq_str("Error: flag -c has no definition\n");
 }

 Test(handle_c, test_valid_input) {
     char *argv = "3";
     int fp = 0;
     cr_redirect_stderr();
     cr_assert_exit(handle_c(argv, &fp), 0, "Expected exit code 0 for valid input");
 }