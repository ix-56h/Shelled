# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:36 by thdelmas          #+#    #+#              #
#    Updated: 2020/02/02 23:53:43 by akeiflin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###

H_FILES				=	error_handler.h \

H_FILES_expansions 	= 	\
						expansions.h \

H_FILES_utils 		= 	\
						ast.h \
						double_linked_list.h \
						stack.h \

H_FILES_builtins 	= 	\
						builtins.h \

H_FILES_line_edit 	= 	\
						ligne.h \
						historique.h \

H_FILES_parser 		=	\
						parser.h \

H_FILES_shell 		=	\
						sh.h \


H_FILES_tokenizer 	=	\
						error_class.h \
						tokenizer.h \
						tokenizer_rules.h \
						wexp_rules.h \

H_FILES_visitor 	=	\
						visitor.h \
						visitor_rules.h \
						exec.h \

# SUPPA concat loop
H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
