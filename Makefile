##
## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME = zappy_server
TESTNAME = unit_tests

CC = gcc
RM = rm -f

SRCS = $(wildcard src/*.c)
TSRCS = $(wildcard tests/unit-tests/*.c)

OBJS = $(SRCS:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror
LDFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

$(TESTNAME): $(TOBJS)
	$(CC) -o $(TESTNAME) $(TOBJS) $(CFLAGS) $(LDFLAGS)

tests_run: $(TESTNAME)
	./$(TESTNAME)
	@gcovr --exclude tests/

clean:##
## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME = zappy_server
TESTNAME = unit_tests

CC = gcc
RM = rm -f

SRCS = $(wildcard src/*.c)
TSRCS = $(wildcard tests/unit-tests/*.c)

OBJS = $(SRCS:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror
LDFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

$(TESTNAME): $(TOBJS)
	$(CC) -o $(TESTNAME) $(TOBJS) $(CFLAGS) $(LDFLAGS)

tests_run: $(TESTNAME)
	./$(TESTNAME)
	@gcovr --exclude tests/

clean:
	$(RM) $(OBJS) $(TOBJS)
	$(RM) *.gc* $(TESTNAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run

	$(RM) $(OBJS) $(TOBJS)
	$(RM) *.gc* $(TESTNAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
