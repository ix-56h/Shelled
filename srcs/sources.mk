# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2020/05/11 13:00:32 by mguerrea         ###   ########.fr        #
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
				 parse_brace_group.c \
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
					lex_sequence.c \
					gnt_standalone.c \

C_FILES_visitor = \
				  visitor.c \
				  visitor_redir.c \
				  visitor_redir2.c \
				  visitor_assign.c \
				  visitor_special.c \
				  fd.c \
				  fd2.c \
				  exec.c \
				  exec_misc.c \
				  test_and_find.c \
				  visitor_cmd.c \
				  visitor_greatand.c \
				  visitor_leftredi.c \
				  visitor_rightredi.c \
				  visitor_lessand.c \
				  visitor_dless.c \
				  visitor_dgreat.c \
				  job.c \

C_FILES_shell = \
				main.c \
				env.c \
				env2.c \
				init.c \
				signal.c \
				set.c \
				shell_var.c \

C_FILES_line_edit = \
					alloc.c \
					clear.c \
					controleur.c \
					controleur2.c \
					garbage.c \
					get_things.c \
					historique.c \
					historique_controler.c \
					historique_act.c \
					ligne.c \
					line_edit.c \
					line_key1.c \
					line_key2.c \
					line_misc.c \
					move.c \
					term_misc.c \
					test_key.c \
					ctrl_c.c \
					termios.c \

C_FILES_builtins = \
				   ft_setenv.c \
				   ft_take.c \
				   ft_unsetenv.c \
				   ft_addpath.c \
				   ft_cd.c \
				   ft_cd2.c \
				   ft_echo.c \
				   ft_exit.c \
				   builtin_misc.c \
				   ft_debug_job.c \
				   ft_return.c \
				   ft_set.c \
				   ft_unset.c \
				   ft_export.c \

C_FILES_utils = \
				index_end_squote.c \
				double_linked_list.c \
				double_linked_list2.c \
				double_linked_list3.c \
				erase_char.c \
				dquotes_remove.c \
				dynamic_arrays.c \
				stack.c \
				queue.c \
				free_tree.c \
				fifo_creator.c \
				lifo_creator.c \
				free_sh.c \
				ast_draw.c \
				is_arithmetic.c \

C_FILES_expansions = \
					 expansions.c \
					 quote_removal.c \
					 expression.c \
					 substitution.c \
					 parameter_expansions.c \
					 parameter_expansions2.c \
					 expansions_utils.c \
					 dispatch_expansions.c \
					 manage_brace.c \

C_FILES_jobs = \
				bg.c \
				jobs.c \
				fg.c \
				update_jobs.c \
				manage_list.c \

C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
