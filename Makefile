# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 19:09:15 by gderenzi          #+#    #+#              #
#    Updated: 2017/05/30 12:40:30 by gderenzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
SRC			= ft_printf.c \
			  init.c \
			  check.c \
			  buff.c \
			  handle_format.c \
			  display_num.c \
			  display_char.c \
			  wchar_to_char.c \
			  c_flag.c \
			  d_flag.c \
			  p_flag_undefined.c \
			  s_flag.c \
			  u_o_flag.c \
			  wu_wo_flag.c \
			  x_flag.c \
			  apply_flags.c \
			  util.c \
			  util2.c

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

re: fclean all
