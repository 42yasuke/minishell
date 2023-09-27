/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:31 by jose              #+#    #+#             */
/*   Updated: 2023/09/20 00:49:03 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_remove_sdquote(char *line, char sdq)
{
	char	*quote;
	int		i;

	quote = ft_strchr(line, sdq);
	while (quote)
	{
		i = -1;
		while (++i < 2)
		{
			ft_memmove(quote, quote + 1, ft_strlen(quote + 1));
			quote = ft_strchr(line, sdq);
		}
	}
}

char	*ft_sd_quote_manager(char *line)
{
	char	*new_line;

	new_line = ft_replace_special_chraracter(line);
	ft_remove_useless_space_in_export_cmd(new_line);
	ft_remove_sdquote(new_line, SQ);
	ft_remove_sdquote(new_line, DQ);
	return (new_line);
}
