# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

VPATH = /:src/:

SRC	= 	\
		built-ins/ft_echo.c \
		built-ins/ft_env.c \
		built-ins/ft_exit.c \
		built-ins/ft_export.c \
		built-ins/ft_pwd.c \
		exec/exec_utils.c \
		exec/exec.c \
		exec/pipeline.c \
		exec/redirections.c \
		exec/redirections_utils.c \
		expand/clear.c \
		expand/env_utils.c \
		expand/expand_clear.c \
		expand/expand.c \
		parser/parser_utils.c \
		parser/parser.c \
		structures/t_command_utils.c \
		structures/t_envp_utils.c \
		structures/t_line_utils.c \
		structures/t_minishell_utils.c \
		structures/t_redir_utils.c \
		minishell.c \
		utils.c \
		here_doc.c \
		validator.c

OBJ_DIR = objects
OBJ =	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT = libft/libft.a

RDL_LINK =	-lreadline

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(RDL_LINK) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(dir $(LIBFT))

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(dir $(LIBFT)) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(dir $(LIBFT)) fclean
	rm -f $(NAME)

re: fclean all