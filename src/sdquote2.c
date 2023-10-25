/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:31 by jose              #+#    #+#             */
/*   Updated: 2023/10/25 12:45:40 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_remove_sdq_loop(char *line, char sdq, char *quote, int change)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = quote;
	while (++i < 2)
	{
		if (*tmp == sdq && *(tmp + 1) == sdq && !i)
			change = true;
		if (!i)
			ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1));
		else if (change)
		{
			if (!*(tmp + 1) || *(tmp + 1) == SPACE_TO_CUT)
				*tmp = ' ';
			else
				ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1));
		}
		else
			ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1));
		tmp = ft_strchr(line, sdq);
	}
}

static void	ft_remove_sdquote(char *line, char sdq)
{
	char	*quote;
	int		change;

	quote = ft_strchr(line, sdq);
	while (quote)
	{
		change = false;
		ft_remove_sdq_loop(line, sdq, quote, change);
		quote = ft_strchr(line, sdq);
	}
}

char	*ft_sd_quote_manager(char *line, char **env)
{
	char	*new_line;

	new_line = ft_replace_special_chraracter(line, env);
	ft_remove_sdquote(new_line, SQ);
	ft_remove_sdquote(new_line, DQ);
	return (free(line), new_line);
}
