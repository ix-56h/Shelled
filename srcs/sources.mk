# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2019/12/23 01:52:57 by niguinti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \

C_FILES_parser = \
	parser.c \
	misc.c \
	dynamic_arrays.c \
	parse_error.c \
	stack.c \
	free_tree.c \

C_FILES_tokenizer = \
	tokenizer.c \
	wordexp_tokenizer.c	\
	wordexp_misc.c \

C_FILES_ast_visitor = \


# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
