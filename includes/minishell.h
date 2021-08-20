/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:23:32 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 12:19:21 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
// #include <readline/readline.h>
#include <readline/history.h>
#include "readline.h"
#include <string.h>
#include "libft.h"
# define CMDSTR_ECHO			"echo"
# define CMDSTR_CD				"cd"
# define CMDSTR_PWD				"pwd"
# define CMDSTR_EXPORT			"export"
# define CMDSTR_UNSET			"unset"
# define CMDSTR_ENV				"env"
# define CMDSTR_EXIT			"exit"
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
	FAIL
};

enum	e_cmd_type
{
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT
};

enum	e_parsed_data_order
{
	COMMAND,
	OPTION,
	ARG,
	REDIRECT
};

typedef struct	s_all
{
	t_list	*envp;
	t_list	**start_envp;
}				t_all;

void	print_err_msg(int err_type, const char *str, char c);
void	print_system_err(const char *str);

char	*get_env_path(void);
char	*get_env_variable(const char *env_key);
void	run_cmd(char *cmd);
void	ft_chdir(char **cmd);
void	ft_echo(char **cmd);
void	ft_pwd();

void	delete_split_strs(char **str);
void	skip_space(const char **str);
int		is_redirect_sign(char c);
int		is_quote(char c);
int		is_hyphen(char c);
void	skip_quote(char const *s, size_t *str_idx, size_t *word_len);
char	**cmdline_split(char const *s, char *delimeter);
t_all	*all(void);

void	ft_env(void);
void	init_env(char **envp);
void	ft_export(char **cmd);
int		ft_unset(char **cmd);
int		validate_env_key(char* key);


#endif