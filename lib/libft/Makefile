# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 13:46:22 by mosantos          #+#    #+#              #
#    Updated: 2025/09/16 12:28:39 by mosantos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = ./libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
DELETE = rm -f
SRCS = ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strlen.c \
       ft_isalpha.c \
       ft_isdigit.c \
	ft_isspace.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_strmapi.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_striteri.c \
       ft_split.c \
       ft_itoa.c \
       ft_utils.c \
       ft_utils2.c \
       ft_printf.c \
       ft_atoll.c \
	ft_atoll_base.c \
       get_next_line.c \
       get_next_line_utils.c \
       $(BONUS_SRCS)

BONUS_SRCS = ft_lstnew_bonus.c \
	     ft_lstsize_bonus.c \
	     ft_lstadd_front_bonus.c \
	     ft_lstlast_bonus.c \
	     ft_lstadd_back_bonus.c \
	     ft_lstiter_bonus.c \
	     ft_lstdelone_bonus.c \
	     ft_lstclear_bonus.c \
	     ft_lstmap_bonus.c


OBJ = $(SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar -rcs $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	ar -rcs $(NAME) $(BONUS_OBJ)

$(OBJ):	$(INC)

$(BONUS_OBJ):	$(INC)

clean:
		$(DELETE) $(OBJ) $(BONUS_OBJ)

fclean: clean
		$(DELETE) $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
