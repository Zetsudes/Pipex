# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamohame <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 11:20:25 by zamohame          #+#    #+#              #
#    Updated: 2024/11/15 18:55:59 by zamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
AR = ar

SRC = ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_strlen.c \
      ft_memset.c \
      ft_bzero.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_strlcpy.c \
      ft_strlcat.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_strncmp.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strnstr.c \
      ft_atoi.c \
      ft_calloc.c \
      ft_strdup.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      print_greg/ft_printf.c \
      print_greg/handle_char.c \
      print_greg/handle_hex.c \
      print_greg/handle_number.c \
      print_greg/handle_percent.c \
      print_greg/handle_pointer.c \
      print_greg/handle_string.c \
      print_greg/handle_unsigned.c \
      greg_next_line/get_next_line.c \

BSRC = ft_lstnew.c \
       ft_lstadd_front.c \
       ft_lstsize.c \
       ft_lstlast.c \
       ft_lstadd_back.c \
       ft_lstdelone.c \
       ft_lstclear.c \
       ft_lstiter.c \
       ft_lstmap.c \

OBJ = $(SRC:.c=.o) 

BONUS_OBJ = $(BSRC:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) -r $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(BONUS_OBJ)
	$(AR) -r $(NAME) $(OBJ) $(BONUS_OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
