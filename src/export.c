/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:02:12 by jose              #+#    #+#             */
/*   Updated: 2023/05/30 13:36:33 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_analyse(char *str)
{
	int		i;

	i = -1;
	if (!ft_isalpha(str[0]))
		return (ft_error2("exoprt", "invalid arg", 1), false);
	if (!ft_strchr(str, '='))
	{
		while (str[++i])
			if (!ft_isalnum(str[i]))
				return (ft_error2("exoprt", "invalid arg", 1), false);
	}
	else
	{
		while (str[++i] != '=')
		{
			if (!ft_isalnum(str[i]))
				return (ft_error2("exoprt", "invalid arg", 1), false);
		}
	}
	return (true);
}
