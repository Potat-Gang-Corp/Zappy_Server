##
## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME = zappy_server
TESTNAME = unit_tests

CC = gcc
RM = rm -rf
ECHO = /bin/echo -e

GREEN	= \x1b[36m
RED		= \033[0;31m
RESET	= \033[0m

SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name '*.c')
TSRCS = $(wildcard tests/unit-tests/*.c)

SRCS_NO_MAIN = $(filter-out src/main.c, $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJS_NO_MAIN = $(SRCS_NO_MAIN:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror --coverage
LDFLAGS = --coverage -lcriterion
GCOVRFLAGS = -r . --exclude 'tests/*'

all: $(NAME)

$(NAME): $(OBJS)
	@$(ECHO) "$(GREEN)Compiling $@$(RESET) ..."
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTNAME): $(TOBJS) $(OBJS_NO_MAIN)
	$(CC) -o $(TESTNAME) $(TOBJS) $(OBJS_NO_MAIN) $(CFLAGS) $(LDFLAGS)

tests_run: $(TESTNAME)
	@$(ECHO) "$(GREEN)Compiling unit tests $(RESET) ..."
	@gcovr $(GCOVRFLAGS)
	@gcovr $(GCOVRFLAGS) --html --html-details -o tests/coverage.html
	@echo "Coverage report generated in coverage.html"

run_ftests:
	@./tests/functional-tests/test.sh

clean:
	@$(ECHO) "$(RED)Cleaning objects and temporary files ...$(RESET)"
	$(RM) $(OBJS) $(TOBJS)
	find src -name '*.gc*' -exec $(RM) {} +
	$(RM) *.gc* $(TESTNAME) coverage.html
	$(RM) tests/*.gc*
	$(RM) tests/unit-tests/*.gc*
	$(RM) tests/coverage*
	$(RM) coverage*
	$(RM) coding-style-reports.log

fclean: clean
	@$(ECHO) "$(RED)Cleaning executable...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
