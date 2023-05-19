/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:22:23 by jose              #+#    #+#             */
/*   Updated: 2023/01/28 01:46:37 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		cmp;
	va_list	args;

	i = 0;
	cmp = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
			cmp += ft_putchar(str[i]);
		else
		{
			i++;
			ft_goodc(args, str[i], &cmp);
		}
		i++;
	}
	return (cmp);
}
