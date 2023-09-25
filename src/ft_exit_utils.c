/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:50:56 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 11:28:03 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_ll	ft_atoll(const char *nptr)
{
	int		i;
	t_ll	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	ft_helph_to_compare(char *nbr, char *llm)
{
	int		i_nbr;
	int		i_llm;
	int		i;

	i_nbr = 0;
	i_llm = 0;
	if (ft_strlen(nbr) > ft_strlen(llm))
		return (false);
	if (ft_strlen(nbr) < ft_strlen(llm))
		return (true);
	while (nbr[i_nbr])
	{
		if (nbr[i_nbr++] > llm[i_llm++])
		{
			i = -1;
			while (++i < i_nbr)
			{
				if (nbr[i] >= llm[i])
					return (false);
			}
		}
	}
	return (true);
}

int	ft_compare_to_llmax_and_llmin(char *nbr)
{
	char	*llmin;
	char	*llmax;
	int		ret;

	llmin = ft_illtoa(LLONG_MIN);
	llmax = ft_illtoa(LLONG_MAX);
	if (nbr[0] == '-')
		ret = ft_helph_to_compare(nbr, llmin);
	else
		ret = ft_helph_to_compare(nbr, llmax);
	return (free(llmax), ret);
}

int	ft_rest_of_div(t_ll dd, int d)
{
	if (dd == LLONG_MIN)
		return (LLONG_MIN + (LLONG_MAX / d + 1) * d);
	if (dd < 0)
	{
		return (dd + (-dd / d) * d);
	}
	return (dd - (dd / d) * d);
}
