/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_var_denv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:07:42 by jose              #+#    #+#             */
/*   Updated: 2023/09/03 08:02:52 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strchr_var(char *line)
{
	char	*var_denv;

	var_denv = ft_strchr(line, DOLLAR);
	while (var_denv)
	{
		var_denv++;
		if (*var_denv && (ft_isalnum(*var_denv) || *var_denv == '?'))
			return (var_denv--, ft_strchr(var_denv, DOLLAR));
		var_denv = ft_strchr(var_denv, DOLLAR);
	}
	return (NULL);
}
