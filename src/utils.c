/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/09/25 11:52:37 by jose             ###   ########.fr       */
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

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork", strerror(errno));
	return (pid);
}

void	ft_peek(char **ps)
{
	char	*s;

	s = *ps;
	while (*s && ft_is_whitespace(*s))
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
