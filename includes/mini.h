/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:54:19 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 20:26:11 by jose             ###   ########.fr       */
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
# define CD_FAILED 2
#define FORK_FAILED 3
#define OPEN_FAILED 4
#define PIPE_FAILED 5
#define EXECVE_FAILED 6
#define SYNTAX_ERROR 7
#define BAD_REDIR 8

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**argv;
	char	**eargv;
	char	*path;
	char	**env;
	int		is_builtin;
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

/*	builtin.c	*/
int		ft_is_builtin(char *line);

/*	utils.c	*/
int		ft_is_whitespace(int c);
void	ft_cd_no_pipe(char *line);
pid_t	ft_fork(void);
int		ft_gettoken(char **ps, char *es, char **q, char **eq);

/*	utils2.c	*/
char	*ft_rm_ws_until_es(char *s, char *es);
int		ft_peek(char **ps, char *es, char *toks);

/*	exec.c	*/
void	ft_exec_manager(char *line);

/*	parse.c	*/
t_cmd	*ft_parsecmd(char *line);
t_cmd	*ft_parsepipe(char **ps, char *es);
t_cmd	*ft_parseredir(t_cmd *cmd, char **ps, char *es);
t_cmd	*ft_parseexec(char **ps, char *es);

/*	nulterminate.c	*/
t_cmd	*ft_nulterminate(t_cmd *cmd);

/*	init.c	*/
t_cmd	*ft_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*ft_execcmd(void);
t_cmd	*ft_redircmd(t_cmd *subcmd, char **file, int mode, int fd);

/*	path.c	*/
void	ft_getpath_n_builtin(t_ecmd *ecmd);

#endif