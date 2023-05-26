/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:43:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/26 23:54:44 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_there_is_sdquote(char *line)
{
	char	*sq;
	char	*dq;

	sq = ft_strchr(line, SQUAOTE);
	dq = ft_strchr(line, DQUAOTE);
	if (sq || dq)
		return (true);
	return (false);
}

int	ft_who_englobe(char *line)
{
	if (ft_strchr(line, '\'') < ft_strchr(line, '"'))
		return (SQUAOTE);
	return (DQUAOTE);
}

int	ft_is_closed(char *line)
{
	int	i;
	int	scount;
	int	dcount;

	i = -1;
	scount = 0;
	dcount = 0;
	while (line[++i])
	{
		if (line[i] == SQUAOTE)
			scount++;
		if (line[i] == DQUAOTE)
			dcount++;
	}
	if (scount % 2 || dcount % 2)
		return (false);
	return (true);
}

static void	ft_update_value(char **tab, int i)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(tab[i], "$?", ft_strlen(tab[i])))
	{
		tmp = tab[i];
		tab[i] = ft_itoa(g_inf->exit_code);
	}
	else
	{
		tmp = tab[i];
		tab[i] = ft_strdup(getenv(ft_strchr(tab[i], '$') + 1));
	}
	free(tmp);
}

void	ft_replace_env(char **tab)
{
	int		i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		if (ft_strchr(tab[i], '$'))
			ft_update_tab(tab, i);
	}
	i = -1;
	while (tab[++i])
	{
		if (ft_strchr(tab[i], '$'))
			ft_update_value(tab, i);
	}
}
