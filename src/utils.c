/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/10/03 17:11:14 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_whitespace(int c)
{
	int	i;

	i = 9;
	while (i < 14)
	{
		if (c == i)
			return (true);
		i++;
	}
	return (c == 32);
}

pid_t	ft_fork(t_ginf *ginf)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(ERROR, "fork", strerror(errno), ginf);
	return (pid);
}

void	ft_peek(char **ps)
{
	char	*s;

	s = *ps;
	while (*s && (ft_is_whitespace(*s) || *s == SPACE_TO_CUT))
		s++;
	*ps = s;
}

int	ft_nb_str(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	ft_is_env_empty(char **envp)
{
	int	is_empty;

	is_empty = (!envp || (envp && !*envp));
	if (!is_empty)
		is_empty = (!getenv("PATH") || !getenv("HOME") || !getenv("USER"));
	return (is_empty);
}
