/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:19:48 by jose              #+#    #+#             */
/*   Updated: 2023/10/01 19:05:24 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ft_error(ERROR, "malloc pipecmd", strerror(errno), NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*ft_execcmd(char **envp)
{
	t_ecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ft_error(ERROR, "malloc execcmd", strerror(errno), NULL);
	cmd->type = EXEC;
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->env = envp;
	return ((t_cmd *)cmd);
}

t_cmd	*ft_redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_rcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ft_error(ERROR, "malloc redircmd", strerror(errno), NULL);
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}
