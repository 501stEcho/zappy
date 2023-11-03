##
## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-valentin.nouri
## File description:
## Makefile
##

CC				=	gcc

INCLUDEFLAGS	=	-I ./include -I ../include

CFLAGS		=	-Wall -Wextra -Werror -g3

LDFLAGS			=

SRC_DIR			=	./src

BUILDDIR		=	./obj

SRC				=	./src/circular_buffer/circular_buffer.c \
					./src/circular_buffer/getter.c \
					./src/circular_buffer/setter.c \
					./src/command/command.c \
					./src/command/token.c \
					./src/communication/communication.c \
					./src/communication/enqueue.c \
					./src/server/clients_management.c \
					./src/server/fdsets_management.c \
					./src/server/infos.c \
					./src/server/select_management.c \
					./src/server/server.c \
					./src/server/socket_management.c \
					./src/linked_list.c

OBJ				=	$(SRC:$(SRC_DIR)/%$(.c)=$(BUILDDIR)/%.o)

TESTS_NAME		=	unit_tests

TEST_DIR		=	tests/

TEST_SRC		=	$(SRC) \
					tests/tests_circular_buffers_getters.c \
					tests/tests_circular_buffers_setters.c \
					tests/tests_circular_buffers.c \
					tests/tests_command.c \
					tests/tests_communication.c \
					tests/tests_extraction.c \
					tests/tests_linked_list.c \
					tests/tests_linked_tail.c \
					tests/tests_token.c

$(BUILDDIR)/%.o: $(SRC_DIR)/%$(.c)
	@mkdir -p $(dir $@)
	$(CC) -MD $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

NAME	=	libnetwork.a

$(NAME):	$(OBJ)
	@echo -e "\033[1;38;5;92mCompile \033[21m$(NAME)\033[0m"
	ar rc $(NAME) $(OBJ) $(LDFLAGS)

all:	$(NAME)

clean: clean_libnetwork tests_clean

clean_libnetwork:
	@echo -e "\033[1;31mCleaning \033[21m$(NAME)\033[1;24m OBJ\033[0m"
	rm -rf $(BUILDDIR)

fclean:	fclean_libnetwork

fclean_libnetwork: clean tests_clean
	@echo -e "\033[1;31mcleaning \033[21m$(NAME)\033[1;24m binary\033[0m"
	rm -f $(NAME)

re:	fclean all

tests_clean:
	@echo -e "\033[1;31mCleaning unit tests files\033[0m"
	rm -f *.gcda
	rm -f *gcno
	rm -f $(TESTS_NAME)

unit_tests:
	$(CC) -o $(TESTS_NAME) $(TEST_SRC) $(INCLUDEFLAGS) \
	-lcriterion --coverage $(LDFLAGS)

tests_run:	tests_clean unit_tests
	./$(TESTS_NAME)
	gcovr --exclude $(TEST_DIR) --branches

-include $(OBJ:%.o=%.d)

.PHONY:	all \
		clean clean_libnetwork \
		fclean fclean_libnetwork \
		re \
		tests_clean unit_tests tests_run
