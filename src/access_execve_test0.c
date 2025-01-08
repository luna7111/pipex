/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   access_execve_test0.c                          .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/08 16:28:30 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/08 17:34:56 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	access_test(char *path)
{
	int	check;

	check = access(path, R_OK);
	printf("Read: %d\n", check);
	check = access(path, W_OK);
	printf("Write: %d\n", check);
	check = access(path, X_OK);
	printf("Execute: %d\n", check);
	return (check);
}

void	execute(int argn, char **args, char **env)
{
	execve(args[1], &args[1], env);
}

int	main(int argn, char **args, char **env)
{
	if (argn < 2)
		return (0);
	char *path = args[1];
	if (access_test(path) == 0)
		execute(argn, args, env);
	else
		printf("Cant open :(\n");
}
