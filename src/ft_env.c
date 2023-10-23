/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:14:59 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:53:37 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_env(t_ecmd *ecmd, t_ginf *ginf)
{
	int	i;

	i = -1;
	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-' && ft_strlen(ecmd->argv[1]) > 1)
			ft_error(ENV_FAILED, "env", "invalid option", ginf);
		else
			ft_error(EXECVE_FAILED, "env", "invalid args", ginf);
	}
	while (ginf->env[++i])
		ft_printf("%s\n", ginf->env[i]);
	(ft_free_ginf(ginf, true), exit(EXIT_SUCCESS));
}
