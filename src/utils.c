/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:23:47 by jose              #+#    #+#             */
/*   Updated: 2023/05/24 12:34:08 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_whitespace(int c)
{
	int	i;

	i = 9;
	while (i < 14)
	{
		if (c == i)
			return (true);
		i++;
	}
	return (c == 32);
}

void	ft_cd_no_pipe(char *line)
{
	int	i;

	i = 2;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	if (!line[i])
	{
		if (chdir(line + 2))
			ft_error(CD_FAILED, strerror(errno));
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, strerror(errno));
	return (pid);
}

static void	ft_unset_no_pipe_with_args(char **var, char **envp)
{
	char	**new_env;
	size_t	diff;
	int		i;
	int		j;

	i = ft_nb_str(envp);
	new_env = malloc(sizeof(*new_env) * i);
	if (!new_env)
		ft_error(MALLOC_FAILED, "new_env : malloc failed");
	i = -1;
	j = 0;
	while (envp[++i])
	{
		diff = envp[i] + ft_strlen(envp[i]) - ft_strchr(envp[i], '=');
		if (!ft_strncmp(var[1], envp[i], diff))
			free(envp[i]);
		else
			new_env[j++] = envp[i];
	}
	new_env[j] = NULL;
	*envp = *new_env;
	free(new_env);
}

void	ft_unset_no_pipe(char *line, char **envp)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (tmp[1])
	{
		if (tmp[2])
			ft_error(UNSET_FAILED, "unset : invalid argument");
		if (tmp[1][0] == '-')
			ft_error(UNSET_FAILED, "unset : invalid option");
		else
			ft_unset_no_pipe_with_args(tmp, envp);
	}
	ft_free_all(tmp);
}
