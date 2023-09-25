/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:57:12 by jose              #+#    #+#             */
/*   Updated: 2023/09/24 11:58:04 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_pwd(t_ecmd *ecmd)
{
	char	*path;

	if (ecmd->argv[1] && ecmd->argv[1][0] == '-')
		ft_error(PWD_FAILED, "pwd", "option unknown");
	path = getcwd(NULL, 0);
	if (!path)
	{
		if (errno == ENOENT)
			ft_error(PWD_FAILED, "pwd", "getcwd : \
			cannot access parent directories");
		ft_error(PWD_FAILED, "pwd", strerror(errno));
	}
	ft_printf("%s\n", path);
	(ft_free_ginf(true), free(path), exit(EXIT_SUCCESS));
}
