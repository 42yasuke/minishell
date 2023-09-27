/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:48:08 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 09:26:51 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_find_n_update_env_name_in_env(char **env, char *str, int lst)
{
	char	*tmp;
	int		i;
	size_t	diff;

	i = -1;
	while (env[++i])
	{
		diff = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!ft_strncmp(str, env[i], diff))
		{
			tmp = env[i];
			if (lst && ft_strchr(str, '='))
				env[i] = ft_add_guigui_on_env_name(str);
			else if (!lst)
				env[i] = ft_strdup(str);
			if ((lst && ft_strchr(str, '=')) || !lst)
				free(tmp);
			break ;
		}
	}
	if (!env[i] && lst)
		env[i] = ft_add_guigui_on_env_name(str);
	else if (!env[i] && !lst)
		env[i] = ft_strdup(str);
}

void	ft_update_env_n_lst_env(char *str)
{
	if (ft_strchr(str, '='))
		ft_find_n_update_env_name_in_env(g_inf->env, str, false);
	ft_find_n_update_env_name_in_env(g_inf->lst_env, str, true);
}

char	*ft_get(char *str)
{
	char	**env;
	int		i;
	size_t	diff;

	i = -1;
	env = g_inf->env;
	while (env[++i])
	{
		diff = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!ft_strncmp(str, env[i], diff))
			return (env[i]);
	}
	return (NULL);
}

char	*ft_getenv(char *str)
{
	char	**env;
	int		i;
	size_t	diff;

	i = -1;
	env = g_inf->env;
	while (env[++i])
	{
		diff = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!ft_strncmp(str, env[i], diff))
			return (env[i] + diff + 1);
	}
	return (NULL);
}
