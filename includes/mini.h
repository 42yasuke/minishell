/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:54:19 by jose              #+#    #+#             */
/*   Updated: 2023/05/23 02:39:30 by jose             ###   ########.fr       */
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
# include <fcntl.h>

/*	node type's macros	*/
# define EXEC 1
# define PIPE 2
# define REDIR 3

# define MAXCHAR 100

/* error's macro	*/
# define BAD_PARAMETERS 0
# define MALLOC_FAILED 1
# define CD_FAILED 2
# define FORK_FAILED 3
# define OPEN_FAILED 4
# define PIPE_FAILED 5
# define EXECVE_FAILED 6
# define SYNTAX_ERROR 7
# define BAD_REDIR 8
# define ECHO_FAILED 9
# define PWD_FAILED 10
# define EXPORT_FAILED 11
# define EXIT_FAILED 12

/*	builtin's macro	*/
# define CD 1
# define PWD 2
# define ECHO 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

typedef struct s_lenv
{
	char			*env_name;
	int				id;
	struct s_lenv	*next;
}	t_lenv;

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
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_pcmd;

/*	ptr on execution tree	*/
extern t_cmd	*g_cmd;

/*	error.c	*/
void	ft_error(int err, char *msg_err);

/*	builtin.c	*/
int		ft_is_builtin(char *line);
void	ft_built_it(t_cmd *ecmd);
void	ft_cd(t_ecmd *ecmd);
void	ft_echo(t_cmd *ecmd);
void	ft_pwd(t_ecmd *ecmd);

/*	builtin2.c	*/
void	ft_export(t_ecmd *ecmd);
void	ft_unset(t_ecmd *ecmd);
void	ft_env(t_ecmd *ecmd);
void	ft_exit(t_ecmd *t_ecmd);

/*	node_env.c	*/
t_lenv	*ft_get_node(t_lenv *lst_env, int id);
void	ft_init_lst(t_lenv *lst_env, char **envp);
t_lenv	*ft_add_nenv(t_lenv *lst_env, int i, char **envp, char *name);

/*	node_env2.c	*/
void	ft_export_with_args(t_ecmd *ecmd);
void	ft_unset_with_args(t_ecmd *ecmd);

/*	utils.c	*/
int		ft_is_whitespace(int c);
void	ft_cd_no_pipe(char *line);
pid_t	ft_fork(void);
int		ft_gettoken(char **ps, char *es, char **q, char **eq);

/*	utils2.c	*/
char	*ft_rm_ws_until_es(char *s, char *es);
int		ft_peek(char **ps, char *es, char *toks);
char	**ft_cpy_envp(char **envp);
int		ft_nb_str(char **envp);

/*	exec.c	*/
void	ft_exec_manager(char *line, char **envp);

/*	parse.c	*/
t_cmd	*ft_parsecmd(char *line, char **envp);
t_cmd	*ft_parsepipe(char **ps, char *es, char **envp);
t_cmd	*ft_parseredir(t_cmd *cmd, char **ps, char *es);
t_cmd	*ft_parseexec(char **ps, char *es, char **envp);

/*	nulterminate.c	*/
t_cmd	*ft_nulterminate(t_cmd *cmd);

/*	init.c	*/
t_cmd	*ft_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*ft_execcmd(char **envp);
t_cmd	*ft_redircmd(t_cmd *subcmd, char **file, int mode, int fd);

/*	path.c	*/
void	ft_getpath_n_builtin(t_ecmd *ecmd);

/*	free.c	*/
void	ft_free_all(char **str);
void	ft_free_lst(t_lenv *lst_env);
void	ft_free_cmd(t_cmd *cmd);

#endif