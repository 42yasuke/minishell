/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/09/25 16:48:49 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line, char **envp)
{
	t_cmd	*cmd;

	if (ft_strchr(line, PIPE))
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

	tmp = ft_strchr(*ps, PIPE);
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
	if (ft_strchr(*ps, REDIN))
	{
		if (ft_is_it_a_double_red(*ps, REDIN))
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
	ecmd->argv = ft_split(*ps, SPACE_TO_CUT);
	ft_getpath_n_builtin(ecmd);
	return (ret);
}
