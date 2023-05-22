/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:24:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/22 17:33:56 by jose             ###   ########.fr       */
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
	ft_init_lst(lst_env);
	while (environ[++i])
	{
		tmp = ft_get_node(lst_env, i);
		ft_printf("export %s\n", tmp->env_name);
	}
	(ft_free_lst(lst_env), exit(EXIT_SUCCESS));
}

void	ft_export(t_ecmd *ecmd)
{
	if (ecmd->argv[1])
		
	else
		ft_export_no_args(ecmd);
}

void	ft_unset(t_ecmd *ecmd)
{
	
}

void	ft_env(t_ecmd *ecmd)
{
	int	i;

	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
	exit(EXIT_SUCCESS);
}

void	ft_exit(t_ecmd *t_ecmd)
{
	
}
