/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/07/26 14:30:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line, char **envp)
{
	t_cmd	*cmd;

	if (ft_strchr(line, '|') && g_inf->interpret)
		cmd = ft_parsepipe(&line, envp);
	else
	{
		ft_peek(&line);
		cmd = ft_parseexec(&line, envp);
	}
	return (cmd);
}

t_cmd	*ft_parsepipe(char **ps, char **envp)
{
	t_cmd	*cmd;
	char	*tmp;

	tmp = ft_strchr(*ps, '|');
	if (tmp)
	{
		*tmp = '\0';
		tmp++;
		ft_peek(ps);
		cmd = ft_parseexec(ps, envp);
		ft_peek(&tmp);
		cmd = ft_pipecmd(cmd, ft_parsepipe(&tmp, envp));
	}
	else
		cmd = ft_parseexec(ps, envp);
	return (cmd);
}

t_cmd	*ft_parseredir(t_cmd *cmd, char **ps)
{
	char	*infile;

	infile = ft_strchr(*ps, '<');
	if (infile)
	{
		if (infile[1] == '<')
			ft_here_doc(&cmd, ps);
		else
			ft_infile_red(&cmd, ps);
	}
	ft_outfile_red(&cmd, ps);
	return (cmd);
}

t_cmd	*ft_parseexec(char **ps, char **envp)
{
	t_ecmd	*ecmd;
	t_cmd	*ret;

	ret = ft_execcmd(envp);
	ecmd = (t_ecmd *)ret;
	ret = ft_parseredir(ret, ps);
	ecmd->argv = ft_split(*ps, ' ');
	ft_getpath_n_builtin(ecmd);
	return (ret);
}
