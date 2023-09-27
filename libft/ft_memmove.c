/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:25:21 by jralph            #+#    #+#             */
/*   Updated: 2023/09/25 17:44:48 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{	
	size_t	i;

	if (src < dest)
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		i = 0;
		while (i < n && ((char *)src)[i])
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
		while (((char *)dest)[i])
		{
			((char *)dest)[i] = '\0';
			i++;
		}
	}
	return (dest);
}
