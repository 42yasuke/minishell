/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:24:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/31 23:57:37 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_export_no_args(t_ecmd *ecmd)
{
	t_lenv	*lst_env;
	t_lenv	*tmp;
	int		i;

	i = -1;
	lst_env = malloc(sizeof(*lst_env));
	if (!lst_env)
		ft_error(MALLOC_FAILED, "lst_env", "malloc failded");
	ft_init_lst(lst_env, ecmd->env);
	while (ecmd->env[++i])
	{
		tmp = ft_get_node(lst_env, i);
		ft_printf("export %s\n", tmp->env_name);
	}
	(ft_free_ginf(true), ft_free_lst(lst_env), exit(EXIT_SUCCESS));
}

void	ft_export(t_ecmd *ecmd)
{
	int	i;

	i = 0;
	if (ecmd->argv[1])
	{
		while (ecmd->argv[++i])
		{
			if (ft_analyse(ecmd->argv[i]))
				ft_export_with_args(ecmd->argv[i], ecmd->env);
			else
			{
				i = g_inf->exit_code;
				(ft_free_ginf(true), exit(i));
			}
		}
	}
	ft_export_no_args(ecmd);
}

void	ft_unset(t_ecmd *ecmd)
{
	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-')
			ft_error(UNSET_FAILED, "unset", "invalid option");
		else
			ft_unset_with_args(ecmd);
	}
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}

void	ft_env(t_ecmd *ecmd)
{
	int	i;

	i = -1;
	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-')
			ft_error(ENV_FAILED, "env", "invalid option");
		else
			ft_error(EXECVE_FAILED, "env", "No such file or directory");
	}
	while (ecmd->env[++i])
		ft_printf("%s\n", ecmd->env[i]);
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}

void	ft_exit(t_ecmd *ecmd)
{
	int		i;
	int		quit;

	if (ecmd->argv[1])
	{
		quit = ft_verif_numeric_arg(ecmd->argv);
		if (quit)
		{
			i = ft_verif_numeric_arg2(ecmd->argv);
			ft_free_ginf(true);
			(ft_printf("exit\n"), exit(i));
		}
		i = g_inf->exit_code;
		(ft_free_ginf(true), exit(i));
	}
	(ft_free_ginf(true), ft_printf("exit\n"), exit(EXIT_SUCCESS));
}
