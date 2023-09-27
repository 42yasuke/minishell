/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goodc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:27:23 by jose              #+#    #+#             */
/*   Updated: 2023/01/28 01:46:45 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_goodc(va_list args, char c, int *cmp)
{
	unsigned long	pn;

	if (c == 'c')
		*cmp += ft_putchar((char)va_arg(args, int));
	else if (c == 's')
		*cmp += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
	{
		pn = (unsigned long)(va_arg(args, void *));
		if (pn == 0)
			*cmp += ft_putstr("(nil)");
		else
			*cmp += ft_putptr((void *)pn, 0);
	}
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), cmp);
	else if (c == 'u')
		*cmp += ft_putnbru(va_arg(args, unsigned int));
	else if (c == 'x')
		*cmp += ft_puthexa_min(va_arg(args, unsigned int));
	else if (c == 'X')
		*cmp += ft_puthexa_maj(va_arg(args, unsigned int));
	else if (c == '%')
		*cmp += ft_putchar('%');
}
