/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   utils.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/18 16:35:19 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/27 16:51:44 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	perror_exit(char *error)
{
	perror(error);
	exit(-1);
}

void	print_error(char *error)
{
	ft_dprintf(STDERR, "%s\n", error);
	exit(-1);
}

char	*command_path(char **cmd_args, char **env)
{
	char	*file_path;
	char	**dir;
	int		i;

	if (ft_strchr(cmd_args[0], '/') && access(cmd_args[0], X_OK) == 0)
		return (cmd_args[0]);
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	env[i] += 5;
	dir = ft_split(env[i], ':');
	i = 0;
	while (dir[i])
	{
		dir[i] = ft_strappend(dir[i], "/", 1);
		dir[i] = ft_strappend(dir[i], cmd_args[0], ft_strlen(cmd_args[0]));
		if (access(dir[i], X_OK) == 0)
		{
			file_path = ft_strdup(dir[i]);
			free_strarray(dir);
			return (file_path);
		}
		i++;
	}
	free_strarray(dir);
	write(STDERR, cmd_args[0], ft_strlen(cmd_args[0]));
	write(STDERR, ": command not found\n", 20);
	free_strarray(cmd_args);
	exit(-1);
	return (NULL);
}
