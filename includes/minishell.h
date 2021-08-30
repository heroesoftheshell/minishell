/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:23:32 by hekang            #+#    #+#             */
/*   Updated: 2021/08/30 11:16:46 by hekang           ###   ########.fr       */
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
}				t_all;

typedef struct s_parsed_data
{
	char		*redirections;
	char		**cmd;
}				t_parse_data;

void			print_err_msg(int err_type, const char *str, char c);
void			print_system_err(const char *str);

char			*get_env_path(void);
char			*get_env_variable(const char *env_key);
void			set_env_variable(const char *env_key, const char *env_value);
void			run_cmd(char **chunk);
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
int				handle_redirection(const char *redirections);

#endif