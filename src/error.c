/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/05/25 15:27:21 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_error(int err, char *msg_err)
{
	if (err == BAD_PARAMETERS)
		ft_printf("Error : %s\n", msg_err);
	else
		ft_printf("Error : %s\n", msg_err);
	if(g_inf)
	{
		g_inf->exit_code = EXIT_FAILURE;
		free(g_inf->line);
		if (g_inf->top)
			ft_free_cmd(g_inf->top);
		free(g_inf);
		g_inf = NULL;
	}
	exit(EXIT_FAILURE);
}
