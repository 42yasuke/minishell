/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:07:45 by jralph            #+#    #+#             */
/*   Updated: 2022/11/13 13:07:51 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isgoodchar(char const *set, char c)
{
	size_t	i;

	i = 0;
	if (set)
	{
		while (set[i])
		{
			if (c == set[i])
				return (0);
			i++;
		}
	}
	return (1);
}

static size_t	ft_numgoodchar(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start])
	{
		if (ft_isgoodchar(set, s1[start]))
			break ;
		start++;
	}
	while (end)
	{
		if (ft_isgoodchar(set, s1[end]))
			break ;
		end--;
	}
	if (start > end)
		return (0);
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = 0;
	if (s1)
	{
		res = malloc(sizeof(*s1) * (ft_numgoodchar(s1, set) + 1));
		if (!res)
			return (0);
		while (s1[i] && !ft_isgoodchar(set, s1[i]))
			i++;
		if (s1[i] && ft_isgoodchar(set, s1[i]))
		{
			while (j < ft_numgoodchar(s1, set))
			{
				res[j] = s1[j + i];
				j++;
			}
		}
		res[j] = 0;
	}
	return (res);
}
