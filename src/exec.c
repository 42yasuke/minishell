/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:12:55 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 20:49:49 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exec(t_ecmd *ecmd)
{
	if (ecmd->is_builtin)
		ft_built_it(ecmd);
	else
		execve(ecmd->path, ecmd->argv, ecmd->env);
	ft_error(EXECVE_FAILED, sterror(errno));
}

static void	ft_redir(t_rcmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode) < 0)
		ft_error(OPEN_FAILED, strerror(errno))
	ft_runcmd(rcmd->cmd);
}

static void ft_pipe(t_pcmd *pcmd)
{
	int		p[2];
	int		i;
	int		sta;
	pid_t	pid1;
	pid_t	pid2;

	i = 0;
	if (pipe(p) < 0)
		ft_error(PIPE_FAILED, sterror(errno));
	pid1 = ft_fork();
	if (!pid1)
	{
		(close(STDOUT_FILENO), dup(p[1]), close(p[0]), close(p[1]));
		ft_runcmd(pcmd->left);
	}
	pid2 = ft_fork();
	if (!pid2)
	{
		(close(STDIN_FILENO), dup(p[0]), close(p[0]), close(p[1]));
		ft_runcmd(pcmd->right);
	}
	(close(p[0]), close(p[1]));
	(waitpid(pid1, &sta, 0), waitpid(pid2, &sta, 0));
}

static void	ft_runcmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		ft_exec((t_ecmd*)cmd);
	else if(cmd->type == REDIR)
		ft_redir((t_rcmd*)cmd);
	else
		ft_pipe((t_pcmd*)cmd);
}

void	ft_exec_manager(char *line)
{
	int		status;
	pid_t	pid;

	pid = ft_fork();
	if (!pid)
		ft_runcmd(ft_parsecmd(line));
	waitpid(pid, &status, 0);
}