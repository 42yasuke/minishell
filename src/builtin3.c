/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 05:09:01 by jose              #+#    #+#             */
/*   Updated: 2023/05/24 16:57:48 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_another_one_env(char **var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (i < MAXARG)
		envp[i] = ft_strdup(var[1]);
	else
		ft_error(EXPORT_FAILED, "export : max variable reached");
}

static void	ft_export_no_pipe_args(char **var, char **envp)
{
	char	*tmp;
	size_t	diff;
	int		i;

	i = -1;
	while (envp[++i])
	{
		diff = ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '='));
		if (!ft_strncmp(var[1], envp[i], diff))
		{
			tmp = envp[i];
			envp[i] = ft_strdup(var[1]);
			free(tmp);
			break ;
		}
	}
	if (!envp[i])
		ft_another_one_env(var, envp);
}

static void	ft_export_no_args(char **envp)
{
	t_lenv	*lst_env;
	t_lenv	*tmp;
	int		i;

	i = -1;
	lst_env = malloc(sizeof(*lst_env));
	if (!lst_env)
		ft_error(MALLOC_FAILED, "lst_env : malloc failded");
	ft_init_lst(lst_env, envp);
	while (envp[++i])
	{
		tmp = ft_get_node(lst_env, i);
		ft_printf("export %s\n", tmp->env_name);
	}
	ft_free_lst(lst_env);
}

void	ft_export_no_pipe(char *line, char **envp)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (tmp[1])
	{
		if (tmp[2])
			ft_error(EXPORT_FAILED, "export : invalid argument");
		if (tmp[1][0] == '-')
			ft_error(EXPORT_FAILED, "export : invalid option");
		else
		{
			if (!ft_strchr(tmp[1], '='))
				ft_error(EXPORT_FAILED, "export : variable : need an affectation");
			ft_export_no_pipe_args(tmp, envp);
		}
	}
	else
		ft_export_no_args(envp);
	ft_free_all(tmp);
}

int	ft_builtin_no_pipe(char *line, char **envp)
{
	int	is_builtin;

	is_builtin = false;
	if (!ft_strchr(line, '|'))
	{
		if (!ft_strncmp(line, "cd", 2))
			ft_cd_no_pipe(line);
		else if (!ft_strncmp(line, "export", 6))
			ft_export_no_pipe(line, envp);
		else if (!ft_strncmp(line, "unset", 5))
			ft_unset_no_pipe(line, envp);
		is_builtin = (!ft_strncmp(line, "cd", 2) || \
		!ft_strncmp(line, "export", 6) || !ft_strncmp(line, "unset", 5));
	}
	return (is_builtin);
}
