#include "minishell.h"

int		redirect_ouput(char *filename, bool is_append_mode)
{
	int	fd;

	if (is_append_mode)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("\033[1;4;34;47mHOS >\033[0m ");
		return (FAIL);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int		redirect_input(char *filename, bool is_heredoc_mode)
{
	int	fd;

	if (is_heredoc_mode)
		fd = open(filename, O_RDONLY);
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("\033[1;4;34;47mHOS >\033[0m ");
		return (FAIL);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int		classify_redirection_type(char *str)
{
	int	idx;
	int	err_chk;

	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == '>')
		{
			if (str[idx + 1] == '>')
				err_chk = redirect_ouput(&(str[idx + 2]), true);
			else
				err_chk = redirect_ouput(&(str[idx + 1]), false);
			return (err_chk);
		}
		else if (str[idx] == '<')
		{
			if (str[idx + 1] == '<')
				err_chk = redirect_input(&(str[idx + 2]), true);
			else
				err_chk = redirect_input(&(str[idx + 1]), false);
			return (err_chk);
		}
	}
	return (FAIL);
}

int		handle_redirection(const char *redirections)
{
	char	**splitted_red;
	int		idx;
	int		err_chk;

	splitted_red = ft_split(redirections, ',');
	if (splitted_red == NULL)
		return (FAIL);
	idx = -1;
	while (splitted_red[++idx])
	{
		err_chk = classify_redirection_type(splitted_red[idx]);
	}
	return (err_chk);
}