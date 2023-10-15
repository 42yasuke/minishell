/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:57:12 by jose              #+#    #+#             */
/*   Updated: 2023/10/15 13:54:50 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_pwd(t_ecmd *ecmd, t_ginf *ginf)
{
	char	*path;

	if (ecmd->argv[1] && ft_strlen(ecmd->argv[1]) > 1 \
	&& ecmd->argv[1][0] == '-')
		ft_error(ERROR2, "pwd", "option unknown", ginf);
	path = getcwd(NULL, 0);
	if (!path)
	{
		if (errno == ENOENT)
			ft_error(ERROR, "pwd", MSG_ERR_GETCWD, ginf);
		ft_error(ERROR, "pwd", strerror(errno), ginf);
	}
	ft_printf("%s\n", path);
	(ft_free_ginf(ginf, true), free(path), exit(EXIT_SUCCESS));
}
