/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:12:36 by jose              #+#    #+#             */
/*   Updated: 2023/08/01 18:33:07 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_infile_red(char *line)
{
	char	*str;

	str = ft_strchr(line, '<');
	if (!str)
		return (true);
	str++;
	ft_peek(&str);
	if (*str == '<')
	{
		str++;
		ft_peek(&str);
	}
	if (*str && *str != '|')
		return (true);
	return (false);
}

static int	ft_verif_outfile_red(char *line)
{
	char	*str;

	str = ft_strchr(line, '>');
	if (!str)
		return (true);
	str++;
	ft_peek(&str);
	if (*str == '>')
	{
		str++;
		ft_peek(&str);
	}
	if (*str && *str != '|')
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
		if (!ft_verif_infile_red(str))
			return (false);
		str++;
		str = ft_strchr(str, '<');
	}
	str = ft_strchr(line, '>');
	while (str)
	{
		if (!ft_verif_outfile_red(str))
			return (false);
		str++;
		str = ft_strchr(str, '>');
	}
	return (ft_verif_cmd_suite(line));
}
