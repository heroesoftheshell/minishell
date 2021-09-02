/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:23:32 by hekang            #+#    #+#             */
/*   Updated: 2021/09/02 10:53:42 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/history.h>
# include "readline.h"
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft.h"
# define SYNTAX_ERR_MSG_HEADER	"hosh: syntax error near unexpected token `"
# define SYNTAX_ERR_MSG_TAIL	"'"

enum	e_err_type
{
	SUCCESS,
	PIPE_SYNTAX_ERR,
	REDIRECT_SYNTAX_ERR,
	NEWLINE_SYNTAX_ERR,
	COMMAND_NOT_FOUND,
	QUOTE_EXIT_ERR,
	NO_SUCH_FILE_OR_DIR,
	MEM_ALLOC_ERR,
	FAIL
};

typedef struct s_all
{
	t_list		*envp;
	int			end_code;
	int			pipefd_backup[2];
	int			pid_list[BUFSIZ];
}				t_all;

typedef struct s_parsed_data
{
	char		*redirections;
	char		**cmd;
}				t_parse_data;

typedef struct s_str_join_pack
{
	char		*joined_str;
	char		*converted_str;
	char		*substr;
	char		*mid_str;
}				t_str_join_pack;

void			print_err_msg(int err_type, const char *str, char c);
void			print_system_err(const char *str);

char			*get_env_path(void);
char			*get_env_variable(const char *env_key);
void			set_env_variable(const char *env_key, char *env_value);
void			run_cmd(char **chunk, t_parse_data	*parsed_data);

void			ft_chdir(char **cmd);
void			ft_echo(char **cmd);
void			ft_pwd(void);

void			delete_split_strs(char **str);
void			delete_parsed_data(t_parse_data *p_data);
void			skip_space(const char **str);
int				is_redirect_sign(char c);
int				is_quote(char c);
int				is_hyphen(char c);
void			skip_quote(char const *s, size_t *str_idx, size_t *word_len);
char			**cmdline_split(char const *s, char *delimeter);
t_all			*all(void);

void			ft_env(void);
void			init_env(char **envp);
void			ft_export(char **cmd);
void			ft_unset(char **cmd);
int				validate_env_key(char *key, int unset_key);
void			ft_print_endcode(void);
void			ft_exit(char *exit_code);

char			**line_parse(const char *line);
t_parse_data	*cmd_chunk_parse(const char *chunk);
bool			is_include_filename_in_redirect(const char *str);
int				custom_rl_getc_fuction(FILE *stream);
int				handle_redirection(t_parse_data *parsed_data);
int				check_env_key(char *cmd);
int				validate_redirect_expression(const char **str, char start_c);
char			*conv_env_var(const char **src, int str_idx, int *char_idx, \
					bool is_inside_quote);
void			do_nothing(int signo);
void			catch_function_in(int signo);
void			catch_function(int signo);
void			init_signal(void);
void			init_pipefd_backup(int *pipefd_backup);
void			handle_input(char *input);
int				is_builtin(char *cmd);

void			first_pipe(t_parse_data *parsed_data, \
					int *pid_list, int *pipefd);
void			middle_pipe(t_parse_data *parsed_data, \
					int *pid_list, int *pipefd);
void			last_pipe(t_parse_data *parsed_data, \
					int *pid_list, int *pipefd);
void			none_pipe(t_parse_data *parsed_data);
void			handle_parsed_data(t_parse_data *parsed_data, \
					char *next_chunk, int *is_pipe, int *pipefd);
void			dup_std(int pipe, int pipe2);
void			close_both(int pipefd, int pipefd2);
char			*parse_quote_str(const char **src, char quote_char, \
					int str_idx, int *char_idx);
char			*substr_join(char *prev_str, char *substr);
char			*substr_join3(char *prefix, char *mid_str, \
					char *postfix);
int				divide_redirection(const char **splitted_data, \
					t_parse_data *parsed_data);
int				switch_str_to_handled_quote_str(char **sp_data, int si);
int				exec_heredoc(int fd, const char *delimiter, int stdin_fd);
void			convert_env_execption(const char *env_key, char **ret);

#endif