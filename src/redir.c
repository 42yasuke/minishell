/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:39:15 by jose              #+#    #+#             */
/*   Updated: 2023/09/25 19:03:21 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_infile_red(t_cmd **cmd, char **ps)
{
	char	*file;

	file = ft_give_me_file_name(*ps, REDIN);
	*cmd = ft_redircmd(*cmd, file, O_RDONLY, STDIN_FILENO);
	ft_make_me_point_on_cmd(*ps, REDIN);
}

void	ft_outfile_red(t_cmd **cmd, char **ps)
{
	char	*file;

	if (ft_strchr(*ps, REDOUT))
	{
		file = ft_give_me_file_name(*ps, REDOUT);
		if (ft_is_it_a_double_red(*ps, REDOUT))
			*cmd = ft_redircmd(*cmd, file, O_WRONLY | O_CREAT | \
			O_APPEND, STDOUT_FILENO);
		else
			*cmd = ft_redircmd(*cmd, file, O_WRONLY | O_CREAT | \
			O_TRUNC, STDOUT_FILENO);
		ft_make_me_point_on_cmd(*ps, REDOUT);
	}
}
