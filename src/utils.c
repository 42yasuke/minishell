/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/05/20 21:31:34 by jose             ###   ########.fr       */
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
