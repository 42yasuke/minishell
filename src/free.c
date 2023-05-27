/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:36:35 by jose              #+#    #+#             */
/*   Updated: 2023/05/27 22:20:27 by jose             ###   ########.fr       */
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

void	ft_free_lst(t_lenv *lst_env)
{
	t_lenv	*tmp;

	while (lst_env)
	{
		tmp = lst_env->next;
		free(lst_env);
		lst_env = tmp;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_ecmd	*ecmd;
	t_rcmd	*rcmd;
	t_pcmd	*pcmd;

	if (cmd->type == EXEC)
	{
		ecmd = (t_ecmd*)cmd;
		if (ecmd->path)
			if (!access(ecmd->path, X_OK))
				free(ecmd->path);
		ft_free_all(ecmd->argv);
		free(cmd);
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (t_rcmd*)cmd;
		(ft_free_cmd(rcmd->cmd), free(cmd));
	}
	else
	{
		pcmd = (t_pcmd*)cmd;
		(ft_free_cmd(pcmd->left), ft_free_cmd(pcmd->right), free(cmd));
	}
}

void	ft_free_ginf(void)
{
	if(g_inf)
	{
		g_inf->exit_code = EXIT_FAILURE;
		free(g_inf->line);
		if (g_inf->top)
			ft_free_cmd(g_inf->top);
		ft_free_all(g_inf->env);
		free(g_inf);
		g_inf = NULL;
	}
}
