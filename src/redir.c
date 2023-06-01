/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:39:15 by jose              #+#    #+#             */
/*   Updated: 2023/06/01 01:21:44 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_infile_red_else(char **ps)
{
	char	*infile;

	infile = ft_strchr(*ps, '<');
	infile--;
	*infile = '\0';
}

void	ft_infile_red(t_cmd **cmd, char **ps)
{
	char	*file;
	char	*infile;

	infile = ft_strchr(*ps, '<');
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
		if (**ps == '<')
			*ps = infile;
		else
			ft_infile_red_else(ps);
		*cmd = ft_redircmd(*cmd, file, O_RDONLY, STDIN_FILENO);
	}
}

static void	ft_outfile_red_else(t_cmd **cmd, char **outf)
{
	char	*file;
	char	*outfile;

	outfile = *outf;
	ft_peek(&outfile);
	file = outfile;
	while (*outfile && !ft_is_whitespace(*outfile))
		outfile++;
	if (*outfile)
		*outfile = '\0';
	*cmd = ft_redircmd(*cmd, file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
}

void	ft_outfile_red(t_cmd **cmd, char **ps)
{
	char	*file;
	char	*outfile;

	outfile = ft_strchr(*ps, '>');
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
			*cmd = ft_redircmd(*cmd, file, O_WRONLY | \
			O_CREAT | O_APPEND, STDOUT_FILENO);
		}
		else
			ft_outfile_red_else(cmd, &outfile);
	}
}
