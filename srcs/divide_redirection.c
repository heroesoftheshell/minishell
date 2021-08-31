/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:33:24 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 16:46:45 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redirections_str(const char **splitted_data, \
			t_parse_data *parsed_data, int *sd_idx)
{
	if (is_include_filename_in_redirect(splitted_data[*sd_idx]))
		parsed_data->redirections = \
			substr_join3(parsed_data->redirections, ",", \
			ft_strdup(splitted_data[*sd_idx]));
	else
	{
		parsed_data->redirections = \
			substr_join3(parsed_data->redirections, ",", \
			ft_strjoin(splitted_data[*sd_idx], \
			splitted_data[*sd_idx + 1]));
		++(*sd_idx);
	}
}

int	divide_redirection(const char **splitted_data, \
				t_parse_data *parsed_data)
{
	int		sd_idx;
	int		cmd_count;

	if (parsed_data == NULL)
		return (FAIL);
	sd_idx = -1;
	cmd_count = 0;
	while (splitted_data[++sd_idx])
		cmd_count++;
	parsed_data->cmd = (char **)ft_calloc(cmd_count + 1, sizeof(char *));
	sd_idx = -1;
	cmd_count = -1;
	while (splitted_data[++sd_idx])
	{
		if (is_redirect_sign(splitted_data[sd_idx][0]))
			set_redirections_str(splitted_data, parsed_data, &sd_idx);
		else
			(parsed_data->cmd)[++cmd_count] = ft_strdup(splitted_data[sd_idx]);
	}
	(parsed_data->cmd)[++cmd_count] = NULL;
	return (SUCCESS);
}
