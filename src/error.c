/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 10:27:59 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_make_msg_err(char *cmd, char *msg_err)
{
	char	*tmp;
	char	*ret;

	ret = ft_strjoin("minishel : ", cmd);
	tmp = ret;
	ret = ft_strjoin(ret, " : ");
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, msg_err);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	return (free(tmp), ret);
}

void	ft_error(int err, char *cmd, char *msg_err)
{
	int		exit_code;
	char	*str;

	str = NULL;
	exit_code = EXIT_FAILURE;
	if (msg_err)
		str = ft_make_msg_err(cmd, msg_err);
	if (msg_err)
		write (STDERR_FILENO, str, ft_strlen(str));
	(free(str), ft_free_ginf(true));
	if (err == EXECVE_FAILED)
		exit_code = 127;
	else if (err == EXIT_FAILED || err == UNSET_FAILED)
		exit_code = 2;
	else if (err == ENV_FAILED)
		exit_code = 125;
	else if (err == SIGINT)
		exit_code = 130;
	else if (err == PERMISSION_DENIED)
		exit_code = 126;
	exit(exit_code);
}

void	ft_error2(char *cmd, char *msg_err, int err)
{
	char	*tmp;

	tmp = ft_make_msg_err(cmd, msg_err);
	write (STDERR_FILENO, tmp, ft_strlen(tmp));
	free(tmp);
	g_inf->exit_code = err;
}
