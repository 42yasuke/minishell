/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:24:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/22 23:41:35 by jose             ###   ########.fr       */
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
		ft_error(MALLOC_FAILED, "lst_env : malloc failded");
	ft_init_lst(lst_env, ecmd->env);
	while (ecmd->env[++i])
	{
		tmp = ft_get_node(lst_env, i);
		ft_printf("export %s\n", tmp->env_name);
	}
	(ft_free_lst(lst_env), exit(EXIT_SUCCESS));
}

void	ft_export(t_ecmd *ecmd)
{
	if (ecmd->argv[1])
	{
		if (ecmd->argv[2])
			ft_error(EXPORT_FAILED, "export : invalid argument");
		if (ecmd->argv[1][0] == '-')
			ft_error(EXPORT_FAILED, "export : invalid option");
		else
			ft_export_with_args(ecmd);
	}
	ft_export_no_args(ecmd);
}

void	ft_unset(t_ecmd *ecmd)
{
	if (ecmd->argv[1])
	{
		if (ecmd->argv[2])
			ft_error(EXPORT_FAILED, "unset : invalid argument");
		if (ecmd->argv[1][0] == '-')
			ft_error(EXPORT_FAILED, "unset : invalid option");
		else
			ft_unset_with_args(ecmd);
	}
	exit(EXIT_SUCCESS);
}

void	ft_env(t_ecmd *ecmd)
{
	int	i;

	i = -1;
	while (ecmd->env[++i])
		ft_printf("%s\n", ecmd->env[i]);
	exit(EXIT_SUCCESS);
}

void	ft_exit(t_ecmd *ecmd)
{
	int	i;

	i = -1;
	if (ecmd->argv[1])
	{
		if (ecmd->argv[2])
			ft_error(EXIT_FAILED, "exit : invalid argument");
		if (ecmd->argv[1][0] == '-')
			ft_error(EXIT_FAILED, "exit : invalid option");
		else
		{
			while (ecmd->argv[1][++i])
			{
				if (!ft_isdigit(ecmd->argv[1][++i]))
					ft_error(EXIT_FAILED, "exit : invalid argument");
			}
			if (ft_strlen(ecmd->argv[1]) > 3 || ft_atoi(ecmd->argv[1]) > 255)
				ft_error(EXIT_FAILED, "exit : invalid argument");
			exit(ft_atoi(ecmd->argv));
		}
	}
	exit(EXIT_SUCCESS);
}
