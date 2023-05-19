/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:54:19 by jose              #+#    #+#             */
/*   Updated: 2023/05/19 19:32:36 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>

/*	node type's macros	*/
# define EXEC 1
# define PIPE 2
# define REDIR 3

# define MAXCHAR 100

/* error's macro	*/
# define BAD_PARAMETERS 0
# define MALLOC_FAILED 1

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**argv;
	char	**eargv;
}	t_ecmd;

typedef struct s_redircmd
{
	int				type;
	struct s_cmd	*cmd;
	char			*file;
	char			*efile;
	int				mode;
	int				fd;
}	t_rcmd;

typedef struct s_pipecmd
{
	int		type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_pcmd;

/*	error.c	*/
void	ft_error(int err, char *msg_err);
#endif