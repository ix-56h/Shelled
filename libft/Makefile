# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 19:34:49 by niguinti          #+#    #+#              #
#    Updated: 2020/03/01 12:28:17 by ezonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= libft.a

# All the directories needed to know where files should be (Can be changed)

OBJDIR		= objects/
SRCDIR		= sources/
INCDIR		= ./incs/

# Source files (Can be changed)

SRC			=	ft_atoi.c         ft_islower.c      ft_memcpy.c       ft_putendl.c      ft_sort_tab.c     ft_strcmp.c       ft_strjoin.c      ft_strncmp.c      ft_strsplit.c	\
				ft_bzero.c        ft_isprint.c      ft_memdel.c       ft_putendl_fd.c   ft_split_n_trim.c ft_strcpy.c       ft_strjoinf.c     ft_strncpy.c      ft_strstr.c		\
 				ft_ftoa.c         ft_itoa_base.c    ft_memmove.c      ft_putnbr.c       ft_strcat.c       ft_strdel.c       ft_strlcat.c      ft_strnequ.c      ft_strsub.c		\
 				ft_isalnum.c      ft_memalloc.c     ft_memset.c       ft_putnbr_fd.c    ft_strcdup.c      ft_strdup.c       ft_strlen.c       ft_strnew.c       ft_strtrim.c	\
				ft_isalpha.c      ft_memccpy.c      ft_nbrlen_base.c  ft_putstr.c       ft_strchr.c       ft_strequ.c       ft_strmap.c       ft_strnstr.c      ft_strtrimf.c	\
				ft_isascii.c      ft_memchr.c       ft_putchar.c      ft_putstr_fd.c    ft_strclen.c      ft_striter.c      ft_strmapi.c      ft_strrchr.c      ft_tolower.c	\
				ft_isdigit.c      ft_memcmp.c       ft_putchar_fd.c   ft_size_digit.c   ft_strclr.c       ft_striteri.c     ft_strncat.c      ft_strrev.c       ft_toupper.c	\
				ft_isdigits.c	  ft_strichr.c		ft_calloc.c		  ft_strljoin.c  	ft_strreplace.c   ft_free.c			ft_vjoin.c 		  ft_vprint.c		ft_vprintfd.c   \
				ft_itoa.c		  ft_isalldigit.c																																	\
				ft_tablen.c \
				ft_isalnum_str.c \
				ft_isportable.c
# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
CHECKDIR	= $(shell if [ ! -d "$(OBJDIR)" ]; then	mkdir $(OBJDIR); fi)

# How files should be compiled with set flags (Can be changed)

OBJ			= $(SRC:.c=.o)
CFLAGS		= -I$(INCDIR) -Wall -Wextra -Werror -g3
#CFLAGS		= -I$(INCDIR) -Wall -Wextra -Werror -g3
#CFLAGS		= -I$(INCDIR) -Wall -Wextra -Werror -g3 -fsanatize=address
CC			= gcc

# Build the library when all .c files are compiled into .o files and then indexing it

$(NAME): $(CHECKDIR) $(COBJ)
	@echo "\033[33m\n      - Building \033[0m$(NAME) \033[33m...\n\033[0m"
	@ar rc $(NAME) $(COBJ)
	@echo "\033[33m      - Indexing \033[0m$(NAME) \033[33m...\n\033[0m"
	@ranlib $(NAME)
	@echo "\033[32m***   Project $(NAME) successfully compiled   ***\n\033[0m"

all: $(NAME)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "\033[33m      - Compiling :\033[0m" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Deleting all .o files and then the directory where they were located

clean:
	@echo "\033[32m***   Deleting all object files from $(NAME)   ...   ***\n\033[0m"
	@rm -rf $(COBJ)

# Deleting the library after cleaning up all .o files

fclean: clean
	@echo "\033[32m***   Deleting executable file from $(NAME)   ...   ***\n\033[0m"
	@rm -rf $(NAME)

# Delete all .o files then the library and rebuild the whole thing again

re: fclean all

.PHONY: all clean fclean re
