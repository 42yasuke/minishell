/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:16:57 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 09:27:39 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_analyse_unset(char *str)
{
	if (*str == '-')
		return (ft_error2("unset", "invalid option", 2), false);
	if (!ft_isalpha(*str) && *str != '_')
		return (ft_error2("unset", "invalid arg", 1), false);
	while (*str)
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (ft_error2("unset", "invalid arg", 1), false);
		str++;
	}
	return (true);
}

static void	ft_unset_with_args(char *str, char **envp)
{
	size_t	diff;
	int		i;
	int		take_next;

	take_next = false;
	i = -1;
	while (envp[++i])
	{
		diff = ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '='));
		if (!ft_strncmp(str, envp[i], diff))
		{
			free(envp[i]);
			take_next = true;
		}
		if (take_next)
			envp[i] = envp[i + 1];
	}
}

void	ft_unset_no_pipe(char *line, char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(line, SPACE_TO_CUT);
	g_inf->exit_code = EXIT_SUCCESS;
	while (tmp[++i])
	{
		if (ft_analyse_unset(tmp[i]))
		{
			ft_unset_with_args(tmp[i], envp);
			ft_unset_with_args(tmp[i], g_inf->lst_env);
		}
	}
	ft_free_all(tmp);
}

void	ft_unset(t_ecmd *ecmd)
{
	int	i;

	i = 0;
	g_inf->exit_code = EXIT_SUCCESS;
	if (ecmd->argv[1])
	{
		while (ecmd->argv[++i])
		{
			if (ft_analyse_unset(ecmd->argv[i]))
			{
				ft_unset_with_args(ecmd->argv[i], ecmd->env);
				ft_unset_with_args(ecmd->argv[i], g_inf->lst_env);
			}
		}
	}
	i = g_inf->exit_code;
	(ft_free_ginf(true), exit(i));
}
