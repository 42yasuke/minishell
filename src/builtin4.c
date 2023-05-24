/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:11:51 by jose              #+#    #+#             */
/*   Updated: 2023/05/24 20:59:11 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_exit_no_pipe(char *line, char **envp)
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
			(ft_printf("exit\n"), ft_free_all(tmp), ft_free_all(envp), free(line), exit(ft_atoi(tmp[1])));
		}
	}
	(ft_printf("exit\n"), ft_free_all(tmp), ft_free_all(envp), free(line), exit(EXIT_SUCCESS));
}
