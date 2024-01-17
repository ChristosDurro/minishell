SRCS = main.c utils.c lexer/lexer.c lexer/lexer_utils.c \
	lexer/token.c signals/signals.c \
	env.c builtins/echo.c parser/parser.c builtins/pwd.c builtins/cd.c \
	builtins/export.c builtins/unset.c executor/executor.c \
	executor/child_processes.c executor/executor_utils.c \
	executor/redirections.c executor/redirections_utils.c \
	executor/redirections_heredoc.c executor/heredoc_expand.c\
	builtins/utils.c builtins/exit.c free.c expansion.c \
	parser/parser_utils.c parser/redirection_parsing.c \
	expansion_utils.c

OBJS = ${SRCS:.c=.o}

NAME = minishell

HEADER = minishell.h

LIBFT = libft
LIBFT_LIB = libft/libft.a

CC = cc
CFLAGS =  -Wall -Werror -Wextra #-g #-fsanitize=address

all: ${NAME}

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


${LIBFT_LIB}:
	make -C ${LIBFT}

${NAME}: ${OBJS} ${LIBFT_LIB}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME} -lreadline

clean:
	make clean -C  ${LIBFT}
	rm -f ${OBJS} ${LIBFT_LIB}

fclean: clean
	make fclean -C  ${LIBFT}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
