/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:16:57 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:54:23 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_analyse_unset(char *str)
{
	if (*str == '-' && ft_strlen(str) > 1)
		return (ft_error2(INVALID_OPTION, "unset", "invalid option"), false);
	if (!ft_isalpha(*str) && *str != '_')
		return (ft_error2(ERROR, "unset", "invalid arg"), false);
	while (*str)
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (ft_error2(ERROR, "unset", "invalid arg"), false);
		str++;
	}
	return (true);
}

static void	ft_unset_with_args(char *str, char **envp)
{
	size_t	diff;
	size_t	diff2;
	int		i;
	int		take_next;

	take_next = false;
	i = -1;
	diff = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	while (envp[++i])
	{
		diff2 = ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '='));
		if (!ft_strncmp(str, envp[i], diff) && diff == diff2)
		{
			free(envp[i]);
			take_next = true;
		}
		if (take_next)
			envp[i] = envp[i + 1];
	}
}

void	ft_unset_no_pipe(char *line, t_ginf *ginf)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(line, SPACE_TO_CUT);
	g_exit_code = EXIT_SUCCESS;
	while (tmp[++i])
	{
		if (ft_analyse_unset(tmp[i]))
		{
			ft_unset_with_args(tmp[i], ginf->env);
			ft_unset_with_args(tmp[i], ginf->lst_env);
		}
	}
	ft_free_all(tmp);
}

void	ft_unset(t_ecmd *ecmd, t_ginf *ginf)
{
	int	i;

	i = 0;
	g_exit_code = EXIT_SUCCESS;
	if (ecmd->argv[1])
	{
		while (ecmd->argv[++i])
		{
			if (ft_analyse_unset(ecmd->argv[i]))
			{
				ft_unset_with_args(ecmd->argv[i], ecmd->env);
				ft_unset_with_args(ecmd->argv[i], ginf->lst_env);
			}
		}
	}
	i = g_exit_code;
	(ft_free_ginf(ginf, true), exit(i));
}
