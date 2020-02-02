# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2020/02/02 05:22:29 by niguinti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \

C_FILES_parser = \
				 misc.c \
				 parse_and_or.c \
				 parse_cmd_name.c \
				 parse_cmd_prefix.c \
				 parse_cmd_suffix.c \
				 parse_cmd_word.c \
				 parse_command.c \
				 parse_complete_command.c \
				 parse_complete_commands.c \
				 parse_compound_command.c \
				 parse_compound_list.c \
				 parse_error.c \
				 parse_filename.c \
				 parse_here_end.c \
				 parse_io_file.c \
				 parse_io_here.c \
				 parse_io_redirect.c \
				 parse_linebreak.c \
				 parse_list.c \
				 parse_newline_list.c \
				 parse_pipe_sequence.c \
				 parse_pipeline.c \
				 parse_program.c \
				 parse_redirect_list.c \
				 parse_scripting_part1.c \
				 parse_scripting_part2.c \
				 parse_scripting_part3.c \
				 parse_scripting_part4.c \
				 parse_separator.c \
				 parse_separator_op.c \
				 parse_sequential_sep.c \
				 parse_simple_command.c \
				 parse_subshell.c \
				 parse_term.c \

C_FILES_tokenizer = \
					term_and_op_check.c \
					tokenizer.c \
					tokenizer_misc.c \
					wordexp_misc.c \
					wordexp_tokenizer.c \

C_FILES_visitor = \
				  visitor.c \
				  fd.c \
				  exec.c \

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
					test_key.c \

C_FILES_builtins = \
				   ft_env.c \
				   ft_setenv.c \
				   ft_take.c \
				   ft_unsetenv.c \
				   ft_addpath.c \
				   ft_cd.c \
				   ft_cd2.c \
				   ft_echo.c \
				   ft_exit.c \
				   builtin_misc.c \

C_FILES_utils = \
				double_linked_list.c \
				erase_char.c \
				dquotes_remove.c \
				dynamic_arrays.c \
				stack.c \
				queue.c \
				free_tree.c \
				ast_draw.c \

C_FILES_expansions = \
					 expansions.c \
					 quote_removal.c \
					 expression.c \

C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
