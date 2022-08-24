SOURCES =	main.c prompt.c parser.c token.c signals.c clean.c
NAME = minishell
LIBFT = libft/libft.a
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${SOURCES:.c=.o}}
CC = gcc
FLAGS =  -Werror -Wextra -Wall

# Colors
GREEN = \33[1;32m
L_CYAN = \33[1;36m
L_BLUE = \33[1;34m
L_GREEN = \33[1;92m
L_PURPLE = \33[1;35m
NC = \033[0m

all: ${NAME}

bonus: ${BONUS}

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.c
					@ mkdir -p ${OBJS_PATH}
					@ echo "Compiling: $<"
					@ ${CC} ${FLAGS} -c $< -o $@ -I libft/include/ -I include/

${NAME}: ${LIBFT} ${OBJS}
			@ ${CC} ${FLAGS} ${OBJS} -lreadline ${LIBFT} -o ${NAME}
			@ echo "${GREEN}${NAME} successfully compiled!${NC}"

${LIBFT}: 
		@ make -C libft/ --no-print-directory

clean:
		@ rm -rf ${OBJS_PATH} ${BOBJS_PATH}
		@ echo "${L_CYAN}Objects deleted!${NC}"

fclean: clean
		@ make fclean -C libft/ --no-print-directory
		@ rm -rf ${NAME} ${BONUS}
		@ echo "${L_BLUE}push_swap deleted!${NC}"
	
re: fclean all

norma:
		norminette ${SRCS} include/
