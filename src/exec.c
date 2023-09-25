/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:12:55 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 20:10:34 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exec(t_ecmd *ecmd)
{
	if (ecmd->is_builtin)
		ft_built_it(ecmd);
	else if (!ecmd->argv[0])
		(ft_free_ginf(true), exit(EXIT_SUCCESS));
	else
		execve(ecmd->path, ecmd->argv, ecmd->env);
	if (!access(ecmd->path, F_OK) && access(ecmd->path, X_OK))
		ft_error(PERMISSION_DENIED, "execve", strerror(errno));
	ft_error(EXECVE_FAILED, "execve", strerror(errno));
}

static void	ft_redir(t_rcmd *rcmd)
{
	if (ft_strncmp(rcmd->file, DI, 11) && ft_strncmp(rcmd->file, DO, 12))
	{
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0644) < 0)
			ft_error(OPEN_FAILED, "execve", strerror(errno));
	}
	ft_runcmd(rcmd->cmd);
}

void	ft_runcmd(t_cmd *cmd)
{
	if (cmd->type == PIPE)
		ft_pipe((t_pcmd *)cmd);
	else if (cmd->type == REDIR)
		ft_redir((t_rcmd *)cmd);
	else if (cmd->type == EXEC)
		ft_exec((t_ecmd *)cmd);
}

void	ft_exec_manager(char *line, char **envp)
{
	int		sta;
	t_cmd	*cmd;
	pid_t	pid;

	sta = 0;
	pid = ft_fork();
	g_inf->is_child_process = true;
	if (!pid)
	{
		cmd = ft_parsecmd(line, envp);
		g_inf->top = cmd;
		if (g_inf->here_doc_quit)
			(ft_free_ginf(true), exit(130));
		ft_runcmd(cmd);
	}
	waitpid(pid, &sta, 0);
	g_inf->is_child_process = false;
	if (WIFEXITED(sta))
		g_inf->exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_inf->exit_code = 128 + WTERMSIG(sta);
}
