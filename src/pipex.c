/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:37 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/15 22:00:03 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*command_path(char *name, char **env)
{
	char	*file_path;
	char	**dir;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	env[i] += 5;
	dir = ft_split(env[i], ':');
	i = 0;
	while (dir[i])
	{
		dir[i] = ft_strappend(dir[i], "/", 1);
		dir[i] = ft_strappend(dir[i], name, ft_strlen(name));
		if (access(dir[i], X_OK) == 0)
		{
			file_path = ft_strdup(dir[i]);
			free_strarray(dir);
			return (file_path);
		}
		i++;
	}
	return (NULL);
}

int	start_behaviour(int fd_out, char *infile, char *command, char **env)
{
	int		infile_fd;
	char	**cmd_args;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, STDIN);
	dup2(fd_out, STDOUT);
	cmd_args = ft_split(command, ' ');
	execve(command_path(cmd_args[0], env), cmd_args, env);
	return (0);
}

int	middle_behaviour(int fd_in, int fd_out, char *command, char **env)
{
	char **cmd_args;

	dup2(fd_in, STDIN);
	dup2(fd_out, STDOUT);
	cmd_args = ft_split(command, ' ');
	execve(command_path(cmd_args[0], env), cmd_args, env);
	return (0);
}

int	end_behaviour(int fd_in, char *outfile, char *command, char **env)
{
	int		outfile_fd;
	char	**cmd_args;

	outfile_fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	dup2(outfile_fd, STDOUT);
	dup2(fd_in, STDIN);
	cmd_args = ft_split(command, ' ');
	execve(command_path(cmd_args[0], env), cmd_args, env);
	return (0);
}

#define FIRST_CMD 2
#define ANYPID -1

int	main(int argn, char **argv, char **env)
{
	int	current_pipe[2];
	int fd_in;
	int	i;
	int	wstatus;

	if (argn < 5)
		return (ft_printf("Error: Wrong number of arguments."));
	pipe(current_pipe);
	if (fork() == 0)
		start_behaviour(current_pipe[STDOUT], argv[1], argv[2], env);
	close(current_pipe[STDOUT]);
	i = 1;
	while (argn > 5)
	{
		fd_in = current_pipe[STDIN];
		pipe(current_pipe);
		if (fork() == 0)
			middle_behaviour(fd_in, current_pipe[STDOUT], argv[FIRST_CMD + i], env);
		close(fd_in);
		close(current_pipe[STDOUT]);
		i ++;
		argn --;
	}
	if (fork() == 0)
		end_behaviour(current_pipe[STDIN], argv[FIRST_CMD + i + 1], argv[FIRST_CMD + i], env);
	close(current_pipe[STDIN]);
	while (i--)
		waitpid(ANYPID, &wstatus, 0);
	return (0);
}
