/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:29:50 by jose              #+#    #+#             */
/*   Updated: 2023/10/03 17:13:42 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_double_dollar(char *dollar)
{
	if (*(dollar + 1) == '$')
	{
		*dollar = '4';
		*(dollar + 1) = '2';
	}
}

static int	ft_is_dollar_to_remove(char *str, char *dollar)
{
	int		remove_it;
	char	*tmp;

	tmp = dollar + 1;
	remove_it = !ft_is_between_sdquote(str, dollar, DQ);
	remove_it = (remove_it && (*tmp == DQ || *tmp == SQ));
	if (dollar == str)
		return (remove_it);
	remove_it = (remove_it && *(dollar - 1) != '$');
	return (remove_it);
}

static int	ft_is_a_dollar_limiter(char *str, char *dollar)
{
	char	*tmp;

	while (dollar != str)
	{
		tmp = dollar - 1;
		while (tmp != str && ft_is_whitespace(*tmp))
			tmp--;
		if (tmp == str)
			return (true);
		if (*tmp == REDIN && *(tmp - 1) == REDIN)
			return (false);
		dollar--;
	}
	return (true);
}

static int	ft_is_a_good_one(char *str, char *dollar)
{
	int	is_good;

	is_good = *(dollar + 1);
	is_good = (is_good && (ft_isalnum(is_good) || is_good == '?'));
	if (!is_good)
		return (false);
	return (ft_is_a_dollar_limiter(str, dollar));
}

void	ft_find_dollar_n_replace_it(char *line)
{
	char	*dollar;

	dollar = ft_strchr(line, '$');
	while (dollar)
	{
		if (ft_is_between_sdquote(line, dollar, DQ) || \
		!ft_is_between_sdquote(line, dollar, SQ))
		{
			if (ft_is_a_good_one(line, dollar))
				*dollar = DOLLAR;
			else if (ft_is_dollar_to_remove(line, dollar))
				ft_memmove(dollar, dollar + 1, ft_strlen(dollar + 1));
			else if (ft_is_a_dollar_limiter(line, dollar))
				ft_double_dollar(dollar);
		}
		dollar = ft_strchr(dollar + 1, '$');
	}
}
