/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:02:12 by jose              #+#    #+#             */
/*   Updated: 2023/09/19 23:40:37 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_export_no_args(void)
{
	int		i;

	i = -1;
	ft_range_lst(g_inf->lst_env);
	while (g_inf->lst_env[++i])
		ft_printf("export %s\n", g_inf->lst_env[i]);
}

void	ft_export_no_pipe(char *line)
{
	char	**tmp;
	int		i;

	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		i = 0;
		while (tmp[++i])
		{
			if (ft_analyse(tmp[i]))
				ft_update_env_n_lst_env(tmp[i]);
		}
	}
	else
		ft_export_no_args();
	ft_free_all(tmp);
}

void	ft_export(t_ecmd *ecmd)
{
	int	i;

	i = 0;
	g_inf->exit_code = EXIT_SUCCESS;
	if (ecmd->argv[1])
	{
		while (ecmd->argv[++i])
		{
			if (ft_analyse(ecmd->argv[i]))
				ft_update_env_n_lst_env(ecmd->argv[i]);
		}
	}
	else
		ft_export_no_args();
	i = g_inf->exit_code;
	(ft_free_ginf(true), exit(i));
}
