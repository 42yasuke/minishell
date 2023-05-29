/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 05:09:01 by jose              #+#    #+#             */
/*   Updated: 2023/05/29 21:05:09 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_another_one_env(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (i < MAXARG)
		envp[i] = ft_strdup(str);
	else
		ft_error(EXPORT_FAILED, "export : max variable reached");
}

static void	ft_export_no_pipe_args(char *str, char **envp)
{
	char	*tmp;
	size_t	diff;
	int		i;

	i = -1;
	while (envp[++i])
	{
		diff = ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '='));
		if (!ft_strncmp(str, envp[i], diff))
		{
			tmp = envp[i];
			envp[i] = ft_strdup(str);
			free(tmp);
			break ;
		}
	}
	if (!envp[i])
		ft_another_one_env(str, envp);
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
	int		i;

	tmp = ft_split(line, ' ');
	if (tmp[1])
	{
		i = 0;
		while (tmp[++i])
		{
			if (ft_analyse(tmp[i]))
				ft_export_no_pipe_args(tmp[i], envp);
		}
	}
	else
		ft_export_no_args(envp);
	ft_free_all(tmp);
}

void	ft_builtin_no_pipe(char *line, char **envp)
{
	if (!ft_strchr(line, '|'))
	{
		if (!ft_strncmp(line, "cd", 2))
			ft_cd_no_pipe(line);
		else if (!ft_strncmp(line, "export", 6))
			ft_export_no_pipe(line, envp);
		else if (!ft_strncmp(line, "unset", 5))
			ft_unset_no_pipe(line, envp);
		else if (!ft_strncmp(line, "exit", 4))
			ft_exit_no_pipe(line);
	}
}
