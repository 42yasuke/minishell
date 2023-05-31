/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:57:46 by jose              #+#    #+#             */
/*   Updated: 2023/05/31 23:07:39 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_loop(t_ecmd *ecmd, int is_n)
{
	int	i;

	i = 1;
	while (ecmd->argv[++i])
	{
		if (i == 2 && !is_n)
			ft_printf(" ");
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
		if (ecmd->argv[1][0] == '-')
		{
			if (!ft_strncmp(ecmd->argv[1], "-n", ft_strlen(ecmd->argv[1])))
				is_n = true;
		}
		if (!is_n)
			ft_printf("%s", ecmd->argv[1]);
		ft_loop(ecmd, is_n);
	}
	if (!is_n)
		ft_printf("\n");
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}
