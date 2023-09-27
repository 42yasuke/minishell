/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 01:31:32 by jralph            #+#    #+#             */
/*   Updated: 2023/01/20 14:51:37 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compt(long n)
{
	int	res;

	res = 0;
	if (!n)
		return (1);
	if (n < 0)
		return (ft_compt(-n));
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

static char	*ft_strrev(char *s)
{
	size_t	i;
	char	tmp;

	i = 0;
	while (i < ft_strlen(s) / 2)
	{
		tmp = s[i];
		s[i] = s[ft_strlen(s) - 1 - i];
		s[ft_strlen(s) - 1 - i] = tmp;
		i++;
	}
	return (s);
}

static void	ft_alloc(int n, char **res)
{
	if (n >= 0)
		*res = malloc (sizeof(**res) * (ft_compt(n) + 1));
	else
		*res = malloc (sizeof(**res) * (ft_compt(n) + 2));
	if (!*res)
		return ;
}

static void	ft_loop(int n, int *i, long *begin, char **res)
{
	while (ft_compt(n) != *i)
	{
		*(*res + *i) = *begin % 10 + '0';
		*i += 1;
		*begin /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	begin;

	begin = n;
	i = 0;
	ft_alloc(n, &res);
	if (!res)
		return (0);
	if (n < 0)
	{
		begin = -begin;
	}
	ft_loop(n, &i, &begin, &res);
	if (n < 0)
	{
		res[i] = '-';
		i++;
	}
	res[i] = 0;
	res = ft_strrev(res);
	return (res);
}
