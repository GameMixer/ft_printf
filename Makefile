# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 19:09:15 by gderenzi          #+#    #+#              #
#    Updated: 2017/04/06 15:16:03 by gderenzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
SRC			= ft_printf.c

OBJ			= $(addprefix $(OBJDIR),$(SRC:.c=.o))

LIBDIR		= ./libft
LIBFT		= $(LIBDIR)/libft.a
LIBINC		= -I$(LIBDIR)/includes/
LIBLINK		= -L$(LIBDIR) -lft

SRCDIR		= ./src/
INCDIR		= ./includes/
OBJDIR		= ./obj/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBDIR)

$(addprefix $(OBJDIR), %.o): $(addprefix $(SRCDIR), %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(LIBINC) -I $(INCDIR) -o $@ -c $<

clean:
	$(MAKE) clean -C $(LIBDIR)
	@rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all
