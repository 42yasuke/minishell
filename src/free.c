/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:36:35 by jose              #+#    #+#             */
/*   Updated: 2023/09/30 20:53:38 by jose             ###   ########.fr       */
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

void	ft_free_cmd(t_cmd *cmd)
{
	t_ecmd	*ecmd;
	t_rcmd	*rcmd;
	t_pcmd	*pcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_ecmd *)cmd;
		if (ecmd->path)
			if (!access(ecmd->path, X_OK))
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
	{
		pcmd = (t_pcmd *)cmd;
		(ft_free_cmd(pcmd->left), ft_free_cmd(pcmd->right), free(cmd));
	}
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
