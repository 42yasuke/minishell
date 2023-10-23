/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:18:36 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 14:04:39 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_peek2(char **ps)
{
	char	*s;

	s = *ps;
	if (*s && (ft_isalpha(*s) || *s == '_'))
	{
		while (*s && (ft_isalnum(*s) || *s == '_'))
			s++;
	}
	else if (*s && (*s == '?' || ft_isdigit(*s)))
		s++;
	*ps = s;
}

char	*ft_stick_str(char *bf_var, char *var_denv, char *af_var, char **env)
{
	char	*tmp;
	char	*tmp2;

	var_denv = ft_update_value(var_denv, env);
	tmp = ft_strjoin(bf_var, var_denv);
	if (!tmp)
		return (free(var_denv), free(bf_var), NULL);
	tmp2 = ft_strjoin(tmp, af_var);
	return (free(tmp), free(var_denv), free(bf_var), tmp2);
}

static void	ft_find_n_replace_var_if(char **tmp_chr, char **tmp)
{
	if (**tmp_chr)
	{
		*tmp = ft_strdup(*tmp_chr);
		**tmp_chr = '\0';
		*tmp_chr = *tmp;
	}
}

char	*ft_find_n_replace_var(char *line, char **env)
{
	char	*new_line;
	char	*tmp_chr;
	char	*var_denv;
	char	*tmp;

	tmp = NULL;
	new_line = ft_strdup(line);
	if (!new_line)
		ft_error(ERROR, "ft_strdup", "malloc_failled", NULL);
	tmp_chr = ft_strchr(new_line, DOLLAR);
	while (tmp_chr)
	{
		*tmp_chr = '\0';
		tmp_chr++;
		var_denv = tmp_chr;
		ft_peek2(&tmp_chr);
		ft_find_n_replace_var_if(&tmp_chr, &tmp);
		new_line = ft_stick_str(new_line, var_denv, tmp_chr, env);
		tmp_chr = ft_strchr(new_line, DOLLAR);
		free(tmp);
		tmp = NULL;
	}
	return (new_line);
}
