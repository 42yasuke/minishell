/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:54:56 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 11:57:45 by jose             ###   ########.fr       */
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
		if (!ft_strncmp(str, env[i], diff))
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
		env[id_old_pwd] = ft_strjoin("OLDPWD=", ft_getenv("PWD"));
	else
		env[id_old_pwd] = ft_add_guigui_on_env_name(ft_get("OLDPWD"));
	free(tmp);
	id_pwd = ft_getenv_id(env, "PWD");
	tmp = env[id_pwd];
	if (is_env)
		env[id_pwd] = ft_strjoin("PWD=", path);
	else
		env[id_pwd] = ft_add_guigui_on_env_name(ft_get("PWD"));
	free(tmp);
}

static void	ft_cd_verif_if_parents_dir_exists(void)
{
	char	*path;

	errno = 0;
	path = getcwd(NULL, 0);
	if (errno == ENOENT)
		ft_error2("cd", "cannot access parent directories", 1);
	else
		g_inf->exit_code = EXIT_SUCCESS;
	if (path)
	{
		ft_update_pwd_n_olpwd_vars(g_inf->env, path, true);
		ft_update_pwd_n_olpwd_vars(g_inf->lst_env, path, false);
	}
	free(path);
}

void	ft_cd_no_pipe(char *line)
{
	char	**tmp;

	tmp = ft_split(line, SPACE_TO_CUT);
	if (tmp[1])
	{
		if (tmp[1][0] == '-')
			ft_error2("cd", "invalid option", 2);
		else if (tmp[2])
			ft_error2("cd", "too many arguments", 1);
		else
		{
			if (chdir(tmp[1]))
				ft_error2("cd", "No such file or directory", 1);
			else
				ft_cd_verif_if_parents_dir_exists();
		}
	}
	else
		ft_error2("cd", "only relative or absolu path", 1);
	ft_free_all(tmp);
}

void	ft_cd(t_ecmd *ecmd)
{
	int	i;

	if (ecmd->argv[1])
	{
		if (ecmd->argv[1][0] == '-')
			ft_error(12, "cd", "invalid option");
		if (ecmd->argv[2])
			ft_error(CD_FAILED, "cd", "too many arguments");
		if (chdir(ecmd->argv[1]))
			ft_error(CD_FAILED, "cd", strerror(errno));
		else
		{
			ft_cd_verif_if_parents_dir_exists();
			i = g_inf->exit_code;
			(ft_free_ginf(true), exit(i));
		}
	}
	ft_error(CD_FAILED, "cd", "only relative or absolu path");
}
