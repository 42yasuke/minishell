/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 12:24:01 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = line + ft_strlen(line);
	cmd = ft_parseline(&s, es);

}

t_cmd	*ft_parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = ft_parseexec(ps, es);
	if (peek(ps,es, "|"))
	{
		ft_gettoken(ps, es, 0, 0);
		cmd = ft_pipecmd(cmd, ft_parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*ft_parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = ft_parsepipe(ps, es);
	while ()
	{

	}
}