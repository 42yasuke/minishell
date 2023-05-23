/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:20:31 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 00:47:24 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_another_one_env(t_ecmd *ecmd)
{
	char	**new_env;
	int		i;

	i = ft_nb_str(ecmd->env);
	new_env = malloc(sizeof(*new_env) * (i + 2));
	if (!new_env)
		ft_error(MALLOC_FAILED, "new_env : malloc failed");
	i = -1;
	while (ecmd->env[++i])
		new_env[i] = ecmd->env[i];
	new_env[i] = ft_strdup(ecmd->argv[1]);
	new_env[i + 1] = NULL;
	*ecmd->env = *new_env;
	free(new_env);
}

void	ft_export_with_args(t_ecmd *ecmd)
{
	char	*tmp;
	size_t	diff;
	int		i;

	i = -1:
	while (ecmd->env[++i])
	{
		diff = ecmd->env[i] + ft_strlen(ecmd->env[i]) - ft_strchr(ecmd->env[i], '=');
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
	exit(EXIT_SUCCESS);
}

void	ft_unset_with_args(t_ecmd *ecmd)
{
	char	**new_env;
	size_t	diff;
	int		i;
	int		j;

	i = ft_nb_str(ecmd->env);
	new_env = malloc(sizeof(*new_env) * i);
	if (!new_env)
		ft_error(MALLOC_FAILED, "new_env : malloc failed");
	i = -1;
	j = 0;
	while (ecmd->env[++i])
	{
		diff = ecmd->env[i] + ft_strlen(ecmd->env[i]) - ft_strchr(ecmd->env[i], '=');
		if (!ft_strncmp(ecmd->argv[1], ecmd->env[i], diff))
			free(ecmd->env[i]);
		else
			new_env[j++] = ecmd->env[i];
	}
	new_env[j] = NULL;
	*ecmd->env = *new_env;
	free(new_env);
}
