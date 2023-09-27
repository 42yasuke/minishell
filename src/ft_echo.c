/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:34:14 by jose              #+#    #+#             */
/*   Updated: 2023/09/26 23:05:46 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_analyse_first_arg(char *str)
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
	return (true);
}

static void	ft_loop(t_ecmd *ecmd, int is_n)
{
	int	i;

	i = is_n;
	while (ecmd->argv[++i])
	{
		/*if (i == 2 && !is_n)
			ft_printf(" ");*/
		ft_printf("%s", ecmd->argv[i]);
		if (ecmd->argv[i + 1])
			ft_printf(" ");
	}
}

void	ft_echo(t_ecmd *ecmd)
{
	int	is_n;

	is_n = false;
	if (ecmd->argv[1])
	{
		is_n = ft_analyse_first_arg(ecmd->argv[1]);
		ft_loop(ecmd, is_n);
	}
	if (!is_n)
		ft_printf("\n");
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}
