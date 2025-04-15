
LIBFT_DIR = greg_lib
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIE

SRC = src/pipex.c \
	  src/error.c \
	  src/parsing.c \
	  src/path.c \

BONUS_SRC = bonus/pipex.c \
	 	bonus/error.c \
	  	bonus/parsing.c \
	  	bonus/path.c \

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = pipex
BONUS_NAME = pipex_bonus

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -Iinclude -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: all clean fclean re
