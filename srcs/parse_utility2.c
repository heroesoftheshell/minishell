#include "minishell.h"

bool	is_include_filename_in_redirect(const char *str)
{
	if (is_redirect_sign(str[1]))
		return (str[2] != '\0');
	else
		return (str[1] != '\0');
}

void	delete_parsed_data(t_parse_data *p_data)
{
	int	idx;

	free(p_data->redirections);
	idx = -1;
	while ((p_data->cmd)[++idx])
	{
		free((p_data->cmd)[idx]);
	}
	free(p_data);
}