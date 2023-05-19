/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:56:36 by jralph            #+#    #+#             */
/*   Updated: 2022/11/13 00:56:41 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s, unsigned int start, size_t len)
{
	if (len > ft_strlen(s) - start)
		return (ft_strlen(s) - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	res = 0;
	if (start > (unsigned int)ft_strlen(s) || !*s)
	{
		res = malloc(sizeof(*s));
		if (!res)
			return (0);
	}
	else if (*s)
	{
		len = ft_len(s, start, len);
		res = malloc(sizeof(*s) * (len + 1));
		if (!res)
			return (0);
		while (s[i + start] && i < len)
		{
			res[i] = s[start + i];
			i++;
		}
	}
	res[i] = 0;
	return (res);
}
