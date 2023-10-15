/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:34:14 by jose              #+#    #+#             */
/*   Updated: 2023/10/15 13:52:20 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_analyse_option_n(char *str)
{
	int	i;

	i = 0;
	if (*str != '-')
		return (false);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (!(i == 1 && !str[i]));
}

static int	ft_find_start(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && ft_analyse_option_n(argv[i]))
		i++;
	return (i);
}

static void	ft_loop(t_ecmd *ecmd, int start)
{
	int	i;

	i = start - 1;
	while (ecmd->argv[++i])
	{
		ft_printf("%s", ecmd->argv[i]);
		if (ecmd->argv[i + 1])
			ft_printf(" ");
	}
}

void	ft_echo(t_ecmd *ecmd, t_ginf *ginf)
{
	int	is_n;
	int	start;

	is_n = false;
	start = 0;
	if (ecmd->argv[1])
	{
		is_n = ft_analyse_option_n(ecmd->argv[1]);
		start = ft_find_start(ecmd->argv);
		ft_loop(ecmd, start);
	}
	if (!is_n)
		ft_printf("\n");
	(ft_free_ginf(ginf, true), exit(EXIT_SUCCESS));
}
