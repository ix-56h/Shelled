/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "ft_printf.h"
#include "tokenizer.h"

char	**add_pot(char **alias, char *pot)
{
	size_t		i;
	size_t		j;
	char		**new_env;
	char		*new_var;

	j = 0;
	i = 0;
	while (alias && alias[i])
		++i;
	i += 2;
	new_env = ft_calloc(sizeof(char *) * i);
	while (j < i - 2)
	{
		new_env[j] = alias[j];
		j++;
	}
	alias = ft_free(alias);
	new_var = ft_strdup(pot);
	new_env[j] = new_var;
	return (new_env);
}

int is_alias(char *t_alias, char **cpy_alias)
{
  int cpt;

  cpt = -1;
  ft_printf("is | data : %s\n", t_alias);
  while (cpy_alias[++cpt])
  {
    ft_printf("is | alias : %s\n", cpy_alias[cpt]);
    if (ft_strcmp(get_name(cpy_alias[cpt]), t_alias) == 0)
    {
      write(1, "is_alias\n", 9);
      return (cpt);
    }
  }
  write(1, "no_alias\n", 9);
  return (-1);
}

char *launch_recursive(char *alias_v, char **alias_cpy, t_lifo *stack)
{
  t_tokens token;
  char **save_alias;
  char *to_add;
  char *new_input;
  char **pot_alias;
//  char *complete_v;
//  char *stock_op;
//  char *alias_c;
  int cpt;
  int i;

  i = 0;
  cpt = 0;
  save_alias = cpy_env(alias_cpy);
  ft_printf("alias_v : %s\n", alias_v);
  while ((token = get_next_token(alias_v, stack)).data)
  {
    ft_printf("data : %s\n", token.data);
    ft_printf("toketype : %d\n", token.tok);
    if (ft_strcmp(token.data, "EOF") == 0)
    {
      write(1, "\nx", 2);
      break ;
    }
    if (i == 0)
    {
      if (!(pot_alias = (char**)malloc(sizeof(char*) * 2)))
        return (NULL);
      pot_alias[0] = ft_strdup(token.data);
      pot_alias[1] = NULL;
      i++;
    }
    else
      pot_alias = add_pot(pot_alias, token.data);
  }
  i = 0;
  cpt = 0;
  while (pot_alias[cpt])
  {
    if (is_alias(pot_alias[cpt], alias_cpy) >= 0)
    {
      write(1, "alias\n", 6);
      to_add = recursive_alias(pot_alias[cpt], alias_cpy, stack);
      ft_printf("recurse : %s\n", to_add);
      if (to_add)
      {
        if (i == 0)
          new_input = ft_strdup(to_add);
        else
        {
          new_input = ft_strjoin(new_input, " ");
          new_input = ft_strjoin(new_input, to_add);
        }
        i++;
      }
    }
    else
    {
      write(1, "not alias\n", 10);
      if (i == 0)
        new_input = ft_strdup(pot_alias[cpt]);
      else
      {
        new_input = ft_strjoin(new_input, " ");
        new_input = ft_strjoin(new_input, pot_alias[cpt]);
      }
      i++;
    }
    ft_printf("input : %s\n", new_input);
    cpt++;
    alias_cpy = cpy_env(save_alias); // realloc alias_cpy
  }
  write(1, "a\n", 1);
  return (new_input);

/*      while (alias_v[cpt])
      {
    if ((alias_c = get_semi_alias(alias_v, &cpt))) // recupere les commandes entre les op des alias
    {
//      ft_printf("launch | semi alias : %s  -> cpt : %d, c of cpt : %c\n", alias_c, cpt, alias_v[cpt]);
      stock_op = get_op(alias_v, &cpt);  // recupere l'op apres alias_c
//      ft_printf("launch | op : %s -> cpt : %d, c of cpt : %c\n", stock_op, cpt, alias_v[cpt]);
//      ft_printf("launch | given to recursive : %s\n", alias_c);
      alias_c = recursive_alias(alias_c, alias_cpy); // transforme recursivement les semi alias
//      ft_printf("launch | new_alias recursively changed : %s\n", alias_c);
//      ft_printf("launch | print_r value : complete : %s, new_alias : %s, stock_op : %s, i: %d\n", complete_v, alias_c, stock_op, i);
      complete_v = print_r(complete_v, alias_c, stock_op, &i); // stock les alias transformer
//      ft_printf("launch | complete_v : %s -> added to big alias\n", complete_v);
      alias_cpy = cpy_env(save_alias); // realloc alias_cpy
//      getchar();
}*/
}

char  *test_alias(char *alias_n, t_lifo *stack)
{
	char	*name_g;
  char  *complete_v;
	int		cpt;
  char  **alias_cpy;

	cpt = -1;
  alias_cpy = cpy_env(g_alias);
	while (g_alias[++cpt])
	{
		name_g = get_name(g_alias[cpt]);
		if (ft_strcmp(name_g, alias_n) == 0)
		{
      alias_cpy = del_var(alias_cpy, name_g);
//      ft_printf("before launch | alias_v : %s\n", get_value(g_alias[cpt]));
      complete_v = launch_recursive(get_value(g_alias[cpt]), alias_cpy, stack);
//      ft_printf("after launch | complete value : %s\n", complete_v);
//      ft_printf("complete value : %s\n", complete_v);
//      getchar();
			free(name_g);
//      free(alias_n);
			return (complete_v);
		}
		free(name_g);
	}
//	free(alias_n);
	return (NULL);
}

char *add_alias(char *input, t_lifo *stack)
{
  t_tokens    token;
  char        *new_input;
  char **pot_alias;
  char *to_add;
  int cpt;
  static int  i;
//  int debug;

	if (!g_alias)
		return (input);
  while ((token = get_next_token(input, stack)).data)
  {
    ft_printf("token data : %s\n", token.data);
    if (token.data)
    if (ft_strcmp(token.data, "EOF") == 0)
      break ;
    if (i == 0)
    {
      if (!(pot_alias = (char**)malloc(sizeof(char*) * 2)))
        return (NULL);
      pot_alias[0] = ft_strdup(token.data);
      pot_alias[1] = NULL;
      i++;
    }
    else
      pot_alias = add_pot(pot_alias, token.data);

    /*
    if (token.data)
    {
      to_add = test_alias(token.data);
      if (to_add)
      {
        if (i == 0)
          new_input = ft_strdup(to_add);
        else
        {
          new_input = ft_strjoin(new_input, " ");
          new_input = ft_strjoin(new_input, to_add);
        }
        i++;
      }
      else
      {
        if (i == 0)
          new_input = ft_strdup(token.data);
        else
        {
          new_input = ft_strjoin(new_input, " ");
          new_input = ft_strjoin(new_input, token.data);
        }
        i++;
      }
    }*/
  }
  i = 0;
  cpt = 0;
  while (pot_alias[cpt])
    ft_printf("pot alias : %s\n", pot_alias[cpt++]);
  cpt = 0;
  while (pot_alias[cpt])
  {
    ft_printf("token : %s\n", pot_alias[cpt]);
    to_add = test_alias(pot_alias[cpt], stack);
    if (to_add)
    {
      if (i == 0)
        new_input = ft_strdup(to_add);
      else
      {
        new_input = ft_strjoin(new_input, " ");
        new_input = ft_strjoin(new_input, to_add);
      }
      i++;
    }
    else
    {
      if (i == 0)
        new_input = ft_strdup(pot_alias[cpt]);
      else
      {
        new_input = ft_strjoin(new_input, " ");
        new_input = ft_strjoin(new_input, pot_alias[cpt]);
      }
      i++;
    }
    cpt++;
  }
  i = 0;
/*	rm_first_space(input);
	cpt = -1;
	while (input[++cpt])
	{
//    ft_printf("cpt add : %d\n", cpt);
		alias_n = get_next_word(input, cpt);  //  return the word where cpt start
		if (alias_n)
		{
			len_n = ft_strlen(alias_n);   // save len alias name for add cpt if no new_input
			if ((alias_n = test_alias(alias_n)))  // test if alias_n is an alias if its true return the value esle return NULL
				input = new_input(alias_n, input, &cpt, len_n);  // modify input whith the alias value add the len to cpt
			else
				cpt += len_n;  // add len of word command if not aliases
			free(alias_n);
		}
		ignore_args_n_op(input, &cpt);  // cpt is place to the end of command name
    if (cpt == (int)ft_strlen(input))
      return (input);
	}*/
	return (new_input);
}

int  get_len(char *input, int cpt)
{
	char	w_q;
	int		i;

	i = cpt;
	w_q = 0;
  while (input[i] && input[i] != ' ')
  {
    if (input[i] == '\'' || input[i] == '\"')
    {
      w_q = input[i];
      i++;
      while (input[i] && input[i] != w_q)
        i++;
      return (i - cpt);
    }
    i++;
  }
	return (i - cpt);
}

char *get_next_word(char *input, int cpt)
{
	char	*alias_n;
	int		i;
	int		id;

  if (cpt >= (int)ft_strlen(input))
    return (NULL);
  while (input[cpt] == ' ')
    cpt++;
	i = get_len(input, cpt);
	if (!(alias_n = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	id = 0;
	while (id < i && input[cpt])
	{
		alias_n[id] = input[cpt];
		cpt++;
		id++;
	}
	alias_n[id] = '\0';
	return (alias_n);
}

int ignore_args_n_op(char *input, int *cpt)
{
	t_toktype	op;
	char		  *name;
	size_t		l;

	while (input[*cpt])
	{
		while (input[*cpt] == ' ' && input[*cpt])
			*cpt += 1;
		if (!(name = get_next_word(input, *cpt)))
      return (0);
		l = ft_strlen(name);
		if ((op = check_redirections(name, l, cpt)) != 0
				|| (op = check_operator(name, l, cpt)) != 0
				|| (op = check_pipe(name, l, cpt)) != 0)
		{
			*cpt += ft_strlen(name);
			while (input[*cpt] == ' ' && input[*cpt])
				*cpt += 1;
			*cpt -= 1;
			free(name);
			return (1);
		}
		*cpt += ft_strlen(name);
		free(name);
	}
  return (0);
}

char *get_with_cpt(char *alias_v, int from, int to)
{
  char *alias_command;
  int  cpt;

  cpt = 0;
  if (!(alias_command = (char*)malloc(sizeof(char) * (to - from))))
    return (NULL);
  while (from < to)
  {
    alias_command[cpt] = alias_v[from];
    cpt++;
    from++;
  }
  alias_command[cpt] = '\0';
  return (alias_command);
}

char *get_word(char *alias_v, int *cpt)
{
  char *word;
  int  i;
  int  j;

  i = *cpt;
  j = 0;
  while (alias_v[*cpt] && alias_v[*cpt] != ' ')
    *cpt += 1;
  if (!(word = (char*)malloc(sizeof(char) * (*cpt - i))))
    return (NULL);
  while (i < *cpt)
  {
    word[j] = alias_v[i];
    j++;
    i++;
  }
  word[j] = '\0';
  return (word);
}

char *get_semi_alias(char *alias_v, int *cpt)
{
  t_toktype	op;
	char		  *alias_command;
  char      *to_add;
	size_t		l;
  int       stock_cpt;

  while (alias_v[*cpt] && alias_v[*cpt] == ' ')
    *cpt += 1;
//  ft_printf("semi | cpt : %d, pos sur alias_v : %c  -> first step in function\n", *cpt, alias_v[*cpt - 1]);
//  getchar();
  stock_cpt = *cpt;
  while (alias_v[*cpt])
  {
    to_add = get_word(alias_v, cpt);
    while (alias_v[*cpt] && alias_v[*cpt] == ' ')
      *cpt += 1;
    l = ft_strlen(to_add);
    if ((op = check_redirections(to_add, l, cpt)) != 0 // test d'arret si operateurs
				|| (op = check_operator(to_add, l, cpt)) != 0
				|| (op = check_pipe(to_add, l, cpt)) != 0)
		{
//      ft_printf("semi | op check cpt : %d, char on alias_v : %c -> alias_v : %s\n", *cpt, alias_v[*cpt], alias_v);
      *cpt -= l;
      while (*cpt > 0 && alias_v[*cpt] == ' ')
        *cpt -= 1;
//      ft_printf("semi | op check replace cp : %d, char on alias_v : %c -> alias_v : %s\n", *cpt, alias_v[*cpt], alias_v);
      alias_command = get_with_cpt(alias_v, stock_cpt, *cpt);
//      ft_printf("semi | end op return : %s\n", alias_command);
			free(to_add);
			return (alias_command);
	  }
    free(to_add);
  }
  alias_command = get_with_cpt(alias_v, stock_cpt, *cpt);
//  ft_printf("semi | end no op : %s\n", alias_command);
  return (alias_command);
}

char *print_r(char *complete_v, char *alias_c, char *stock_op, int *i)
{
  if (*i == 0)
  {
//    ft_printf("print_r | first print : alias : %s, op : %s -> alias_c added\n", alias_c, stock_op);
//    getchar();
    if (stock_op)
    {
      complete_v = ft_strjoinf(alias_c, " ", 1);
      complete_v = ft_strjoinf(complete_v, stock_op, 3);
    }
    else
      complete_v = ft_strdup(alias_c);
    *i += 1;
  }  // print premiere recursive
  else
  {
//    ft_printf("print_r | next print : old recursive alias : %s, new recursive to add: %s op if necessary : %s\n", complete_v, alias_c, stock_op);
//    getchar();
    complete_v = ft_strjoinf(complete_v, " ", 1);
    complete_v = ft_strjoinf(complete_v, alias_c, 3);
    if (stock_op)
    {
      complete_v = ft_strjoinf(complete_v, " ", 1);
      complete_v = ft_strjoinf(complete_v, stock_op, 3);
    }
  } // print next op recursive
//  ft_printf("print_r | new_complete value : %s\n", complete_v);
  return (complete_v);
}

char *get_op(char *alias_v, int *cpt)
{
  t_toktype op;
  char    *stock_op;
  size_t  l;

//  ft_printf("get op | alias_v : %s, before get op cpt : %d\n", alias_v, *cpt);
  stock_op = get_next_word(alias_v, *cpt);
//  ft_printf("get op | stock_op getted : %s\n", stock_op);
//  getchar();
  if (stock_op)
  {
    l = ft_strlen(stock_op);
    if ((op = check_redirections(stock_op, l, cpt)) != 0 // test d'arret si operateurs
        || (op = check_operator(stock_op, l, cpt)) != 0
        || (op = check_pipe(stock_op, l, cpt)) != 0)
    {
      *cpt += l + 1;
      return (stock_op);
    }
  }
  return (NULL);
}
