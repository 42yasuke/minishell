/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:58:14 by jose              #+#    #+#             */
/*   Updated: 2023/05/25 16:28:01 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_ginf(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		ft_error(BAD_PARAMETERS, "minishell : bad usage");
	g_inf = malloc(sizeof(*g_inf)); //initialisation
	if (!g_inf)
		ft_error(MALLOC_FAILED, "g_inf : malloc failed");
	g_inf->exit_code = 0;
	g_inf->line = NULL;
	g_inf->top = NULL;
}
