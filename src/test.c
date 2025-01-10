/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   test.c                                         .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/09 12:47:08 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/09 18:08:33 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*command_path(char *name, char **env)
{
	char **dir;
	char *path;
	char *file_path;
	int	i;

	i = 0;
	path = env[i];
	while (ft_strncmp(path, "PATH=", 5))
	{
		i++;
		path = env[i];
	}
	path += 5;
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		dir[i] = ft_strappend(dir[i], "/", 1);
		dir[i] = ft_strappend(dir[i], name, ft_strlen(name));
		if (access(dir[i], X_OK) == 0)
		{
			file_path = ft_strdup(dir[i]);
			free_split(dir);
			return (file_path);
		}
		i++;
	}
	return (NULL);
}

int	child1_behaviour(int fd[2], char **argv, char **env)
{
	int	fd_in;
	char **split_arg;

	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in, 0);
	dup2(fd[1], 1);
	split_arg = ft_split(argv[2], ' ');
	execve(command_path(split_arg[0], env), split_arg, env);
}

int	child2_behaviour(int fd[2], char **argv, char **env)
{
	int	fd_out;
	char **split_arg;

	fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 00644);
	dup2(fd_out, 1);
	dup2(fd[0], 0);
	split_arg = ft_split(argv[3], ' ');
	execve(command_path(split_arg[0], env), split_arg, env);
}

int	main(int argn, char **argv, char **env)
{
	int	fd[2];
	pipe(fd);

	if (argn != 5)
		exit(0);
	pid_t	child1 = fork();
	if (child1 == 0)
		child1_behaviour(fd, argv, env);
	close(fd[1]);
	pid_t	child2 = fork();
	if (child2 == 0)
		child2_behaviour(fd, argv, env);
	close(fd[0]);
}
