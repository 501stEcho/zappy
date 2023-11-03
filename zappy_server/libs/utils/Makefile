##
## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-valentin.nouri
## File description:
## Makefile
##

CC				=	gcc

EXTENSION		=	.c

INCLUDEFLAGS	=	-I ./include

CXXFLAGS		=	-Wall -Wextra -Werror -g3

LDFLAGS			=	-lm

SRC_DIR			=	./src

BUILDDIR		=	./obj

SRC				=	./src/time.c \
					./src/vector.c

OBJ				=	$(SRC:$(SRC_DIR)/%$(EXTENSION)=$(BUILDDIR)/%.o)

TESTS_NAME		=	unit_tests

TEST_DIR		=	tests/

TEST_SRC		=	$(SRC) \
					tests/tests_time.c \
					tests/tests_vector.c

$(BUILDDIR)/%.o: $(SRC_DIR)/%$(EXTENSION)
	@mkdir -p $(dir $@)
	$(CC) -MD $(CXXFLAGS) $(INCLUDEFLAGS) -c $< -o $@

NAME	=	libutils.a

$(NAME):	$(OBJ)
	@echo -e "\033[1;38;5;92mCompile \033[21m$(NAME)\033[0m"
	ar rc $(NAME) $(OBJ) $(LDFLAGS)

all:	$(NAME)

clean: clean_libutils tests_clean

clean_libutils:
	@echo -e "\033[1;31mCleaning \033[21m$(NAME)\033[1;24m OBJ\033[0m"
	rm -rf $(BUILDDIR)

fclean:	fclean_libutils

fclean_libutils: clean tests_clean
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
		clean clean_libutils \
		fclean fclean_libutils \
		re \
		tests_clean unit_tests tests_run
