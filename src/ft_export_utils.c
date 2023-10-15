/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:24:15 by jose              #+#    #+#             */
/*   Updated: 2023/10/15 13:42:11 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_analyse(char *str)
{
	if (!ft_strlen(str))
		return (ft_error2(ERROR, "exoprt", "invalid arg"), false);
	if (*str == '-' && ft_strlen(str) > 1)
		return (ft_error2(INVALID_OPTION, "exoprt", "invalid option"), false);
	if (!ft_isalpha(*str) && *str != '_')
		return (ft_error2(ERROR, "exoprt", "invalid arg"), false);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (ft_error2(ERROR, "exoprt", "invalid arg"), false);
		str++;
	}
	return (true);
}
