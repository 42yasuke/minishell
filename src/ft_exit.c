/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:04:00 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:53:59 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_numeric_arg(char **tmp, t_ginf *ginf, int free_tmp)
{
	int	i;

	i = -1;
	if (tmp[1][0] == '-' && !ft_isdigit(tmp[1][1]))
		(ft_free_all(tmp), ft_error(ERROR2, "exit",
				"numeric argument required", ginf));
	if (tmp[1][0] == '+' && !ft_isdigit(tmp[1][1]))
		(ft_free_all(tmp), ft_error(ERROR2, "exit",
				"numeric argument required", ginf));
	while (tmp[1][++i])
	{
		if (!ft_isdigit(tmp[1][i]))
		{
			if (i || (tmp[1][i] != '+' && tmp[1][i] != '-'))
			{
				if (free_tmp)
					ft_free_all(tmp);
				ft_error(ERROR2, "exit", "numeric argument required", ginf);
			}
		}
	}
	if (tmp[2])
		return (ft_error2(ERROR, "exit", "too many arguments"), false);
	return (true);
}

static int	ft_verif_numeric_arg2(char **tmp, t_ginf *ginf)
{
	t_ll	d;

	if (!ft_compare_to_llmax_and_llmin(tmp[1]))
		(ft_free_all(tmp), ft_error(ERROR2, "exit",
				"numeric argument required", ginf));
	d = ft_atoll(tmp[1]);
	d = ft_rest_of_div(d, 256);
	return ((int)d);
}

void	ft_exit_no_pipe(char *line, t_ginf *ginf)
{
	char	**tmp;
	int		i;
	int		quit;

	quit = true;
	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		quit = ft_verif_numeric_arg(tmp, ginf, true);
		if (quit)
		{
			i = ft_verif_numeric_arg2(tmp, ginf);
			(ft_free_all(tmp), ft_free_ginf(ginf, true));
			(ft_printf("exit\n"), exit(i));
		}
	}
	ft_free_all(tmp);
	if (quit)
		(ft_free_ginf(ginf, true), ft_printf("exit\n"), exit(0));
}

void	ft_exit(t_ecmd *ecmd, t_ginf *ginf)
{
	int		i;
	int		quit;

	if (ecmd->argv[1])
	{
		quit = ft_verif_numeric_arg(ecmd->argv, ginf, false);
		if (quit)
		{
			i = ft_verif_numeric_arg2(ecmd->argv, ginf);
			ft_free_ginf(ginf, true);
			(ft_printf("exit\n"), exit(i));
		}
		i = g_exit_code;
		(ft_free_ginf(ginf, true), exit(i));
	}
	(ft_free_ginf(ginf, true), ft_printf("exit\n"), exit(EXIT_SUCCESS));
}
