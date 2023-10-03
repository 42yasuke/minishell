/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:43:51 by jose              #+#    #+#             */
/*   Updated: 2023/09/30 20:42:02 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_there_is_sdquote(char *line)
{
	char	*sq;
	char	*dq;

	sq = ft_strchr(line, SQUOTE);
	dq = ft_strchr(line, DQUOTE);
	if (sq || dq)
		return (true);
	return (false);
}

int	ft_get_quote(char *line)
{
	char	*sq;
	char	*dq;

	sq = ft_strchr(line, SQUOTE);
	dq = ft_strchr(line, DQUOTE);
	if (sq && dq)
	{
		if (sq < dq)
			return (SQUOTE);
		return (DQUOTE);
	}
	else if (sq)
		return (SQUOTE);
	return (DQUOTE);
}

int	ft_is_closed(char *line)
{
	char	*new_line;
	char	*tmp;
	int		quote;

	new_line = ft_strdup(line);
	if (!new_line)
		ft_error(ERROR, "ft_strdup", strerror(errno), NULL);
	tmp = new_line;
	while (tmp && ft_there_is_sdquote(tmp))
	{
		quote = ft_get_quote(tmp);
		tmp = ft_strchr(tmp, quote);
		if (tmp)
		{
			tmp++;
			tmp = ft_strchr(tmp, quote);
			if (!tmp)
				return (free(new_line), false);
		}
		tmp++;
	}
	return (free(new_line), true);
}

char	*ft_update_value(char *str, char **env)
{
	if (!ft_strlen(str))
		return (ft_strdup(str));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		str = ft_itoa(g_exit_code);
	else
		str = ft_strdup(ft_getenv(str, env));
	return (str);
}
