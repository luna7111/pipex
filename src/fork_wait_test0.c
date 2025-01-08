/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/08 03:29:46 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/08 16:08:18 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void	parent_behaviour()
{
	int	status;
	
	pid_t nb = wait(&status);
	printf("Soy un padre! He decibido el valor %d\n", WEXITSTATUS(status));
	exit(0);
}

int	child_behaviour(void)
{
	printf("Soy un hijo!\n");
	exit(42);
}

int	main(void)
{
	pid_t id = fork();

	if (id == 0)
		child_behaviour();
	else
		parent_behaviour();
}
