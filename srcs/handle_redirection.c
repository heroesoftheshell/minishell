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

int		exec_heredoc(int fd, const char *delimiter)
{
	char	*input;
	char	*str;
	char	*joined_str;

	joined_str = NULL;
	str = NULL;
	while (1)
	{
		input = readline("\033[1;4;34;47m>\033[0m ");
		if (ft_strcmp(input, delimiter) == 0)
		{
			write(fd, joined_str, ft_strlen(joined_str));
			write(fd, "\n", 1);
			break ;
		}
		else
		{
			if (joined_str)
			{
				str = ft_strjoin3(joined_str, "\n", input);
				free(joined_str);
				free(input);
				joined_str = str;
			}
			else
				joined_str = input;
		}
	}
	return (SUCCESS);
}

void		clear_temp(void)
{
	char **argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "-f";
	argv[1] = "./temp";
	argv[2] = NULL;
	if (fork() == 0)
		execve("/bin/rm", (char *const *)argv, NULL);
}

int		redirect_input(char *filename, bool is_heredoc_mode)
{
	int	fd;

	if (is_heredoc_mode)
	{
		fd = open("./temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		exec_heredoc(fd, filename);
		close(fd);
		fd = open("./temp", O_RDONLY);
	}
	else
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("\033[1;4;34;47mHOS >\033[0m ");
		return (FAIL);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if(is_heredoc_mode)
		clear_temp();
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

	if (redirections == NULL)
		return (FAIL);
	splitted_red = ft_split(redirections, ',');
	if (splitted_red == NULL)
		return (FAIL);
	idx = -1;
	while (splitted_red[++idx])
	{
		err_chk = classify_redirection_type(splitted_red[idx]);
		if (err_chk != SUCCESS)
			return (err_chk);
	}
	return (err_chk);
}