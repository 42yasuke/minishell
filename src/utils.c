/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 23:16:02 by jose             ###   ########.fr       */
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
		while (line[i] && ft_is_whitespace(line[i]))
			i++;
		if (chdir(line + i))
			ft_error(CD_FAILED, strerror(errno));
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

static int	ft_gettoken_suite(char **ps, char *es, char **s, char **eq)
{
	char	*g;

	g = *s;
	while(g < es && !ft_is_whitespace(*g) && !ft_strchr("><|", *g))
		g++;
	if (eq)
		*eq = g;
	g = ft_rm_ws_until_es(g, es);
	*ps = g;
	return ('a');
}

int	ft_gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	s = ft_rm_ws_until_es(s, es);
	if (q)
		*q = s;
	ret = *s;
	if (*s && (*s == '|' || *s == '<'))
		s++;
	else if (*s && *s == '>')
	{
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
	}
	else
		return (ft_gettoken_suite(ps, es, &s, eq));
	return (ret);
}
