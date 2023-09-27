/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 02:41:41 by jralph            #+#    #+#             */
/*   Updated: 2022/11/12 02:41:44 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_safe(size_t nmemb, size_t size)
{
	size_t	size_max;

	size_max = LONG_MAX;
	if (nmemb == 0 || size == 0)
		return (0);
	if (nmemb > size_max / size || size > size_max / nmemb)
		return (LONG_MAX);
	return (nmemb * size);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;

	res = malloc(ft_safe(nmemb, size));
	if (!res)
		return (0);
	ft_memset(res, 0, ft_safe(nmemb, size));
	return (res);
}
