/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:38:16 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 23:41:31 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_cd(t_ecmd *ecmd)
{
	if (ecmd->argv[1])
	{
		if(ecmd->argv[2])
			ft_error(CD_FAILED, "cd : invalid argument");
		if (chdir(ecmd->argv[1]))
			ft_error(CD_FAILED, strerror(errno));
		else
			exit(EXIT_SUCCESS) ;
	}
	ft_error(CD_FAILED, "cd : only relative or absolu path");
}

void	ft_echo(t_ecmd *ecmd)
{
	int	is_n;

	is_n = false;
	if(ecmd->argv[1])
	{
		if(ecmd->argv[2])
			ft_error(ECHO_FAILED, "echo : invalid argument");
		if (ecmd->argv[1][0] == '-')
		{
			if (ft_strncmp(ecmd->argv[1], "-n", ft_strlen(ecmd->argv[1])))
				is_n = true;
			else
				ft_error(ECHO_FAILED, "echo : option unknown");
		}
		ft_printf("%s", ecmd->argv[1]);
	}
	if (!is_n)
		ft_printf("\n");
}

void	ft_pwd(t_ecmd *ecmd)
{
	char	*path;

	if(ecmd->argv[1])
	{
		if(ecmd->argv[2])
			ft_error(PWD_FAILED, "pwd : invalid argument");
		if (ecmd->argv[1][0] == '-')
			ft_error(PWD_FAILED, "pwd : option unknown");
	}
	path = getcwd(NULL, 0);
	if (!path)
		ft_error(PWD_FAILED, strerror(errno));
	ft_printf("%s\n", path);
	free(path);
	exit(EXIT_SUCCESS);
}

int	ft_is_builtin(char *line)
{
	if (!ft_strncmp(line, "cd", 2))
		return (CD);
	if (!ft_strncmp(line, "echo", 4))
		return (ECHO);
	if (!ft_strncmp(line, "pwd", 3))
		return (PWD);
	if (!ft_strncmp(line, "export", 6))
		return (EXPORT);
	if (!ft_strncmp(line, "unset", 5))
		return (UNSET);
	if (!ft_strncmp(line, "env", 3))
		return (ENV);
	if (!ft_strncmp(line, "exit", 4))
		return (EXIT);
	return (false);
}

void	ft_built_it(t_ecmd *ecmd)
{
	void	(*built_in[7])(t_ecmd*);

	built_in[0] = &ft_cd;
	built_in[1] = &ft_pwd;
	built_in[2] = &ft_echo;
	built_in[3] = &ft_export;
	built_in[4] = &ft_unset;
	built_in[5] = &ft_env;
	built_in[6] = &ft_exit;
	built_in[ft_is_builtin(ecmd->argv[0]) - 1](ecmd);
}
