/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:45:33 by jose              #+#    #+#             */
/*   Updated: 2023/05/30 13:24:33 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_update_value(char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(str) <= 1)
		return (str);
	if (!ft_strncmp(str, "$?", ft_strlen(str)))
	{
		tmp = str;
		str = ft_itoa(g_inf->exit_code);
	}
	else
	{
		tmp = str;
		str = ft_strdup(getenv(ft_strchr(str, '$') + 1));
	}
	return (free(tmp), str);
}

static char	*ft_bf_str(char **tab, int i)
{
	char	*bf;
	int		j;
	int		is_d;

	j = -1;
	is_d = false;
	bf = ft_strdup(tab[i]);
	if (!bf)
		ft_error(MALLOC_FAILED, "bf", "malloc failed");
	while (bf[++j])
	{
		if (bf[j] == '$')
		{
			if (!j)
				return (free(bf), NULL);
			is_d = true;
		}
		if (is_d)
			bf[j] = '\0';
	}
	return (bf);
}

static char	*ft_nenv_str(char **tab, int i, int *j2)
{
	char	*name_env;
	int		j;

	name_env = ft_strchr(tab[i], '$');
	name_env = ft_strdup(name_env);
	if (name_env[1] == '?')
		return (name_env[2] = '\0', *j2 = 2, name_env);
	if (!name_env)
		ft_error(MALLOC_FAILED, "name_env", "malloc failed");
	j = -1;
	*j2 = -1;
	while (name_env[++j])
	{
		if (*j2 == -1 && ft_is_whitespace(name_env[j]))
			*j2 = j;
		if (*j2 != -1 && j >= *j2)
			name_env[j] = '\0';
	}
	return (name_env);
}

static char	*ft_af_str(char **tab, int i, int j2)
{
	char	*af;

	af = ft_strchr(tab[i], '$');
	af = ft_strdup(af);
	if (j2 != -1)
		af = ft_memmove(af, af + j2, ft_strlen(af + j2) + 1);
	else
	{
		free(af);
		af = NULL;
	}
	return (af);
}

void	ft_update_tab(char **tab, int i)
{
	char	*name_env;
	char	*bf;
	char	*af;
	int		j2;
	char	*tmp;

	bf = ft_bf_str(tab, i);
	name_env = ft_nenv_str(tab, i, &j2);
	name_env = ft_update_value(name_env);
	af = ft_af_str(tab, i, j2);
	if (bf)
	{
		tmp = name_env;
		name_env = ft_strjoin(bf, name_env);
		(free(bf), free(tmp));
	}
	if (af)
	{
		tmp = name_env;
		name_env = ft_strjoin(name_env, af);
		(free(af), free(tmp));
	}
	tmp = tab[i];
	tab[i] = name_env;
	free(tmp);
}

char	*ft_merge_tab(char **tab, int spaced)
{
	char	*line;
	int		nbr_char;
	int		i;
	int		j;

	i = -1;
	nbr_char = 0;
	while (tab[++i])
		nbr_char += ft_strlen(tab[i]);
	line = malloc(sizeof(*line) * (nbr_char + i));
	if (!line)
		ft_error(MALLOC_FAILED, "line", "malloc failed");
	nbr_char = 0;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			line[nbr_char++] = tab[i][j];
		if (spaced && tab[i + 1])
			line[nbr_char++] = ' ';
	}
	return (line[nbr_char] = '\0', line);
}
