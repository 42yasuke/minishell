/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:34 by jose              #+#    #+#             */
/*   Updated: 2023/09/19 20:01:43 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_is_between_sdquote(char *line, char *c, char quote)
{
	char	*str_sdq;
	char	*tmp;

	str_sdq = ft_strchr(line, quote);
	while (str_sdq)
	{
		tmp = ft_strchr(str_sdq + 1, quote);
		if (!tmp || (c > str_sdq && c < tmp))
			return (true);
		str_sdq = ft_strchr(tmp + 1, quote);
	}
	return (false);
}

static void	ft_replace_this_char(char *line, char chr, char spe)
{
	char	*sp_char;

	sp_char = ft_strchr(line, chr);
	while (sp_char)
	{
		if (!ft_is_between_sdquote(line, sp_char, SQ) && \
		!ft_is_between_sdquote(line, sp_char, DQ))
			*sp_char = spe;
		sp_char = ft_strchr(sp_char + 1, chr);
	}
}

static void	ft_find_dollar_n_replace_it(char *line)
{
	char	*dollar;
	char	*tmp;

	dollar = ft_strchr(line, '$');
	while (dollar)
	{
		if (ft_is_between_sdquote(line, dollar, DQ) || \
		!ft_is_between_sdquote(line, dollar, SQ))
		{
			tmp = dollar + 1;
			if (*tmp && (ft_isalnum(*tmp) || *tmp == '?'))
				*dollar = DOLLAR;
			else if (!ft_is_between_sdquote(line, dollar, DQ) \
			&& (*tmp == DQ || *tmp == SQ))
				*dollar = DOLLAR;
		}
		dollar = ft_strchr(dollar + 1, '$');
	}
}

static void	ft_replace_sdquote_char(char *line)
{
	char	*quote;
	char	*quote_next;

	quote = ft_strchr(line, ft_get_quote(line));
	while (quote)
	{
		quote_next = ft_strchr(quote + 1, *quote);
		if (*quote == DQUOTE)
		{
			*quote = DQ;
			*quote_next = DQ;
		}
		else
		{
			*quote = SQ;
			*quote_next = SQ;
		}
		quote = ft_strchr(quote_next, ft_get_quote(quote_next));
	}
}

char	*ft_replace_special_chraracter(char *line)
{
	char	*ret;

	if (ft_there_is_sdquote(line))
		ft_replace_sdquote_char(line);
	ft_replace_this_char(line, '|', PIPE);
	ft_replace_this_char(line, '<', REDIN);
	ft_replace_this_char(line, '>', REDOUT);
	ft_replace_this_char(line, ' ', SPACE_TO_CUT);
	ft_find_dollar_n_replace_it(line);
	ret = ft_find_n_replace_var(line);
	return (ft_replace_this_char(ret, ' ', SPACE_TO_CUT), ret);
}
