SOURCES =	main.c prompt.c parser.c token.c signals.c clean.c init.c utils.c \
			parser_cmds.c validate_pipes.c validate_redirections.c builtins.c \
			executor.c files.c pipes.c path.c exec_utils.c files_2.c parser_quotes.c
SOURCES +=	cd.c echo.c env.c export.c pwd.c unset.c parser_pipes.c token_utils.c

NAME = minishell
LIBFT = libft/libft.a
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${notdir ${SOURCES:.c=.o}}}
VPATH :=	${SRCS_PATH} ${SRCS_PATH}/built_in ${SRCS_PATH}/clean \
			${SRCS_PATH}/main ${SRCS_PATH}/parser ${SRCS_PATH}/utils \
			${SRCS_PATH}/executor
CC = gcc
FLAGS =  -Werror -Wextra -Wall -g

# Colors
GREEN = \33[1;32m
L_CYAN = \33[1;36m
L_BLUE = \33[1;34m
L_GREEN = \33[1;92m
L_PURPLE = \33[1;35m
NC = \033[0m

all: ${NAME}

bonus: ${BONUS}

${OBJS_PATH}/%.o: %.c
	@ mkdir -p ${OBJS_PATH}
	@ echo "Compiling: $<"
	@ ${CC} -c $< -o $@ -I libft/include/ -I include/

${NAME}: ${LIBFT} ${OBJS}
	@ ${CC} ${OBJS} -lreadline ${LIBFT} -o ${NAME}
	@ echo "${GREEN}${NAME} successfully compiled!${NC}"

${LIBFT}: 
	@ make -C libft/ --no-print-directory

clean:
	@ rm -rf ${OBJS_PATH}
	@ echo "${L_CYAN}Objects deleted!${NC}"

fclean: clean
	@ make fclean -C libft/ --no-print-directory
	@ rm -rf ${NAME}
	@ echo "${L_BLUE}push_swap deleted!${NC}"
	
re: fclean all

norma:
		norminette ${SRCS} include/

val: ${NAME}
	valgrind --suppressions=./local.supp --leak-check=full ./minishell

valg: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: clean re all fclean
