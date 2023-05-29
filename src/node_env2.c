/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:20:31 by jose              #+#    #+#             */
/*   Updated: 2023/05/29 21:47:02 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_another_one_env(t_ecmd *ecmd)
{
	int		i;

	i = 0;
	while (ecmd->env[i])
		i++;
	if (i < MAXARG)
		ecmd->env[i] = ft_strdup(ecmd->argv[1]);
	else
		ft_error(EXPORT_FAILED, "export : max variable reached");
}

void	ft_export_with_args(t_ecmd *ecmd)
{
	char	*tmp;
	size_t	diff;
	int		i;

	i = -1;
	while (ecmd->env[++i])
	{
		diff = ft_strlen(ecmd->env[i]) - ft_strlen(ft_strchr(ecmd->env[i], '='));
		if (!ft_strncmp(ecmd->argv[1], ecmd->env[i], diff))
		{
			tmp = ecmd->env[i];
			ecmd->env[i] = ft_strdup(ecmd->argv[1]);
			free(tmp);
			break ;
		}
	}
	if (!ecmd->env[i])
		ft_another_one_env(ecmd);
	(ft_free_ginf(true), exit(EXIT_SUCCESS));
}

void	ft_unset_with_args(t_ecmd *ecmd)
{
	size_t	diff;
	int		i;
	int		take_next;

	take_next = false;
	i = -1;
	while (ecmd->env[++i])
	{
		diff = ft_strlen(ecmd->env[i]) - ft_strlen(ft_strchr(ecmd->env[i], '='));
		if (!ft_strncmp(ecmd->argv[1], ecmd->env[i], diff))	
		{
			free(ecmd->env[i]);
			take_next = true;
		}
		if (take_next)
			ecmd->env[i] = ecmd->env[i + 1];
	}
}
