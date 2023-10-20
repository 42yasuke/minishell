/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:54:37 by jose              #+#    #+#             */
/*   Updated: 2023/10/20 15:55:57 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_parsecmd(char *line, t_ginf *ginf)
{
	t_cmd	*cmd;

	if (ft_strchr(line, PIPE))
		cmd = ft_parsepipe(&line, ginf);
	else
	{
		ft_peek(&line);
		cmd = ft_parseexec(&line, ginf);
	}
	return (cmd);
}

t_cmd	*ft_parsepipe(char **ps, t_ginf *ginf)
{
	t_cmd	*cmd;
	char	*tmp;

	tmp = ft_strchr(*ps, PIPE);
	if (tmp)
	{
		*tmp = '\0';
		tmp++;
		ft_peek(ps);
		cmd = ft_parseexec(ps, ginf);
		ft_peek(&tmp);
		cmd = ft_pipecmd(cmd, ft_parsepipe(&tmp, ginf));
	}
	else
		cmd = ft_parseexec(ps, ginf);
	return (cmd);
}

t_cmd	*ft_parseredir(t_cmd *cmd, char **ps, t_ginf *ginf)
{
	if (ft_strchr(*ps, REDIN))
		ft_infile_red(&cmd, ps, ginf, ft_is_double_red(*ps, REDIN));
	ft_outfile_red(&cmd, ps, ginf);
	return (cmd);
}

t_cmd	*ft_parseexec(char **ps, t_ginf *ginf)
{
	t_ecmd	*ecmd;
	t_cmd	*ret;

	ret = ft_execcmd(ginf->env);
	if (!ginf->top)
		ginf->top = ret;
	ecmd = (t_ecmd *)ret;
	ret = ft_parseredir(ret, ps, ginf);
	ecmd->argv = ft_split(*ps, SPACE_TO_CUT);
	ft_getpath_n_builtin(ecmd);
	return (ret);
}
