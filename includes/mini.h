/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:54:19 by jose              #+#    #+#             */
/*   Updated: 2023/10/25 11:28:52 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

/*	node type's macros	*/
# define EXEC 1
# define PIPE 7
# define REDIR 3
# define REDIN 1
# define REDOUT 2
# define DOLLAR 3
# define SQ 4
# define DQ 5
# define SPACE_TO_CUT 6
# define SQUOTE 39
# define DQUOTE 34

# define MAXARG 100
# define DI "/dev/stdin"
# define DO "/dev/stdout"
# define TCHAO "hasta la vista baby\n"
# define HERE_DOC 69
# define HD_SIGINT 70
# define MSG_ERR_GETCWD "getcwd : cannot access parent directories"
# define TABU 9

/* error's macro	*/
# define BAD_PARAMETERS 0
# define INVALID_OPTION 2
# define ERROR 1
# define ERROR2 2
# define EXECVE_FAILED 127
# define ENV_FAILED 125
# define PERMISSION_DENIED 126
# define OPEN_FAILED 13

/*	builtin's macro	*/
# define CD 1
# define PWD 2
# define ECHO 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

typedef struct s_cmd
{
	int					type;
}						t_cmd;

typedef struct s_execcmd
{
	int					type;
	char				**argv;
	char				*path;
	char				**env;
	int					is_builtin;
}						t_ecmd;

typedef struct s_redircmd
{
	int					type;
	struct s_cmd		*cmd;
	char				*file;
	int					mode;
	int					fd;
}						t_rcmd;

typedef struct s_pipecmd
{
	int					type;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_pcmd;

typedef struct s_ginf
{
	t_cmd				*top;
	char				*line;
	char				**env;
	char				**lst_env;
}						t_ginf;

typedef long long int	t_ll;

/*	ptr on execution tree	*/
extern int				g_exit_code;

/*	error.c	*/
void					ft_error(int err, char *cmd, char *msg, t_ginf *ginf);
void					ft_error2(int err, char *cmd, char *msg_err);

/*	ft_cd.c	*/
void					ft_cd_no_pipe(char *line, t_ginf *ginf);
void					ft_cd(t_ecmd *ecmd, t_ginf *ginf);

/*	ft_pwd.c	*/
void					ft_pwd(t_ecmd *ecmd, t_ginf *ginf);

/*	ft_exit.c	*/
void					ft_exit_no_pipe(char *line, t_ginf *ginf);
void					ft_exit(t_ecmd *t_ecmd, t_ginf *ginf);

/*	ft_exit_utils.c	*/
t_ll					ft_atoll(const char *nptr);
int						ft_compare_to_llmax_and_llmin(char *nbr);
int						ft_rest_of_div(t_ll dd, int d);

/*	ft_env.c	*/
void					ft_env(t_ecmd *ecmd, t_ginf *ginf);

/*	ft_unset.c */
void					ft_unset_no_pipe(char *line, t_ginf *ginf);
void					ft_unset(t_ecmd *ecmd, t_ginf *ginf);

/*	builtin.c	*/
int						ft_is_builtin(char *line);
void					ft_built_it(t_ecmd *ecmd, t_ginf *ginf);
int						ft_is_builtin_no_pipe(char *line);
void					ft_builtin_no_pipe(char *line, t_ginf *ginf);

/*	ft_export.c	*/
void					ft_export_no_pipe(char *line, t_ginf *ginf);
void					ft_export(t_ecmd *ecmd, t_ginf *ginf);

/*	ft_export_utils.c	*/
int						ft_analyse_export(char *str);

/*	ft_update_env.c	*/
void					ft_update_env_n_lst_env(char *str, t_ginf *ginf);
char					*ft_getenv(char *str, char **env);
char					*ft_get(char *str, char **env);

/*	ft_export_remove_space.c	*/
void					ft_remove_useless_space_in_export_cmd(char *line);

/*	node_env.c	*/
char					*ft_add_guigui_on_env_name(char *env_name);

/*	utils.c	*/
int						ft_is_whitespace(int c);
pid_t					ft_fork(t_ginf *ginf);
void					ft_peek(char **ps);
int						ft_nb_str(char **envp);
char					*ft_get_next_redir(char *line);

/*	exec.c	*/
void					ft_exec_manager(char *line, t_ginf *ginf);
void					ft_runcmd(t_cmd *cmd, t_ginf *ginf);

/*	parse.c	*/
t_cmd					*ft_parsecmd(char *line, t_ginf *ginf);
t_cmd					*ft_parsepipe(char **ps, t_ginf *ginf);
t_cmd					*ft_parseredir(t_cmd *cmd, char **ps, t_ginf *ginf);
t_cmd					*ft_parseexec(char **ps, t_ginf *ginf);

/*	init.c	*/
t_cmd					*ft_pipecmd(t_cmd *left, t_cmd *right);
t_cmd					*ft_execcmd(char **envp);
t_cmd					*ft_redircmd(t_cmd *subcmd, char *file, int mode,
							int fd);

/*	init_ginf.c	*/
void					ft_range_lst(char **lst_env);
void					ft_init_ginf(t_ginf *ginf, char **envp);
void					ft_reset_ginf(t_ginf *ginf);

/*	path.c	*/
void					ft_getpath_n_builtin(t_ecmd *ecmd);

/*	free.c	*/
void					ft_free_all(char **str);
void					ft_free_cmd(t_cmd *cmd);
void					ft_free_ginf(t_ginf *ginf, int free_all);

/*	sdquote.c	*/
int						ft_there_is_sdquote(char *line);
int						ft_get_quote(char *line);
int						ft_is_closed(char *line);
char					*ft_update_value(char *str, char **env);

/*	sdquote2.c	*/
char					*ft_sd_quote_manager(char *line, char **env);

/*	sdquote3.c	*/
char					*ft_find_n_replace_var(char *line, char **env);

/*	chr_var_denv.c	*/
char					*ft_strchr_var(char *line);

/*	replace.c	*/
int						ft_is_between_sdquote(char *line, char *c, char quote);
char					*ft_replace_special_chraracter(char *line, char **env);

/*	replace_utils.c	*/
void					ft_find_dollar_n_replace_it(char *line);

/*	ft_illtoa.c	*/
char					*ft_illtoa(t_ll n);

/*	redir.c	*/
int						ft_is_double_red(char *str, int red);
void					ft_infile_red(t_cmd **c, char **ps, t_ginf *gf, int hd);
void					ft_outfile_red(t_cmd **cmd, char **ps, t_ginf *ginf);

/*	redir_utils.c	*/
char					*ft_give_fn(char *st, int red, t_ginf *ginf);

/*	redir_utils2.c	*/
void					ft_make_me_point_on_cmd(char *str, int red);

/*	here_doc.c	*/
void					ft_here_doc(char *limiter, char **env);

/*	ft_echo.c	*/
void					ft_echo(t_ecmd *ecmd, t_ginf *ginf);

/*	ft_pipe.c	*/
void					ft_pipe(t_pcmd *pcmd, t_ginf *ginf);

/*	ft_verif_line.c	*/
int						ft_verif_line(char *line, int flag);

/*	ft_verif_cmd.c	*/
int						ft_verif_cmd(char *line);

/*	ft_signal.c	*/
void					ft_sigint_handler(int sig);
void					ft_sigquit_handler(int sig);
void					ft_ignore_these_signals(void);
void					ft_make_attention_these_signals(void);

#endif