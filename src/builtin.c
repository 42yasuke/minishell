/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:38:16 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 05:23:29 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_cd(char *line)
{
	int	i;

	i = 0;
	while(line)
		i++;
}

int	ft_is_builtin(char *line)
{
	if (!ft_strncmp(line, "cd", 2))
		return (true);
	if (!ft_strncmp(line, "echo", 4))
		return (true);
	if (!ft_strncmp(line, "pwd", 3))
		return (true);
	if (!ft_strncmp(line, "export", 6))
		return (true);
	if (!ft_strncmp(line, "unset", 5))
		return (true);
	if (!ft_strncmp(line, "env", 3))
		return (true);
	if (!ft_strncmp(line, "exit", 4))
		return (true);
	return (false);
}

void	ft_builtin_manager(char *line)
{
	(void)line;
	ft_printf(">>> builtin_manager <<<\n");
}