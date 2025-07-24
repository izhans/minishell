# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

VPATH = /:src/:

SRC	=

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