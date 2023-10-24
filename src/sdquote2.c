/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:31 by jose              #+#    #+#             */
/*   Updated: 2023/10/24 14:41:49 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_remove_sdquote(char *line, char sdq)
{
	char	*quote;
	int		change;
	int		i;

	quote = ft_strchr(line, sdq);
	change = false;
	while (quote)
	{
		i = -1;
		while (++i < 2)
		{
			if (*quote == sdq && *(quote + 1) == sdq)
				change = true;
			ft_memmove(quote, quote + 1, ft_strlen(quote + 1));
			if (i == 1 && change)
			{
				change = false;
				*quote = ' ';
			}
			quote = ft_strchr(line, sdq);
		}
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
