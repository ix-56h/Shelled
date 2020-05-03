#include "libft.h"
#include "sh.h"
#include "builtins.h"

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
			if (ft_isalnum(str[i])
			|| ((str[i] == '=' || str[i] == '_') && i > 0))
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

static void		export_and_set(char *str, int opt)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if ((value = ft_strchr(str, '=')))
	{
		if (ft_strlen(str) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			name = ft_strdup(str);
			add_set(name, value);
			g_env = add_env(g_env, name, value);
			if (opt == 1)
			{
				ft_putstr("export ");
				ft_putendl(name);
			}
		}
		free(name);
	}
}

static void		export_to_env(char *str, int opt)
{
	char	*name;
	char	*value;

	value = NULL;
	name = ft_strdup(str);
	if ((value = get_env(g_set, name)))
	{
		g_env = add_env(g_env, name, value);
		if (opt == 1)
		{
			ft_putstr("export ");
			ft_putstr(name);
			ft_putchar('=');
			ft_putendl(value);
		}
	}
	else if (opt == 1)
	{
		ft_putstr_fd("export: no such variable: ", 2);
		ft_putendl_fd(name, 2);
	}
	free(name);
}

int				ft_export(char **argv, char ***env)
{
	int i;
	int opt;

	i = 0;
	opt = 0;
	if (!env)
		return (0);
	if (!argv[1])
		print_export(*env);
	else
	{
		i = ft_strcmp(argv[1], "-p") == 0 ? 2 : 1;
		opt = i == 2 ? 1 : 0;
		while (argv[i])
		{
			if (ft_isalnum_str(argv[i]) && ft_isalpha(argv[i][0]))
				export_to_env(argv[i], opt);
			else if (is_export(argv[i]))
				export_and_set(argv[i], opt);
			else
				export_error(argv[i]);
			i++;
		}
	}
	return (0);
}
