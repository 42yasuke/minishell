/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ginf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:59:02 by jose              #+#    #+#             */
/*   Updated: 2023/09/26 20:38:16 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_range_lst(char **lst_env)
{
	int		i;
	int		j;
	char	*save;

	i = -1;
	while (lst_env[++i])
	{
		j = i;
		while (lst_env[++j])
		{
			if (ft_strncmp(lst_env[i], lst_env[j], ft_strlen(lst_env[i])) > 0)
			{
				save = lst_env[i];
				lst_env[i] = lst_env[j];
				lst_env[j] = save;
			}
		}
	}
}

static char	**ft_cpy_envp(char **envp)
{
	int		i;
	char	**env;

	env = malloc(sizeof(*env) * (MAXARG + 1));
	if (!env)
		ft_error(MALLOC_FAILED, "env", "malloc failed");
	i = -1;
	while (++i < MAXARG + 1)
		env[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			(ft_free_all(env), ft_error(MALLOC_FAILED, "env", "malloc failed"));
	}
	return (env);
}

static char	**ft_init_lst(char **envp)
{
	char	**export;
	int		i;

	export = malloc(sizeof(*export) * (MAXARG + 1));
	if (!export)
		ft_error(MALLOC_FAILED, "export", "malloc failded");
	i = -1;
	while (++i < MAXARG + 1)
		export[i] = NULL;
	i = -1;
	while (envp[++i])
		export[i] = ft_add_guigui_on_env_name(envp[i]);
	return (export);
}

void	ft_init_ginf(char **envp, int init_all)
{
	if (!envp || (envp && !*envp))
		ft_error(MALLOC_FAILED, "env", "empty");
	if (init_all)
	{
		g_inf = malloc(sizeof(*g_inf));
		if (!g_inf)
			ft_error(MALLOC_FAILED, "g_inf", "malloc failed");
		g_inf->env = ft_cpy_envp(envp);
		g_inf->lst_env = ft_init_lst(envp);
		g_inf->exit_code = 0;
	}
	g_inf->line = NULL;
	g_inf->top = NULL;
	g_inf->is_child_process = false;
	g_inf->here_doc_quit = false;
	g_inf->here_doc = false;
	g_inf->tmp_stdin = -1;
}
