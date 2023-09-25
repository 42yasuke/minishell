/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_remove_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:42:37 by jose              #+#    #+#             */
/*   Updated: 2023/09/19 19:31:51 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_remove_useless_space_in_quote(char *q_with_space, int q)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = q_with_space;
	while (tmp[i] != q)
	{
		if (tmp[i] != ' ')
			i++;
		else
		{
			if (tmp[i + 1] == ' ' || tmp[i - 1] == q || tmp[i + 1] == q)
				ft_memmove(tmp + i, tmp + i + 1, ft_strlen(tmp + i + 1));
			else
				i++;
		}
	}
}

static void	ft_find_export_quote(char *cmd_export)
{
	char	*tmp;

	tmp = ft_strchr(cmd_export, SQ);
	while (tmp)
	{
		if (*(tmp - 1) == '=' && ft_strchr(tmp + 1, SQ))
		{
			if ((ft_isalnum(*(tmp - 2)) || *(tmp - 2) == '_'))
				ft_remove_useless_space_in_quote(tmp, SQ);
		}
		tmp = ft_strchr(tmp + 1, SQ);
	}
	tmp = ft_strchr(cmd_export, DQ);
	while (tmp)
	{
		if (*(tmp - 1) == '=' && ft_strchr(tmp + 1, DQ))
		{
			if ((ft_isalnum(*(tmp - 2)) || *(tmp - 2) == '_'))
				ft_remove_useless_space_in_quote(tmp, DQ);
		}
		tmp = ft_strchr(tmp + 1, DQ);
	}
}

void	ft_remove_useless_space_in_export_cmd(char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "export", 6);
	while (tmp)
	{
		if (*(tmp + 6) == SPACE_TO_CUT)
			ft_find_export_quote(tmp);
		tmp = ft_strnstr(tmp + 1, "export", 6);
	}
}
