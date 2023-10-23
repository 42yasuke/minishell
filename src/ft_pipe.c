/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:00:26 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:54:15 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_pipe_suite(int pid1, int pid2, t_ginf *ginf)
{
	int	sta;

	sta = 0;
	ft_ignore_these_signals();
	(waitpid(pid1, &sta, 0), waitpid(pid2, &sta, 0));
	ft_make_attention_these_signals();
	if (WIFEXITED(sta))
		g_exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_exit_code = 128 + WTERMSIG(sta);
	sta = g_exit_code;
	(ft_free_ginf(ginf, true), exit(sta));
}

void	ft_pipe(t_pcmd *pcmd, t_ginf *ginf)
{
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(p) < 0)
		ft_error(ERROR, "pipe", strerror(errno), ginf);
	pid1 = ft_fork(ginf);
	if (!pid1)
	{
		(close(p[0]), dup2(p[1], STDOUT_FILENO), close(p[1]));
		ft_runcmd(pcmd->left, ginf);
	}
	pid2 = ft_fork(ginf);
	if (!pid2)
	{
		(close(p[1]), dup2(p[0], STDIN_FILENO), close(p[0]));
		ft_runcmd(pcmd->right, ginf);
	}
	(close(p[0]), close(p[1]), ft_pipe_suite(pid1, pid2, ginf));
}
