/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:19:59 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 13:51:14 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_rm_ws_until_es(char *s, char *es)
{
	while (s < es && ft_is_whitespace(*s))
		s++;
	return (s);
}

int	ft_peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_is_whitespace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}
