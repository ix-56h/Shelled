# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 18:06:27 by niguinti          #+#    #+#              #
#    Updated: 2020/01/02 18:50:08 by akeiflin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := 21sh
PROJECT := 21SH
AUTHORS := Niguinti

RM = /bin/rm

### Directories ###
SRC_DIR := ./srcs
INC_DIR := ./incs
OBJ_DIR := ./.obj

### SUB FILES ###
SUB_DIRS := \
	tokenizer \
	parser \
	ast_visitor \
	shell \
	builtins \
	utils \
	line_edit \


### INCLUDE SRC MAKEFILE ###
include $(SRC_DIR)/sources.mk

### INCLUDE INC MAKEFILE ###
include $(INC_DIR)/includes.mk


### ALL SUB DIRS ###
SRC_SUB_DIRS = $(addprefix $(SRC_DIR)/,$(SUB_DIRS))
OBJ_SUB_DIRS = $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))
INC_SUB_DIRS = $(addprefix $(INC_DIR)/,$(SUB_DIRS))


### MAIN AND SUB FILES ###
O_FILES = $(C_FILES:.c=.o)


### Full Paths ###
SRC = $(addprefix $(SRC_DIR)/,$(C_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(O_FILES))
INC = $(addprefix $(INC_DIR)/,$(H_FILES))


### Lib ###
FT = ft
FT_DIR = ./lib$(FT)
FT_INC_DIR = $(FT_DIR)/incs
FT_LNK = -L$(FT_DIR) -l$(FT)

###  CC && FLAGS ###
CC = clang -g
DEBUG_FLAGS = -g3
NO_WARNING ?= false
ifeq ($(NO_WARNING), false)
CFLAGS = \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR)) \
		 -Wall -Werror -Wextra
else
CFLAGS = \
		 $(addprefix -I ,$(INC_DIR) $(INC_SUB_DIRS) $(FT_INC_DIR))
endif

LFLAGS = -ltermcap \
		 $(FT_LNK) \



.PHONY: all clean fclean re

all: init $(FT) $(NAME) bye_msg

### Lib compil ###
$(FT): | lib_msg
	@make -sC $(FT_DIR)

### Mkdir obj ###
$(OBJ_DIR): | mkdir_msg
	@mkdir -p $(OBJ_DIR) $(OBJ_SUB_DIRS)

### Compilation ###
.ONESHELL:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(MAKEFILE_LIST) | compil_msg
	@echo "$(SCURSOR)$(YELLOW)\t- Compiling:$(RESET)$(@F) \c"
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(RCURSOR)$(ERASEL)\c"

### Link ###
.ONESHELL:
$(NAME): init $(OBJ_DIR) $(OBJ) $(INC) $(MAKEFILE_LIST) $(FT_DIR)/libft.a | link_msg
	@echo "$(YELLOW)\t- Building $(RESET)$(NAME) $(YELLOW)...$(RESET) \c"
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

### Clean ###
$(FT)_clean: | lib_msg
	@make -C $(FT_DIR) clean

clean: $(FT)_clean | clean_msg
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	$(RM) -rf $(OBJ_DIR)

$(FT)_fclean: | lib_msg
	@make -C $(FT_DIR) fclean

fclean: $(FT)_fclean | fclean_msg
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(NAME).dSYM
	$(RM) -rf $(NAME)

re: fclean all

init:
	-@ sh ./.githooks/initme.sh 2>&- || true

### INCLUDE TOOLS MAKEFILE ###
include ./tools.mk
