/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:44:51 by hekang            #+#    #+#             */
/*   Updated: 2021/05/18 20:38:47 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
typedef	enum	e_cmd_type
{
	NONE = 0,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	REDIRECT,
	PIPE,
	SEMICOL,
	NEWLINE
}				t_cmd_type;

typedef	struct	s_cmd_rowdata
{
	int			cmd_type;
	char		*sentence_rowdata;
	char		*redirection_block;
	int			cmd_end_type;
}				t_cmd_rowdata;

#endif
