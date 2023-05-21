/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 18:41:33 by jose             ###   ########.fr       */
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

t_cmd	*ft_parseredir(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (ft_peek(ps, es, "<>"))
	{
		tok = ft_gettoken(ps, es, 0, 0);
		if (ft_gettoken(ps, es, &q, &eq)! = 'a')
			ft_error(BAD_REDIR, "missing file redirection");
		if (tok == '<')
			cmd = ft_redircmd(cmd, q, eq, O_RDONLY, STDIN_FILENO);
		else if (tok == '>')
			cmd = ft_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else
			cmd = ft_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
	}
	return (cmd);
}

t_cmd	*ft_parseexec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	int		argc;
	t_ecmd	*ecmd;
	t_cmd	*ret;

	ret = ft_execcmd();
	ecmd = (t_ecmd*)ret;
	argc = 0;
	ret = ft_parseredir(ret, ps, es);
	while (!ft_peek(ps, es, "|"))
	{
		tok = ft_gettoken(ps, es, &q, &eq);
		if (!tok)
			break ;
		if (tok == 'a')
			ft_error(SYNTAX_ERROR, "bad syntax");
		ecmd->argv[argc] = q;
		ecmd->eargv[argc] = eq;
		argc++;
		ret = ft_parseredir(ret, ps, es);
	}
	return (ecmd->argv[argc] = NULL, ecmd->eargv[argc] = NULL, ret);
}