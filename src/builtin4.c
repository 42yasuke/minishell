/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:11:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/28 01:39:21 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exit_no_pipe(char *line)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(line, ' ');
	if (tmp[1])
	{
		if (tmp[2])
			ft_error(EXIT_FAILED, "exit : invalid argument");
		if (tmp[1][0] == '-')
			ft_error(EXIT_FAILED, "exit : invalid option");
		else
		{
			while (tmp[1][++i])
			{
				if (!ft_isdigit(tmp[1][i]))
					ft_error(EXIT_FAILED, "exit : invalid argument");
			}
			if (ft_strlen(tmp[1]) > 3 || ft_atoi(tmp[1]) > 255)
				ft_error(EXIT_FAILED, "exit : invalid argument");
			i = ft_atoi(tmp[1]);
			(ft_printf("exit\n"), ft_free_all(tmp), ft_free_ginf(), exit(i));
		}
	}
	(ft_printf("exit\n"), ft_free_all(tmp), ft_free_ginf(), exit(EXIT_SUCCESS));
}

int	ft_is_builtin_no_pipe(char *line)
{
	int	is_builtin;

	is_builtin = (!ft_strncmp(line, "cd", 2) || !ft_strncmp(line, "export", 6) \
	|| !ft_strncmp(line, "unset", 5) || !ft_strncmp(line, "exit", 4));
	return (is_builtin);
}
