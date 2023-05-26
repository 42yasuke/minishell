/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:31 by jose              #+#    #+#             */
/*   Updated: 2023/05/26 20:17:00 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_sd_quote_manager(char *line)
{
	char	**tab;
	char	*new_line;

	if (ft_there_is_sdquote(line))
	{
		if (!ft_is_closed(line))
			ft_error(SDQUOTE_FAILED, "sdquote : not closed");
		else
		{
			if (ft_who_englobe(line) == SQUAOTE)
				tab = ft_split(line, SQUAOTE);
			else
			{
				tab = ft_split(line, DQUAOTE);
				ft_replace_env(tab);
			}
		}
	}
	else
	{
		tab = ft_split(line, ' ');
		ft_replace_env(tab);
	}
	new_line = ft_merge_tab(tab);
	return (free(line), ft_free_all(tab), new_line);
}
