/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:38:16 by jose              #+#    #+#             */
/*   Updated: 2023/09/30 20:36:28 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_builtin_no_pipe(char *line)
{
	int	is_builtin;

	is_builtin = (!ft_strncmp(line, "cd", 2) || !ft_strncmp(line, "export", 6));
	if (!is_builtin)
	{
		is_builtin = !ft_strncmp(line, "unset", 5);
		if (!is_builtin)
			is_builtin = !ft_strncmp(line, "exit", 4);
	}
	return (is_builtin);
}

void	ft_builtin_no_pipe(char *line, t_ginf *ginf)
{
	if (!ft_strchr(line, PIPE))
	{
		if (!ft_strncmp(line, "cd", 2))
			ft_cd_no_pipe(line, ginf);
		else if (!ft_strncmp(line, "export", 6))
			ft_export_no_pipe(line, ginf);
		else if (!ft_strncmp(line, "unset", 5))
			ft_unset_no_pipe(line, ginf);
		else if (!ft_strncmp(line, "exit", 4))
			ft_exit_no_pipe(line, ginf);
	}
}

static int	ft_is_builtin2(char *line, char *builtin, int ret)
{
	int	diff;

	diff = ft_strncmp(line, builtin, ft_strlen(line));
	if (!diff || diff == SPACE_TO_CUT || diff == ' ')
		return (ret);
	return (false);
}

int	ft_is_builtin(char *line)
{
	if (!ft_strncmp(line, "cd", 2))
		return (ft_is_builtin2(line, "cd", CD));
	if (!ft_strncmp(line, "echo", 4))
		return (ft_is_builtin2(line, "echo", ECHO));
	if (!ft_strncmp(line, "pwd", 3))
		return (ft_is_builtin2(line, "pwd", PWD));
	if (!ft_strncmp(line, "export", 6))
		return (ft_is_builtin2(line, "export", EXPORT));
	if (!ft_strncmp(line, "unset", 5))
		return (ft_is_builtin2(line, "unset", UNSET));
	if (!ft_strncmp(line, "env", 3))
		return (ft_is_builtin2(line, "env", ENV));
	if (!ft_strncmp(line, "exit", 4))
		return (ft_is_builtin2(line, "exit", EXIT));
	return (false);
}

void	ft_built_it(t_ecmd *ecmd, t_ginf *ginf)
{
	void	(*built_in[7])(t_ecmd *, t_ginf *);

	built_in[0] = &ft_cd;
	built_in[1] = &ft_pwd;
	built_in[2] = &ft_echo;
	built_in[3] = &ft_export;
	built_in[4] = &ft_unset;
	built_in[5] = &ft_env;
	built_in[6] = &ft_exit;
	built_in[ft_is_builtin(ecmd->argv[0]) - 1](ecmd, ginf);
}
