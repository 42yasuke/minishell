/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:43:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/31 02:49:01 by jose             ###   ########.fr       */
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
	char	*sq;
	char	*dq;

	sq = ft_strchr(line, SQUAOTE);
	dq = ft_strchr(line, DQUAOTE);
	if (sq && dq)
	{
		if (ft_strchr(line, SQUAOTE) < ft_strchr(line, DQUAOTE))
			return (SQUAOTE);
		return (DQUAOTE);
	}
	else if (sq)
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
	if (scount % 2 && ft_who_englobe(line) == SQUAOTE)
		return (false);
	else if (dcount % 2 && ft_who_englobe(line) == DQUAOTE)
		return (false);
	return (true);
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
		{
			ft_update_tab(tab, i);
			i--;
		}
	}
}
