/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/05/29 22:47:16 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_error(int err, char *msg_err)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	ft_printf("Error : %s\n", msg_err);
	if (err == EXECVE_FAILED)
		exit_code = 127;
	ft_free_ginf(true);
	exit(exit_code);
}

void	ft_error2(char *msg_err, int err)
{
	write (2, msg_err, ft_strlen(msg_err));
	g_inf->exit_code = err;
}