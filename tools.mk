# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tools.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/28 17:25:36 by thdelmas          #+#    #+#              #
#    Updated: 2019/12/08 16:29:38 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### Tools ####################################

AUTHORS ?= Thdelmas

### Escape Sequences ###
SCURSOR = \033[s
RCURSOR = \033[u
ERASEL = \033[2K

RESET		= \033[0m
### Colors ###
WHITE = \033[1;37m
CYAN = \033[36m
GREEN = \033[1m\033[32m
GRED = \033[30;41m
WRED = \033[96;41m
BRED = \033[0;31;40m
BBLUE = \033[0;36m
BBBLUE = \033[1;36m
WBLUE = \033[31;44m
YELLOW = \033[33m
CLEAR = \033[0;0m

GITCOM ?= "Auto-Save"
GITSTATUS = $(shell git status | sed -n 2p | cut -d' ' -f4)
ADD_TO_NORME = $(SRC_DIR) $(INC_DIR) $(FT_DIR)

ADD_TO_GIT = $(SRC_DIR) $(INC_DIR) $(FT_DIR) $(GITLOG_FILE) \
			 Makefile tools.mk auteur README.md

.PHONY: hey link compil savegit gitsave norm


### Norminette ###
.ONESHELL:
norm:
	@printf "\n$(BRED)\t NORM 42$(CLEAR)\n"
	@printf "$(BRED)\t $(ADD_TO_NORME)$(CLEAR)\n"
	@norminette -R CheckForbiddenSourceHeader $(HEADER) $(SRC_NAME)

### Messages rules ###
hey_msg:
	@printf "$(BBBLUE)\t$(PROJECT)$(CLEAR)\n"

bye_msg: | hey_msg
	@printf "$(BRED)By: $(CLEAR)$(WHITE)$(AUTHORS)$(CLEAR)\n"

run_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)RUN$(CLEAR)\n"
	@printf "$(BRED)By: $(CLEAR)$(WHITE)$(AUTHORS)$(CLEAR)\n"

test_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)TEST$(CLEAR)\n"

lib_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)LIBS$(CLEAR)\n"

compil_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)COMPIL$(CLEAR)\n"

link_msg: | hey_msg
	@printf "\n$(BRED)$(PROJECT): $(CLEAR)$(WHITE)LINK$(CLEAR)\n"

mkdir_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)MKDIR$(CLEAR)\n"

fclean_msg: | hey_msg
	@printf "$(BRED)$(PROJECT): $(CLEAR)$(WHITE)FCLEAN$(CLEAR)\n"

clean_msg: | hey_msg
	@printf "\n$(BRED)$(PROJECT): $(CLEAR)$(WHITE)CLEAN$(CLEAR)\n"

