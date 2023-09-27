/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:24:15 by jose              #+#    #+#             */
/*   Updated: 2023/09/18 12:45:04 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_analyse(char *str)
{
	if (!ft_strlen(str))
		return (ft_error2("exoprt", "invalid arg", 1), false);
	if (*str == '-')
		return (ft_error2("exoprt", "invalid option", 2), false);
	if (!ft_isalpha(*str) && *str != '_')
		return (ft_error2("exoprt", "invalid arg", 1), false);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (ft_error2("exoprt", "invalid arg", 1), false);
		str++;
	}
	return (true);
}
