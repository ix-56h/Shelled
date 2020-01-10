# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2020/01/10 18:36:56 by akeiflin         ###   ########.fr        #
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

C_FILES_visitor = \
					  visitor.c \

C_FILES_shell = \
				main.c \
				env.c \

C_FILES_line_edit = \
					alloc.c \
					clear.c \
					controleur.c \
					garbage.c \
					get_things.c \
					historique.c \
					ligne.c \
					line_edit.c \
					line_key1.c \
					line_key2.c \
					line_misc.c \
					move.c \
					term_misc.c \

C_FILES_builtins = \

C_FILES_utils = \
				double_linked_list.c \
				# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
