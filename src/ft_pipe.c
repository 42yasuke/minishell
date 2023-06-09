/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:00:26 by jose              #+#    #+#             */
/*   Updated: 2023/06/01 02:20:34 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_pipe_suite(int **pi, int pid1, int pid2)
{
	int	sta;
	int	*p;

	p = *pi;
	sta = 0;
	(close(p[0]), close(p[1]));
	(waitpid(pid1, &sta, 0), waitpid(pid2, &sta, 0));
	if (WIFEXITED(sta))
		g_inf->exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_inf->exit_code = 128 + WTERMSIG(sta);
	sta = g_inf->exit_code;
	(free(p), ft_free_ginf(true), exit(sta));
}

void	ft_pipe(t_pcmd *pcmd)
{
	int		*p;
	pid_t	pid1;
	pid_t	pid2;

	p = malloc(sizeof(*p) * 2);
	if (!p)
		ft_error(MALLOC_FAILED, "p", strerror(errno));
	if (pipe(p) < 0)
		ft_error(PIPE_FAILED, "pipe", strerror(errno));
	pid1 = ft_fork();
	if (!pid1)
	{
		(close(p[0]), dup2(p[1], STDOUT_FILENO), close(p[1]));
		ft_runcmd(pcmd->left);
	}
	pid2 = ft_fork();
	if (!pid2)
	{
		(close(p[1]), dup2(p[0], STDIN_FILENO), close(p[0]));
		ft_runcmd(pcmd->right);
	}
	ft_pipe_suite(&p, pid1, pid2);
}
