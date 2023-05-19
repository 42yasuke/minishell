/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/05/19 15:38:00 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_error(int err, char *msg_err)
{
	if (err == BAD_PARAMETERS)
		(ft_printf("Error : %s\n", msg_err));
	else if (err == MALLOC_FAILED)
		ft_printf("Error : %s\n", msg_err);
	exit(EXIT_FAILURE);
}
