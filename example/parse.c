/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:44:51 by hekang            #+#    #+#             */
/*   Updated: 2021/07/05 10:42:42 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parse.h"       
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//t_list			*init_list(void)
//{
//	t_list		*result;
//
//	result = (t_list *)ft_calloc(1, sizeof(t_list));
//	result->content = NULL;
//	result->next = NULL;
//	return (result);
//}


int				parse_cmd_type(char *string)
{
	int cnt;

	cnt = 0;
	while (string[cnt] == ' ')
		cnt++;

	return cnt;
}

void			skip_space(char *string)
{
	while (string)
	{
		if (*string != ' ')
			return ;
		string++;
	}
}

int				find_space(char *string)
{
	int			cnt;

	cnt = 0;
	while (string)
	{
		if (*string == ' ')
			return (cnt);
		string++;
		cnt++;
	}
	return cnt;
}

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void	*ft_calloc(size_t count, size_t size)
{
	void *str;

	if (!(str = (void *)malloc(count * size)))
	{
		write(1, "Error\n ** Malloc Error **\n", 26);
		exit(EXIT_SUCCESS);
	}
	if (str == 0)
		return (0);
	ft_memset(str, 0, count * size);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2 + 1);
	return (str);
}

int			*parse(char *string)
{
	//t_list		*cmd_rowdata;
	char		*redirection_block;
	char		*setence_rowdata;
	int			cmd_end_type;
	int			redirection_flag;
	char		*start;
	int			string_len;

	char *mstring;

	mstring = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	mstring = string;
	redirection_flag = 0;
//	cmd_rowdata = init_list();
	skip_space(mstring);
	if (*mstring == '>' || *mstring == '<')
	{
		start = mstring;
		if (*mstring == '>' && *mstring + 1 == '>')
			mstring++;
		mstring++;
		redirection_flag = 1;
	}
	if (redirection_flag)
	{
		skip_space(mstring);
		string_len = find_space(mstring);
		start + string_len = '\0';
		ft_strjoin(redirection_block, start);
	}
	printf("%s\n", redirection_block);
	return (0);
}

int main(void)
{
	parse("   abcd <   n asd ");
	return 0;
}
