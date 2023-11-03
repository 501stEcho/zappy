##
## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-valentin.nouri
## File description:
## Makefile
##

SRC	=	utils/ network/

all:
	@for subdir in $(SRC); do\
		make --no-print-directory -C $$subdir;\
	done
	cp ./**/*.a .

clean:
	@for subdir in $(SRC); do\
		make --no-print-directory clean -C $$subdir;\
	done

fclean:
	@for subdir in $(SRC); do\
		make --no-print-directory fclean -C $$subdir;\
	done
	rm -f ./*.a

re: fclean all

tests_run:
	@for subdir in $(SRC); do\
		make --no-print-directory tests_run -C $$subdir;\
	done

tests_clean:
	@for subdir in $(SRC); do\
		make --no-print-directory tests_clean -C $$subdir;\
	done
