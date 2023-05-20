/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:38:16 by jose              #+#    #+#             */
/*   Updated: 2023/05/20 20:14:45 by jose             ###   ########.fr       */
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
		return (ft_cd(line), true);
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