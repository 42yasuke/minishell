/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:43:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/25 17:03:08 by jose             ###   ########.fr       */
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
