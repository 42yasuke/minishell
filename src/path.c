/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:23:18 by jose              #+#    #+#             */
/*   Updated: 2023/09/19 20:48:02 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_get_path(char *cmd)
{
	char	*path_envp;
	char	**mypaths;
	int		i;
	char	*ret;
	char	*cmd_to_test;

	path_envp = ft_getenv("PATH");
	if (!path_envp)
		return (cmd);
	mypaths = ft_split(path_envp, ':');
	i = 0;
	ret = cmd;
	if (ret && !access(ret, X_OK))
		return (ft_free_all(mypaths), ret);
	cmd_to_test = ft_strjoin("/", cmd);
	while (mypaths[++i])
	{
		ret = ft_strjoin(mypaths[i], cmd_to_test);
		if (!access(ret, X_OK))
			break ;
		free(ret);
		ret = cmd;
	}
	return (free(cmd_to_test), ft_free_all(mypaths), ret);
}

void	ft_getpath_n_builtin(t_ecmd *ecmd)
{
	ecmd->is_builtin = ft_is_builtin(ecmd->argv[0]);
	ecmd->path = ft_get_path(ecmd->argv[0]);
}
