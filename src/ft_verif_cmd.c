/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:45:20 by jose              #+#    #+#             */
/*   Updated: 2023/10/14 21:49:52 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_red(char *line, char red)
{
	char	*str;

	str = ft_strchr(line, red);
	if (!str)
		return (true);
	if (str[1] == red && str[2] == red)
		return (false);
	str++;
	ft_peek(&str);
	if (*str == red && *(str - 1) != red)
		return (false);
	else if (*str && *str != '|')
		return (true);
	return (false);
}

static int	ft_verif_pipe(char *line)
{
	char	*str;

	str = ft_strchr(line, '|');
	if (!str)
		return (true);
	str++;
	ft_peek(&str);
	if (*str && *str != '|')
		return (true);
	return (false);
}

static int	ft_verif_cmd_suite(char *line)
{
	char	*str;

	str = ft_strchr(line, '|');
	ft_peek(&line);
	if (!(str - line))
		return (false);
	while (str)
	{
		if (ft_is_between_sdquote(line, str, 39) || \
		ft_is_between_sdquote(line, str, 34))
			return (true);
		if (!ft_verif_pipe(str))
			return (false);
		str++;
		str = ft_strchr(str, '|');
	}
	return (true);
}

int	ft_verif_cmd(char *line)
{
	char	*str;

	str = ft_strchr(line, '<');
	while (str)
	{
		if (ft_is_between_sdquote(line, str, 39) || \
		ft_is_between_sdquote(line, str, 34))
			return (true);
		if (!ft_verif_red(str, '<'))
			return (false);
		str++;
		str = ft_strchr(str, '<');
	}
	str = ft_strchr(line, '>');
	while (str)
	{
		if (ft_is_between_sdquote(line, str, 39) || \
		ft_is_between_sdquote(line, str, 34))
			return (true);
		if (!ft_verif_red(str, '>'))
			return (false);
		str++;
		str = ft_strchr(str, '>');
	}
	return (ft_verif_cmd_suite(line));
}
