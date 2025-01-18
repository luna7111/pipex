/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   children_behaviours.c                          .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/18 16:27:58 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/18 16:32:10 by ldel-val          ``                     */
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
		dup2(fd[STDOUT], STDOUT);
		fd_in = open(infile, O_RDONLY);
		dup2(fd_in, STDIN);
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args[0], env), cmd_args, env);
		perror("start child error: ");
		exit(0);
	}
	close(fd[STDOUT]);
	return (fd[STDIN]);
}

int	middle_behaviour(int fd_in, char *command, char **env)
{
	char	**cmd_args;
	int		fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[STDIN]);
		dup2(fd_in, STDIN);
		dup2(fd[STDOUT], STDOUT);
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args[0], env), cmd_args, env);
		perror("middle child error: ");
		exit(0);
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
		cmd_args = ft_split(command, ' ');
		execve(command_path(cmd_args[0], env), cmd_args, env);
		perror("end child error: ");
	}
	close(fd_in);
}
