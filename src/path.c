/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:23:18 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 11:32:05 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_verif_strcmd(char *cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '.' && cmd[i + 1] == '/')
			return (true);
		if (cmd[i] == '/' && cmd[i + 1] == '/')
			return (true);
	}
	return (false);
}

static char	*ft_loop(char *path_envp, char *cmd)
{
	int		i;
	char	**mypaths;
	char	*cmd_to_test;
	char	*ret;

	i = -1;
	cmd_to_test = ft_strjoin("/", cmd);
	mypaths = ft_split(path_envp, ':');
	while (mypaths[++i])
	{
		ret = ft_strjoin(mypaths[i], cmd_to_test);
		if (!access(ret, X_OK))
			break ;
		free(ret);
		ret = NULL;
	}
	return (free(cmd_to_test), ft_free_all(mypaths), ret);
}

static char	*ft_get_path(char *cmd, char **env)
{
	char	*path_envp;
	char	*ret;

	path_envp = ft_getenv("PATH", env);
	if (!path_envp || (cmd && (!access(cmd, X_OK))))
		return (cmd);
	ret = ft_loop(path_envp, cmd);
	if (!ret || ft_verif_strcmd(ret))
		(free(ret), ret = cmd);
	return (ret);
}

void	ft_getpath_n_builtin(t_ecmd *ecmd)
{
	ecmd->is_builtin = ft_is_builtin(ecmd->argv[0]);
	ecmd->path = ft_get_path(ecmd->argv[0], ecmd->env);
}
