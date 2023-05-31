/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/05/31 19:18:58 by jose             ###   ########.fr       */
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

/*
char	*file
char	*start_red
char	*end_red*/

t_cmd	*ft_parseredir(t_cmd *cmd, char **ps) //maj
{
	char	*file;
	char	*infile;
	char	*outfile;
	//char	*tmp;

	infile = ft_strchr(*ps, '<');
	outfile = ft_strchr(*ps, '>');
	if (infile && g_inf->interpret)
	{
		infile++;
		ft_peek(&infile);
		file = infile;
		while (*infile && !ft_is_whitespace(*infile))
			infile++;
		if (*infile)
		{
			*infile = '\0';
			infile++;
		}
		if (**ps == '<') //test
			*ps = infile;
		else
		{
			infile = ft_strchr(*ps, '<');
			infile--;
			*infile = '\0';
		}
		cmd = ft_redircmd(cmd, file, O_RDONLY, STDIN_FILENO);
	}
	if (outfile && g_inf->interpret)
	{
		*outfile = '\0';
		outfile++;
		if (*outfile == '>')
		{
			outfile++;
			ft_peek(&outfile);
			file = outfile;
			while (*outfile && !ft_is_whitespace(*outfile))
				outfile++;
			if (*outfile)
				*outfile = '\0';
			cmd = ft_redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		}
		else
		{
			ft_peek(&outfile);
			file = outfile;
			while (*outfile && !ft_is_whitespace(*outfile))
				outfile++;
			if (*outfile)
				*outfile = '\0';
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
	//ft_peek(ps);
	ret = ft_parseredir(ret, ps);
	ecmd->argv = ft_split(*ps, ' ');
	ft_getpath_n_builtin(ecmd);
	return (ret);
}
