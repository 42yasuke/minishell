/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:40:13 by jralph            #+#    #+#             */
/*   Updated: 2022/11/10 08:40:19 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_length;

	i = 0;
	dest_length = ft_strlen(dest);
	if (size)
	{
		while (src[i] && i + dest_length < size - 1)
		{
			dest[i + dest_length] = src[i];
			i++;
		}
		dest[i + dest_length] = 0;
	}
	if (dest_length > size)
		return (size + ft_strlen(src));
	return (dest_length + ft_strlen(src));
}
