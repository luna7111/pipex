/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:37 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/11 13:38:59 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*command_path(char *name, char **env)
{
	//char	*file_path;
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
			return (dir[i]);//free_split needed!!!
		i++;
	}
	return (NULL);
}

int	main(int argn, char **argv, char **env)
{
	if (argn > 1)
		printf("%s\n", command_path(argv[1], env));
	return (0);
}
