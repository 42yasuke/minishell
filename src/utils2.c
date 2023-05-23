/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:19:59 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 11:05:01 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_rm_ws_until_es(char *s, char *es)
{
	while (s < es && ft_is_whitespace(*s))
		s++;
	return (s);
}

int	ft_peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_is_whitespace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

int	ft_nb_str(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**ft_cpy_envp(char **envp)
{
	int		i;
	char	**env;

	i = ft_nb_str(envp);
	env = malloc(sizeof(*env) * (i + 1));
	if (!env)
		ft_error(MALLOC_FAILED, "env : malloc failed");
	i = -1;
	while (envp[++i])
		env[i] = NULL;
	env[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			(ft_free_all(env), ft_error(MALLOC_FAILED, "env : malloc failed durinf copy"));
	}
	return (env);
}
