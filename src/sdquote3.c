/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:31 by jose              #+#    #+#             */
/*   Updated: 2023/05/26 20:46:54 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_cpy_str(char **tab, char **tab2)
{
	int	i;

	i = -1;
	while (tab2[++i])
		tab[i] = tab2[i];
}

static void ft_no_quote(char *line, char **tab)
{
	char	**tab2;

	tab2 = ft_split(line, ' ');
	ft_cpy_str(tab, tab2);
	ft_replace_env(tab);
}

static void	ft_quote(char *line, char **tab)
{
	char	**tab2;

	if (!ft_is_closed(line))
		ft_error(SDQUOTE_FAILED, "sdquote : not closed");
	else
	{
		if (ft_who_englobe(line) == SQUAOTE)
		{
			tab2 = ft_split(line, SQUAOTE);
			ft_cpy_str(tab, tab2);
		}
		else
		{
			tab2 = ft_split(line, DQUAOTE);
			ft_cpy_str(tab, tab2);
			ft_replace_env(tab);
		}
	}
}

char	*ft_sd_quote_manager(char *line)
{
	char	**tab;
	char	*new_line;
	int		i;

	i = -1;
	tab = malloc(sizeof(*tab) * (MAXARG + 1));
	if (!tab)
		ft_error(MALLOC_FAILED, "tab : malloc failed");
	while (++i < MAXARG + 1)
		tab[i] = NULL;
	if (ft_there_is_sdquote(line))
		ft_quote(line, tab);
	else
		ft_no_quote(line, tab);
	new_line = ft_merge_tab(tab);
	return (free(line), ft_free_all(tab), new_line);
}
