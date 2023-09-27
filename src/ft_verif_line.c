/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:45:13 by jose              #+#    #+#             */
/*   Updated: 2023/09/26 21:26:13 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_line_suite(char *line, int flag)
{
	if (!ft_strncmp(line, "", ft_strlen(line)))
		return (g_inf->exit_code = EXIT_SUCCESS, false);
	if (flag && ft_there_is_sdquote(line) && !ft_is_closed(line))
		return (ft_error2("sdquote", "not closed", 2), false);
	return (true);
}

int	ft_verif_line(char *line, int flag)
{
	DIR	*dir_ptr;

	if (!ft_verif_cmd(line))
	{
		write(STDERR_FILENO, "minishell: error redirection or pipe\n", 38);
		g_inf->exit_code = 2;
		return (false);
	}
	dir_ptr = opendir(line);
	if (dir_ptr)
	{
		closedir(dir_ptr);
		write(STDERR_FILENO, "minishell: error : is a directory\n", 35);
		g_inf->exit_code = 126;
		return (false);
	}
	return (ft_verif_line_suite(line, flag));
}
