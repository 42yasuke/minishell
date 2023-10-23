/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:56:02 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:53:02 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_make_msg_err(char *cmd, char *msg_err)
{
	char	*tmp;
	char	*ret;

	ret = ft_strjoin("minishell : ", cmd);
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

void	ft_error(int err, char *cmd, char *msg, t_ginf *ginf)
{
	char	*str;

	str = NULL;
	g_exit_code = err;
	if (msg)
		str = ft_make_msg_err(cmd, msg);
	if (msg)
		write (STDERR_FILENO, str, ft_strlen(str));
	(free(str), ft_free_ginf(ginf, true));
	exit(g_exit_code);
}

void	ft_error2(int err, char *cmd, char *msg_err)
{
	char	*tmp;

	tmp = ft_make_msg_err(cmd, msg_err);
	write (STDERR_FILENO, tmp, ft_strlen(tmp));
	free(tmp);
	g_exit_code = err;
}
