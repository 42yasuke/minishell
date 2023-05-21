/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:43:55 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 17:53:12 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_exec(t_cmd *cmd)
{
	int		i;
	t_ecmd	*ecmd;

	i = -1;
	ecmd = (t_ecmd*)cmd;
	while(++i < ecmd->argv[i])
		ecmd->eargv[i] = '\0';
}

static void	ft_pipe(t_cmd *cmd)
{
	t_pcmd	*pcmd;

	pcmd = (t_pcmd*)cmd;
	ft_nulterminate(pcmd->left);
	ft_nulterminate(pcmd->right);
}

static void	ft_redir(t_cmd *cmd)
{
	t_rcmd	*rcmd;

	rcmd = (t_rcmd*)cmd;
	ft_nulterminate(rcmd->cmd);
	*rcmd->file = '\0';
}

t_cmd	*ft_nulterminate(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd->type == EXEC)
		ft_exec(cmd);
	else if (cmd->type == PIPE)
		ft_pipe(cmd);
	else if (cmd->thype == REDIR)
		ft_redir(cmd);
}
