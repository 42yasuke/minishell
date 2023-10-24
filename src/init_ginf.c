/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ginf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:59:02 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 19:43:01 by jralph           ###   ########.fr       */
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
		ft_error(ERROR, "env", "malloc failed", NULL);
	i = -1;
	while (++i < MAXARG + 1)
		env[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			(ft_free_all(env), ft_error(ERROR, "env", "malloc failed", NULL));
	}
	return (env);
}

static char	**ft_init_lst(char **envp)
{
	char	**export;
	int		i;

	export = malloc(sizeof(*export) * (MAXARG + 1));
	if (!export)
		ft_error(ERROR, "export", "malloc failded", NULL);
	i = -1;
	while (++i < MAXARG + 1)
		export[i] = NULL;
	i = -1;
	while (envp[++i])
		export[i] = ft_add_guigui_on_env_name(envp[i]);
	return (export);
}

void	ft_reset_ginf(t_ginf *ginf)
{
	ginf->line = NULL;
	ginf->top = NULL;
}

void	ft_init_ginf(t_ginf *ginf, char **envp)
{
	ginf->line = NULL;
	ginf->top = NULL;
	ginf->env = NULL;
	ginf->lst_env = NULL;
	if (!envp || (envp && !*envp))
		ft_error(ERROR, "env", "empty", ginf);
	ginf->env = ft_cpy_envp(envp);
	ginf->lst_env = ft_init_lst(envp);
	g_exit_code = 0;
	ft_reset_ginf(ginf);
}
