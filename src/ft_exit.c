/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:04:00 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 11:06:04 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_numeric_arg(char **tmp)
{
	int	i;

	i = -1;
	if (tmp[1][0] == '-' && !ft_isdigit(tmp[1][1]))
		(ft_free_all(tmp), ft_error(EXIT_FAILED, "exit",
				"numeric argument required"));
	if (tmp[1][0] == '+' && !ft_isdigit(tmp[1][1]))
		(ft_free_all(tmp), ft_error(EXIT_FAILED, "exit",
				"numeric argument required"));
	while (tmp[1][++i])
	{
		if (!ft_isdigit(tmp[1][i]))
		{
			if (i || (tmp[1][i] != '+' && tmp[1][i] != '-'))
				(ft_free_all(tmp), ft_error(EXIT_FAILED, "exit",
						"numeric argument required"));
		}
	}
	if (tmp[2])
		return (ft_error2("exit", "too many arguments", 1), false);
	return (true);
}

static int	ft_verif_numeric_arg2(char **tmp)
{
	t_ll	d;

	if (!ft_compare_to_llmax_and_llmin(tmp[1]))
		(ft_free_all(tmp), ft_error(EXIT_FAILED, "exit",
				"numeric argument required"));
	d = ft_atoll(tmp[1]);
	d = ft_rest_of_div(d, 256);
	return ((int)d);
}

void	ft_exit_no_pipe(char *line)
{
	char	**tmp;
	int		i;
	int		quit;

	quit = true;
	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		quit = ft_verif_numeric_arg(tmp);
		if (quit)
		{
			i = ft_verif_numeric_arg2(tmp);
			(ft_free_all(tmp), ft_free_ginf(true));
			(ft_printf("exit\n"), exit(i));
		}
	}
	ft_free_all(tmp);
	if (quit)
		(ft_free_ginf(true), ft_printf("exit\n"), exit(EXIT_SUCCESS));
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
