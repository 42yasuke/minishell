/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:39:15 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:15:31 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_double_red(char *str, int red)
{
	char	*tmp;
	char	*last_tmp;

	last_tmp = NULL;
	tmp = ft_strchr(str, red);
	while (tmp)
	{
		last_tmp = tmp;
		tmp = ft_strchr(tmp + 1, red);
	}
	if (last_tmp != str && *(last_tmp - 1) == red)
		return (true);
	return (false);
}

void	ft_infile_red(t_cmd **cmd, char **ps, t_ginf *ginf, int hd)
{
	char	*file;

	file = ft_give_fn(*ps, REDIN, ginf);
	if (hd)
	{
		free(file);
		file = ft_strdup("/tmp/.h_d");
		if (!file)
			ft_error(ERROR, "ft_strdup", "malloc failled", NULL);
	}
	*cmd = ft_redircmd(*cmd, file, O_RDONLY, STDIN_FILENO);
	ft_make_me_point_on_cmd(*ps, REDIN);
}

void	ft_outfile_red(t_cmd **cmd, char **ps, t_ginf *ginf)
{
	char	*file;

	if (ft_strchr(*ps, REDOUT))
	{
		file = ft_give_fn(*ps, REDOUT, ginf);
		if (ft_is_double_red(*ps, REDOUT))
			*cmd = ft_redircmd(*cmd, file, O_WRONLY | O_CREAT | \
			O_APPEND, STDOUT_FILENO);
		else
			*cmd = ft_redircmd(*cmd, file, O_WRONLY | O_CREAT | \
			O_TRUNC, STDOUT_FILENO);
		ft_make_me_point_on_cmd(*ps, REDOUT);
	}
}
