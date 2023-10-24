/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:05:38 by jralph            #+#    #+#             */
/*   Updated: 2023/10/24 10:24:40 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_create_file_help(char *tmp_free, int red)
{
	char	*tmp;

	if (!tmp_free)
		ft_error(ERROR, "ft_create_file", "malloc failled", NULL);
	tmp = tmp_free;
	while (*tmp && (*tmp == red || *tmp == SPACE_TO_CUT))
		tmp++;
	ft_memmove(tmp_free, tmp, ft_strlen(tmp));
	tmp = tmp_free;
	while (*tmp && *tmp != SPACE_TO_CUT)
		tmp++;
	*tmp = '\0';
}
