# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/15 12:30:26 by lkallio           #+#    #+#              #
#    Updated: 2020/02/14 14:25:01 by lkallio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = dbl_data.c ft_printf.c handle_double.c handle_ints.c \
		handle_buffer.c handle_n_str.c pf_utils.c write_double.c write_ints.c
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes/
FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@gcc -g $(FLAGS) -c $< -I $(INC) -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	ar rcs $(NAME) $?

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
