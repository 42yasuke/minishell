/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:02:12 by jose              #+#    #+#             */
/*   Updated: 2023/10/24 14:16:53 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_export_no_args(t_ginf *ginf)
{
	int		i;

	i = -1;
	ft_range_lst(ginf->lst_env);
	while (ginf->lst_env[++i])
		ft_printf("export %s\n", ginf->lst_env[i]);
}

void	ft_export_no_pipe(char *line, t_ginf *ginf)
{
	char	**tmp;
	int		i;

	g_exit_code = EXIT_SUCCESS;
	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		i = 0;
		while (tmp[++i])
		{
			if (ft_analyse_export(tmp[i]))
				ft_update_env_n_lst_env(tmp[i], ginf);
		}
	}
	else
		ft_export_no_args(ginf);
	ft_free_all(tmp);
}

void	ft_export(t_ecmd *ecmd, t_ginf *ginf)
{
	int	i;

	i = 0;
	g_exit_code = EXIT_SUCCESS;
	if (ecmd->argv[1])
	{
		while (ecmd->argv[++i])
		{
			if (ft_analyse_export(ecmd->argv[i]))
				ft_update_env_n_lst_env(ecmd->argv[i], ginf);
		}
	}
	else
		ft_export_no_args(ginf);
	i = g_exit_code;
	(ft_free_ginf(ginf, true), exit(i));
}
