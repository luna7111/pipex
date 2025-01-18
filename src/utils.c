/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   utils.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/18 16:35:19 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/18 16:38:31 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	print_error(char *error)
{
	ft_printf("%s\n", error);
	exit(-1);
}

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
