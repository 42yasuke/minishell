/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 02:55:54 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_error(int err, char *msg_err)
{
	if (err == BAD_PARAMETERS)
		ft_printf("Error : %s\n", msg_err);
	else
		ft_printf("Error : %s\n", msg_err);
	if(g_cmd)
		ft_free_cmd(g_cmd);
	exit(EXIT_FAILURE);
}
