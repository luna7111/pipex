/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   children_behaviours.c                          .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/18 16:27:58 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/29 19:32:19 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	start_behaviour(char *infile, char *command, char **env)
{
	int		fd_in;
	char	**cmd_args;
	int		fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		fd_in = open(infile, O_RDONLY);
		dup2(fd_in, STDIN);
		dup2(fd[STDOUT], STDOUT);
		close(fd[STDOUT]);
		close(fd[STDIN]);
		if (fd_in == -1)
			print_error("Cannot open file for reading.");
		close(fd_in);
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args, env), cmd_args, env);
		free_strarray(cmd_args);
		perror_exit("");
	}
	close(fd[STDOUT]);
	return (fd[STDIN]);
}

int	here_doc_behaviour(char *delimiter)
{
	int		fd[2];
	char	*read_line;

	pipe(fd);
	if (fork() == 0)
	{
		read_line = malloc(close(fd[STDIN]));
		while (1)
		{
			free(read_line);
			ft_printf("pipe heredoc>");
			read_line = get_next_line(STDIN, GNL_STD);
			if (!ft_strncmp(read_line, delimiter, ft_strlen(read_line) - 1))
				if (ft_strlen(read_line) - 1 == ft_strlen(delimiter))
					break ;
			write(fd[STDOUT], read_line, ft_strlen(read_line));
		}
		free(read_line);
		get_next_line(STDIN, GNL_FREE);
		close(fd[STDOUT]);
		exit(0);
	}
	close(fd[STDOUT]);
	waitpid(ANYPID, NULL, 0);
	return (fd[STDIN]);
}

int	middle_behaviour(int fd_in, char *command, char **env)
{
	char	**cmd_args;
	int		fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd_in, STDIN);
		dup2(fd[STDOUT], STDOUT);
		close(fd[STDIN]);
		close(fd[STDOUT]);
		close(fd_in);
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args, env), cmd_args, env);
		free_strarray(cmd_args);
		perror_exit("");
	}
	close(fd_in);
	close(fd[STDOUT]);
	return (fd[STDIN]);
}

void	end_behaviour(int fd_in, char *outfile, char *command, char **env)
{
	char	**cmd_args;
	int		fd_out;

	if (fork() == 0)
	{
		fd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 00644);
		dup2(fd_out, STDOUT);
		dup2(fd_in, STDIN);
		close(fd_out);
		if (fd_in == -1)
			print_error("Cannot open file for writing");
		close(fd_in);
		if (access(outfile, W_OK) != 0)
			print_error("Cannot open file for writing");
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args, env), cmd_args, env);
		free_strarray(cmd_args);
		perror_exit("");
	}
	close(fd_in);
}

void	append_behaviour(int fd_in, char *outfile, char *command, char **env)
{
	char	**cmd_args;
	int		fd_out;

	if (fork() == 0)
	{
		fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 00644);
		dup2(fd_out, STDOUT);
		dup2(fd_in, STDIN);
		close(fd_out);
		if (fd_in == -1)
			print_error("Cannot open file for writing");
		close(fd_in);
		if (access(outfile, W_OK) != 0)
			print_error("Cannot open file for writing");
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args, env), cmd_args, env);
		free_strarray(cmd_args);
		perror_exit("");
	}
	close(fd_in);
}
