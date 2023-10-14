/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:10:16 by jralph            #+#    #+#             */
/*   Updated: 2023/10/14 22:37:00 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cpy(char *res, char const *s, size_t start)
{
	size_t	i;

	i = start;
	while (s && *s)
	{
		res[i] = *s;
		s++;
		i++;
	}
}

static char	*ft_getlines(char *stash, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc (sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (stash[i] && i < len)
	{
		res[i] = stash[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static void	ft_loop(char **stash, int fd)
{
	char		*tmp;
	int			len;
	char		*buf;

	len = BUFFER_SIZE;
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	while (!ft_strchr(*stash, '\n') && len == BUFFER_SIZE)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buf[len] = '\0';
		tmp = *stash;
		*stash = ft_strjoin(tmp, buf);
		if (!*stash)
		{
			*stash = NULL;
			(free(tmp), free(buf));
			return ;
		}
		free(tmp);
	}
	free(buf);
}

static char	*ft_last_line(char **stash)
{
	char	*lines;

	lines = malloc(sizeof(char) * (ft_strlen(*stash) + 1));
	if (!lines)
		return (NULL);
	ft_cpy(lines, *stash, 0);
	lines[ft_strlen(*stash)] = '\0';
	free(*stash);
	*stash = NULL;
	return (lines);
}

char	*get_next_line(int fd)
{
	static char		*stash = NULL;
	char			*lines;

	lines = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	ft_loop(&stash, fd);
	if (ft_strchr(stash, '\n'))
	{
		lines = ft_getlines(stash, ft_strchr(stash, '\n') - stash + 1);
		if (!lines)
		{
			free(stash);
			return (NULL);
		}
		return (free(stash), stash = NULL, lines);
	}
	else if (stash && *stash)
		return (ft_last_line(&stash));
	return (free(stash), NULL);
}
