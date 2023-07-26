/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:58:14 by jose              #+#    #+#             */
/*   Updated: 2023/07/25 20:22:30 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_ginf(char **envp, int init_all)
{
	if (init_all)
	{
		g_inf = malloc(sizeof(*g_inf));
		if (!g_inf)
			ft_error(MALLOC_FAILED, "g_inf", "malloc failed");
		g_inf->env = ft_cpy_envp(envp);
		g_inf->exit_code = 0;
	}
	g_inf->line = NULL;
	g_inf->top = NULL;
	g_inf->interpret = true;
	g_inf->is_child_process = false;
	g_inf->here_doc_quit = false;
	g_inf->here_doc = false;
	g_inf->tmp_stdin = -1;
}

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

	i_nbr = 0;
	i_llm = 0;
	if (ft_strlen(nbr) > ft_strlen(llm))
		return (false);
	if (ft_strlen(nbr) < ft_strlen(llm))
		return (true);
	while (nbr[i_nbr])
	{
		if (nbr[i_nbr++] > llm[i_llm++])
			return (false);
	}
	return (true);
}

int	ft_compare_to_llmax_and_llmin(char *nbr)
{
	char	*llmin;
	char	*llmax;

	llmin = ft_illtoa(LLONG_MIN);
	llmax = ft_illtoa(LLONG_MAX);
	if (nbr[0] == '-')
		return (ft_helph_to_compare(nbr, llmin));
	return (ft_helph_to_compare(nbr, llmax));
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
