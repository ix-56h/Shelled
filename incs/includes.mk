# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:36 by thdelmas          #+#    #+#              #
#    Updated: 2020/01/12 00:44:43 by akeiflin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###

H_FILES		=	parser.h \
				ast.h \
				error_class.h \
				error_handler.h \
				stack.h \
				tokenizer.h \
				tokenizer_rules.h \
				wexp_rules.h \
				visitor_rules.h \
				sh.h \
				builtins.h \
# SUPPA concat loop
#H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
