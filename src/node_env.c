/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:26:04 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 11:27:43 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_range_lst(t_lenv *lst_env, char **envp)
{
	int		i;
	t_lenv	*tmp;
	t_lenv	*save;

	while (envp[i])
	{
		tmp = lst_env;
		save = tmp;
		while (tmp)
		{
			if(ft_strncmp(save->env_name, tmp->env_name, \
			ft_strlen(save->env_name)) > 0)
				save = tmp;
			tmp = tmp->next;
		}
		save->id = i;
		i++;
	}
}

t_lenv	*ft_add_nenv(t_lenv *lst_env, int i, char **envp)
{
	t_lenv	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (tmp)
		(ft_free_lst(lst_env), ft_error(MALLOC_FAILED, strerror(errno)));
	tmp->env_name = envp[i];
	tmp->id = -1;
	tmp->next = NULL;
	return (tmp);
}

static void	ft_make_lst(t_lenv *lst_env, char **envp)
{
	t_lenv	*tmp;
	int		i;

	i = 1;
	tmp = lst_env;
	while (envp[i])
	{
		tmp->next = ft_add_nenv(lst_env, i, envp);
		tmp = tmp->next;
		i++;
	}
}

t_lenv	*ft_get_node(t_lenv *lst_env, int id)
{
	t_lenv	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_init_lst(t_lenv *lst_env, char **envp)
{
	lst_env->env_name = envp[0];
	lst_env->id = -1;
	lst_env->next = NULL;
	if (envp[0])
		(ft_make_lst(lst_env, envp), ft_range_lst(lst_env, envp));
}
