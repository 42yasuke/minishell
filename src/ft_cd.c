/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:54:56 by jose              #+#    #+#             */
/*   Updated: 2023/10/16 12:21:10 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_getenv_id(char **env, char *str)
{
	int		i;
	size_t	diff;

	i = -1;
	while (env[++i])
	{
		diff = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!ft_strncmp(str, env[i], diff) && diff == ft_strlen(str))
			return (i);
	}
	env[i] = ft_strjoin(str, "=");
	return (i);
}

static void	ft_update_pwd_n_olpwd_vars(char **env, char *path, int is_env)
{
	int		id_old_pwd;
	int		id_pwd;
	char	*tmp;

	id_old_pwd = ft_getenv_id(env, "OLDPWD");
	tmp = env[id_old_pwd];
	if (is_env)
		env[id_old_pwd] = ft_strjoin("OLDPWD=", ft_getenv("PWD", env));
	else
		env[id_old_pwd] = ft_add_guigui_on_env_name(ft_get("OLDPWD", env));
	free(tmp);
	id_pwd = ft_getenv_id(env, "PWD");
	tmp = env[id_pwd];
	if (is_env)
		env[id_pwd] = ft_strjoin("PWD=", path);
	else
		env[id_pwd] = ft_add_guigui_on_env_name(ft_get("PWD", env));
	free(tmp);
}

static void	ft_cd_verif_if_parents_dir_exists(t_ginf *ginf)
{
	char	*path;

	errno = 0;
	path = getcwd(NULL, 0);
	if (errno == ENOENT)
		ft_error2(ERROR, "cd", "cannot access parent directories");
	else
		g_exit_code = EXIT_SUCCESS;
	if (path)
	{
		ft_update_pwd_n_olpwd_vars(ginf->env, path, true);
		ft_update_pwd_n_olpwd_vars(ginf->lst_env, path, false);
	}
	free(path);
}

void	ft_cd_no_pipe(char *line, t_ginf *ginf)
{
	char	**tmp;

	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		if (tmp[1][0] == '-' && ft_strlen(tmp[1]) > 1)
			ft_error2(INVALID_OPTION, "cd", "invalid option");
		else if (tmp[2])
			ft_error2(ERROR, "cd", "too many arguments");
		else
		{
			if (chdir(tmp[1]))
				ft_error2(ERROR, "cd", "No such file or directory");
			else
				ft_cd_verif_if_parents_dir_exists(ginf);
		}
	}
	else
		ft_error2(ERROR, "cd", "only relative or absolu path");
	ft_free_all(tmp);
}

void	ft_cd(t_ecmd *ecmd, t_ginf *ginf)
{
	int	i;

	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-' && ft_strlen(ecmd->argv[1]) > 1)
			ft_error(INVALID_OPTION, "cd", "invalid option", ginf);
		if (ecmd->argv[2])
			ft_error(ERROR, "cd", "too many arguments", ginf);
		if (chdir(ecmd->argv[1]))
			ft_error(ERROR, "cd", strerror(errno), ginf);
		else
		{
			ft_cd_verif_if_parents_dir_exists(ginf);
			i = g_exit_code;
			(ft_free_ginf(ginf, true), exit(i));
		}
	}
	ft_error(ERROR, "cd", "only relative or absolu path", ginf);
}
