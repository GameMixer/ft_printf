# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 19:09:15 by gderenzi          #+#    #+#              #
#    Updated: 2017/08/06 21:44:46 by gderenzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
SRC			= ft_printf.c \
			  spec_handle.c \
			  prec_handle.c \
			  check.c \
			  num_conv.c \
			  float_conv.c \
			  str_conv.c \
			  wstr_conv.c \
			  char_conv.c \
			  xou_conv.c \
			  bonus.c \
			  vector.c \
			  util.c

OBJ			= $(addprefix $(OBJDIR),$(SRC:.c=.o))

LIBDIR		= ./libft
LIBFT		= $(LIBDIR)/libft.a
LIBINC		= -I$(LIBDIR)/includes/
LIBOBJ		= $(LIBDIR)/obj/
LIBLINK		= -L$(LIBDIR) -lft

SRCDIR		= ./src/
INCDIR		= ./includes/
OBJDIR		= ./obj/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@ar rc $(NAME) $(OBJ) $(LIBOBJ)*.o
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

comp:
	$(CC) $(NAME) $(LIBINC) -I $(INCDIR) main.c

re: fclean all
