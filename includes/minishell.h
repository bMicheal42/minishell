/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <tmeizo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:45:49 by tmeizo            #+#    #+#             */
/*   Updated: 2021/03/12 14:46:35 by bmicheal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define ALL 2147483647
# define QUOTE 1
# define DQUOTE 2
# define DOLLAR 4
# define TOK_TEXT 'T'
# define TOK_SEMI ';'
# define TOK_PIPE '|'
# define TOK_REDI '<'
# define TOK_REDO '>'
# define TOK_REDA 'R'
# define RD_OUT '>'
# define RD_OUTA 'R'
# define RD_IN '<'
# define PIPE_IN 1
# define PIPE_OUT 2

typedef struct			s_token
{
	char				*data;
	char				type;
	struct s_token		*next;
}						t_token;

typedef struct			s_tok_parser
{
	char				*ret;
	int					i;
	int					j;
	int					qt;
}						t_tok_parser;

typedef struct			s_redirect
{
	char				type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_command
{
	char				*path;
	t_token				*token;
	char				**argv;
	char				**envp;
	t_redirect			*redirect;
	int					fd_in;
	int					fd_out;
	int					pipe_type;
	int					pipe[2];
	struct s_command	*next;
}						t_command;

typedef struct			s_shell
{
	int					i;
	int					j;
	t_token				*token;
	t_token				*head;
	t_command			*cmd;
	char				*input;
	char				*l_a;
}						t_shell;

extern int				g_exit_status;
extern pid_t			g_pid;
extern char				**g_envp;
extern t_shell			g_sh;

int						echo(char **argv, int fd);
int						cd(char **argv, int fd);
char					**export(char **argv, char **envp, int fd);
int						pwd(int fd);
char					**unset(char **argv, char **envp);
int						env(char **envp, int fd);
int						ft_exit(char **argv);
int						index_of(const char *s, char c);
char					**copy_split(char **s);
char					**free_split(char **s);
void					print_greeting(void);
int						cmp_name(char *a, char *b);
char					*ft_getenv(char *name, char **envp);
void					sanitize_tokens(t_token **token);
int						check_syntax(t_token *token);
void					clear_tokens(t_token **token);
void					clear_cmd(t_command **cmd);
int						is_builtin(t_command *cmd);
char					*parse_token(char *s, char **envp);
t_command				*parse_cmd(t_token *token, char **envp);
void					append_rd(t_redirect **rd, char type, char *filename);
void					clear_rd(t_redirect **rd);
char					**parse_argv(t_token *token, char **envp);
char					*find_in_path(char *name, char **envp);
int						process_rd(t_command *cmd);
int						process_pipe(t_command *cmd);
int						prepare_cmd(t_command *cmd);
int						execute(t_command *cmd);
int						exec_builtin(t_command *cmd);
void					ft_read_input(void);
void					ft_error_list(int error);
void					ft_skip_token(void);
void					ft_next_token(void);
int						ft_check_quotes(char *str, int num);
void					ft_full_skip_token(void);
void					ft_defined_data(void);
void					ft_sig_int(int a);
void					ft_sig_quit(int a);
char					*my_join(char *a, char *b);
void					token_util_other(t_tok_parser *p, char *s);
void					quotes_error(void);
char					**ft_sort_by_name(char **s, int lim);
char					*make_lower_string(t_command *cmd);
void					token_util_tild(t_tok_parser *p, char **envp, char *s);
int						forked(t_command *cmd, int status);
int						ft_notvalid_cmd(t_command *cmd);
void					ft_exec_argv(t_command *cmd, int status);
int						ft_exec_util1(t_command *cmd);
void					ft_exec_util2(void);
int						ft_exec_util3(t_command *cmd, int status);
void					ft_exec_util4(t_command *cmd);
void					ft_exec_util5(t_command *cmd);
void					exec_cleanup(t_command *cmd);
void					export_error(char *s);
void					print_sorted_env(char **sorted_envp,
						int fd, int i, int k);
int						env_len(char **envp, char *s, int name_len, int *repl);

#endif
