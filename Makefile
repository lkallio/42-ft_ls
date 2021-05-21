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

NAME = ft_ls
SRC = ft_ls.c ls_exceptions.c ls_files.c ls_glob.c ls_lf.c ls_print.c \
	ls_strutils.c ls_utils.c
SRCDIR = src
OBJ = $(SRC:.c=.o)
OBJDIR = obj
INC = includes
PF = printf/libftprintf.a
PFINC = printf/includes
FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || (mkdir -p $(OBJDIR) && printf "Created directory \e[38;5;136m$(OBJDIR)\e[37m\n\n")
	@gcc $(FLAGS) -c $< -I $(INC) -I $(PFINC) -o $@
	@printf "\e[F\e[JCompiling $<\nWaiting for compilation..."

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@printf "\e[F\e[JCompiled \e[38;5;111m$(subst obj/,,$?)\e[37m\n\007Making printf...\n"
	@make -C printf
	@printf "\e[F\e[JPrintf done!\n"
	@gcc $(FLAGS) -o $(NAME) $^ -I $(INC) $(PF) -I $(PFINC)
	@printf "Compiled binary \e[38;5;37m$(NAME)\e[37m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\e[38;5;210mRemoved $(OBJDIR)\e[37m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\e[38;5;210mRemoved $(NAME)\e[37m\n"
	@make -C printf fclean
	@printf "\e[38;5;210mRemoved printf/obj\e[37m\n"
	@printf "\e[38;5;210mRemoved printf/libftprintf.a\e[37m\n"

re: fclean all
