#include "libft.h"
#include "sh.h"
#include "builtins.h"

#include <stdio.h>

static void		print_export(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr("export ");
		ft_putendl(env[i]);
		i++;
	}
}

static void		export_error(char *str)
{
	ft_putstr_fd("42sh: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" : not a valid identifier", 2);
}

static int		is_export(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]))
	{
		while (str[i])
		{
			if (ft_isalnum(str[i]) || ((str[i] == '=' || str[i] == '_') && i > 0))
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

static void		export_and_set(char *str)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (value = ft_strchr(str, '='))
	{
		if (ft_strlen(str) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			name = str;
			add_set(name, value);
			g_env = add_env(g_env, name, value);
		}
	}
}

static void		export_to_env(char *str)
{
	char	*name;
	char	*value;

	value = NULL;
	name = ft_strdup(str);
	if (value = get_env(g_set, name))
		g_env = add_env(g_env, name, value);
	free(name);
}

int				ft_export(char **argv, char ***env)
{
	int i;

	i = 1;
	if (!env)
		return (0);
	if (!argv[1])
		print_export(*env);
	else
	{
		while (argv[i])
		{
			if (i == 1 && ft_strcmp(argv[i], "-p") == 0)
			{
				printf("\nOPT -p\n");
				i++;
			}
			if (ft_isalnum_str(argv[i]) && ft_isalpha(argv[i][0]))
				export_to_env(argv[i]);
			else if (is_export(argv[i]))
				export_and_set(argv[i]);
			else
				export_error(argv[i]);
			i++;
		}
	}
	return (0);
}
