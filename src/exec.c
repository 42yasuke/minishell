/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:12:55 by jose              #+#    #+#             */
/*   Updated: 2023/05/31 21:39:03 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exec(t_ecmd *ecmd)
{
	if (ecmd->is_builtin)
		ft_built_it(ecmd);
	else
		execve(ecmd->path, ecmd->argv, ecmd->env);
	ft_error(EXECVE_FAILED, "execve", strerror(errno));
}

static void	ft_redir(t_rcmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode , 0644) < 0)
		ft_error(OPEN_FAILED, "execve",strerror(errno));
	ft_runcmd(rcmd->cmd);
}

static void ft_pipe(t_pcmd *pcmd)
{
	int		p[2];
	int		sta;
	pid_t	pid1;
	pid_t	pid2;

	sta = 0;
	if (pipe(p) < 0)
		ft_error(PIPE_FAILED, "execve",strerror(errno));
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
	(close(p[0]), close(p[1]));
	(waitpid(pid1, &sta, 0), waitpid(pid2, &sta, 0));
	if (WIFEXITED(sta))
		g_inf->exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_inf->exit_code = 128 + WTERMSIG(sta);
	sta = g_inf->exit_code;
	(ft_free_ginf(true), exit(sta));
}

void	ft_runcmd(t_cmd *cmd)
{
	if (cmd->type == PIPE)
		ft_pipe((t_pcmd*)cmd);
	else if(cmd->type == REDIR)
		ft_redir((t_rcmd*)cmd);
	else if(cmd->type == EXEC)
		ft_exec((t_ecmd*)cmd);
}

void	ft_exec_manager(char *line, char **envp)
{
	int		sta;
	t_cmd	*cmd;
	pid_t	pid;

	sta = 0;
	pid = ft_fork();
	if (!pid)
	{
		cmd = ft_parsecmd(line, envp);
		g_inf->top = cmd;
		ft_runcmd(cmd);
	}
	waitpid(pid, &sta, 0);
	if (WIFEXITED(sta))
		g_inf->exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_inf->exit_code = 128 + WTERMSIG(sta);
}