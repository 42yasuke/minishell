/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:12:55 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:53:19 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exec(t_ecmd *ecmd, t_ginf *ginf)
{
	if (ecmd->is_builtin)
		ft_built_it(ecmd, ginf);
	else if (!ecmd->argv[0])
		(ft_free_ginf(ginf, true), exit(EXIT_SUCCESS));
	else
		execve(ecmd->path, ecmd->argv, ecmd->env);
	if (!access(ecmd->path, F_OK) && access(ecmd->path, X_OK))
		ft_error(PERMISSION_DENIED, "execve", strerror(errno), ginf);
	ft_error(EXECVE_FAILED, "execve", strerror(errno), ginf);
}

static void	ft_redir(t_rcmd *rcmd, t_ginf *ginf)
{
	if (!rcmd->file)
		(ft_free_ginf(ginf, true), exit(EXIT_FAILURE));
	if (ft_strncmp(rcmd->file, DI, 11) && ft_strncmp(rcmd->file, DO, 12))
	{
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0644) < 0)
			ft_error(ERROR, "open failed", strerror(errno), ginf);
	}
	ft_runcmd(rcmd->cmd, ginf);
}

void	ft_runcmd(t_cmd *cmd, t_ginf *ginf)
{
	if (cmd->type == PIPE)
		ft_pipe((t_pcmd *)cmd, ginf);
	else if (cmd->type == REDIR)
		ft_redir((t_rcmd *)cmd, ginf);
	else if (cmd->type == EXEC)
		ft_exec((t_ecmd *)cmd, ginf);
}

void	ft_exec_manager(char *line, t_ginf *ginf)
{
	int		sta;
	t_cmd	*cmd;
	pid_t	pid;

	sta = 0;
	pid = ft_fork(ginf);
	if (!pid)
	{
		cmd = ft_parsecmd(line, ginf);
		ginf->top = cmd;
		if (g_exit_code == HD_SIGINT)
			(ft_free_ginf(ginf, true), exit(130));
		ft_runcmd(cmd, ginf);
	}
	ft_ignore_these_signals();
	waitpid(pid, &sta, 0);
	ft_make_attention_these_signals();
	if (WIFEXITED(sta))
		g_exit_code = WEXITSTATUS(sta);
	else if (WIFSIGNALED(sta))
		g_exit_code = 128 + WTERMSIG(sta);
	if (g_exit_code == 131)
		write(STDOUT_FILENO, "Quit\n", 6);
}
