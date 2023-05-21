/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 14:33:37 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = line + ft_strlen(line);
	cmd = ft_parsepipe(&s, es);
	ft_peek(&s, es, "");
	if (s != es)
		ft_error(SYNTAX_ERROR, "syntax error");
	ft_nulterminate(cmd);
	return (cmd);
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

t_cmd	*ft_nulterminate(t_cmd *cmd)
{

}