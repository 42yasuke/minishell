/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 20:06:15 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line, char **envp)
{
	t_cmd	*cmd;

	if (ft_strchr(line, '|'))
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
	return (cmd);
}

t_cmd	*ft_parseredir(t_cmd *cmd, char **ps)
{
	char	*file;
	char	*tmp;

	tmp = ft_strchr(*ps, '<');
	if (tmp)
	{
		tmp++;
		ft_peek(&tmp);
		file = tmp;
		while (*tmp && !ft_is_whitespace(*tmp))
			tmp++;
		if (*tmp)
		{
			*tmp = '\0';
			tmp++;
		}
		*ps = tmp;
		cmd = ft_redircmd(cmd, file, O_RDONLY, STDIN_FILENO);
	}
	tmp = ft_strchr(*ps, '>');
	if (tmp)
	{
		*tmp = '\0';
		tmp++;
		if (*tmp == '>')
		{
			tmp++;
			ft_peek(&tmp);
			file = tmp;
			while (*tmp && !ft_is_whitespace(*tmp))
				tmp++;
			if (*tmp)
				*tmp = '\0';
			cmd = ft_redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		}
		else
		{
			ft_peek(&tmp);
			file = tmp;
			while (*tmp && !ft_is_whitespace(*tmp))
				tmp++;
			if (*tmp)
				*tmp = '\0';
			cmd = ft_redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		}
	}
	return (cmd);
}

t_cmd	*ft_parseexec(char **ps, char **envp)
{
	t_ecmd	*ecmd;
	t_cmd	*ret;

	ret = ft_execcmd(envp);
	ecmd = (t_ecmd*)ret;
	ret = ft_parseredir(ret, ps);
	ecmd->argv = ft_split(*ps, ' ');
	ft_getpath_n_builtin(ecmd);
	return (ret);
}
