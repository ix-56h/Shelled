# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    includes.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 14:33:36 by thdelmas          #+#    #+#              #
#    Updated: 2019/12/30 17:29:38 by niguinti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
H_FILES =	\
			error_class.h \
			error_handler.h \
			parser.h \
			stack.h \
			tokenizer.h \
			tokenizer_rules.h \
			visitor.h \
			visitor_rules.h \
			wexp_rules.h \
			sh.h \


# SUPPA concat loop
H_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(H_FILES_$(SUB_DIR))))
