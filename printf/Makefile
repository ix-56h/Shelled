# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 19:34:36 by niguinti          #+#    #+#              #
#    Updated: 2020/02/10 15:19:49 by niguinti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= libprintf.a

# All the directories needed to know where files should be (Can be changed)

OBJDIR		= objects/
SRCDIR		= sources/
INCDIR		= ./includes/

# Source files (Can be changed)

SRC			=	colors.c			\
				colors_suit.c		\
				ft_strlen.c			\
				ft_toupper.c		\
				ft_printf.c			\
				ft_atoi.c			\
				ft_bzero.c			\
				ft_isdigit.c		\
				ft_nbrlen_base.c	\
				ft_size_digit.c		\
				ft_strcmp.c			\
				dprintf.c			\
				vprintf.c			\
				vdprintf.c			\
				bdprintf.c			\
				utils.c				\
				utils_handlers.c	\
				utils_diouf.c		\
				handler.c			\
				handler_i.c			\
				handler_u.c			\
				handler_c.c			\
				handler_s.c			\
				handler_p.c			\
				handler_x.c			\
				handler_o.c			\
				handler_percent.c	\
				handler_f.c			\

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libft and then the Project

all: $(NAME)

$(NAME): $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@ar rc $(NAME) $(COBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Deleting all .o files and then the directory where they were located

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(COBJ)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
