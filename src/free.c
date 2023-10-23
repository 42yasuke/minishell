/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:36:35 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 13:02:35 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_free_all(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

static void	ft_free_pcmd(t_cmd *cmd)
{
	t_pcmd	*pcmd;

	pcmd = (t_pcmd *)cmd;
	ft_free_cmd(pcmd->left);
	ft_free_cmd(pcmd->right);
	free(cmd);
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_ecmd	*ecmd;
	t_rcmd	*rcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_ecmd *)cmd;
		if (ecmd->path)
			if (!access(ecmd->path, X_OK) && ecmd->path != ecmd->argv[0])
				free(ecmd->path);
		ft_free_all(ecmd->argv);
		free(cmd);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_rcmd *)cmd;
		(ft_free_cmd(rcmd->cmd), free(rcmd->file), free(cmd));
	}
	else
		ft_free_pcmd(cmd);
}

void	ft_free_ginf(t_ginf *ginf, int free_all)
{
	if (ginf)
	{
		free(ginf->line);
		ginf->line = NULL;
		if (ginf->top)
			ft_free_cmd(ginf->top);
		if (free_all)
		{
			ft_free_all(ginf->env);
			ft_free_all(ginf->lst_env);
			free(ginf);
		}
	}
}
