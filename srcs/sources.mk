# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2019/12/08 15:41:29 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \

C_FILES_parser = \
	parser.c \
	misc.c \
	tokenizer.c \
	dynamic_arrays.c \
	parse_error.c \
	wordexp_tokenizer.c	\
	wordexp_misc.c \
	stack.c \
	free_tree.c \

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
