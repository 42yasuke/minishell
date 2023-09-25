/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:14:59 by jose              #+#    #+#             */
/*   Updated: 2023/09/09 10:15:16 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_env(t_ecmd *ecmd)
{
	int	i;

	i = -1;
	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-')
			ft_error(ENV_FAILED, "env", "invalid option");
		else
			ft_error(EXECVE_FAILED, "env", "invalid args");
	}
	while (g_inf->env[++i])
		ft_printf("%s\n", g_inf->env[i]);
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}
