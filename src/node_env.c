/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:26:04 by jose              #+#    #+#             */
/*   Updated: 2023/10/01 17:37:15 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_add_guigui(char *env_name, char *ret, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_name[i])
	{
		ret[j] = env_name[i];
		i++;
		j++;
		if (env_name[i - 1] == '=' && !flag)
		{
			ret[j] = '"';
			flag = true;
			j++;
		}
	}
	ret[j] = '"';
	ret[j + 1] = '\0';
}

char	*ft_add_guigui_on_env_name(char *env_name)
{
	char	*ret;

	if (!ft_strchr(env_name, '='))
		return (ft_strdup(env_name));
	ret = malloc(sizeof(*ret) * (ft_strlen(env_name) + 2 + 1));
	if (!ret)
		ft_error(ERROR, "ret", "malloc failed", NULL);
	ft_add_guigui(env_name, ret, false);
	return (ret);
}
