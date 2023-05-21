/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 12:16:16 by jose             ###   ########.fr       */
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

void	ft_cd_no_pipe(char *line)
{
	int	i;

	i = 2;
	while (line[i] && line[i] != '|')
		i++;
	if (!line[i])
	{
		i = 2;
		while (line[i] && !ft_is_whitespace(line[i]))
			i++;
		if (!line[i] && ft_strlen(line) > 2)
		{
			if (chdir(line + 3))
				ft_error(CD_FAILED, strerror(errno));
		}
		ft_error(CD_FAILED, "bro, seriously ?");
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, strerror(errno));
	return (pid);
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
