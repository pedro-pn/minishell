SOURCES =	main.c prompt.c parser.c signals.c clean.c init.c utils.c \
			validate_pipes.c validate_redirections.c builtins.c \
			executor.c files.c pipes.c path.c exec_utils.c files_2.c \
			parser_quotes.c cd.c echo.c env.c export.c pwd.c unset.c \
			parser_quotes_2.c utils_2.c parser_utils.c \
			expansion.c init_2.c utils_3.c exec_wait.c \
			signals_2.c export_utils.c expansion_utils.c prompt_utils.c \
			utils_4.c wildcard.c

PP_SOURCES := main.c parser.c clean.c init.c utils.c builtins.c executor.c \
			files.c pipes.c path.c exec_utils.c files_2.c parser_quotes.c export.c \
			unset.c parser_quotes_2.c utils_2.c parser_utils.c expansion.c init_2.c utils_3.c \
			exec_wait.c signals_2.c export_utils.c expansion_utils.c prompt_utils.c utils_4.c wildcard.c

NAME = minishell
LIBFT = libft/libft.a
SRCS_PATH = srcs
OBJS_PATH = objs
MY_SRCS = ${addprefix ${SRCS_PATH}/, ${notdir ${MY_SOURCES}}}
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
	@ ${CC} ${FLAGS} -c $< -o $@ -I libft/include/ -I include/

${NAME}: ${LIBFT} ${OBJS}
	@ ${CC} ${FLAGS} ${OBJS} -lreadline ${LIBFT} -o ${NAME}
	@ echo "${GREEN}${NAME} successfully compiled!${NC}"

${LIBFT}: 
	@ make -C libft/ --no-print-directory

clean:
	@ rm -rf ${OBJS_PATH}
	@ echo "${L_CYAN}Objects deleted!${NC}"

fclean: clean
	@ make fclean -C libft/ --no-print-directory
	@ rm -rf ${NAME}
	@ echo "${L_BLUE}minishell deleted!${NC}"
	
re: fclean all

norma: ${PP_SOURCES}
		norminette $^ include/


aa: ${MY_SOURCES}
	echo $^
val: ${NAME}
	valgrind --suppressions=./local.supp --leak-check=full ./minishell

valg: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: clean re all fclean
