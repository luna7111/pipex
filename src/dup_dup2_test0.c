/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   dup_dup2_test0.c                               .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/08 20:46:49 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/08 21:32:45 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "../libft/libft.h"


/* 

	las lecturas al fd duplicado con dup() están sincronizadas con las lecturas
	al fd original

int	main(int argn, char **args)
{
	char *string;
	if (argn < 2)
		return (0);
	int fd = open(args[1], O_RDONLY);
	int fd1 = dup(fd);
	
	string = get_next_line(fd);
	printf("Lectura del fd original (%d): %s\n", fd, string);
	string = get_next_line(fd1);
	printf("Lectura del fd duplicado (%d): %s\n", fd1, string);
}
*/

int	main(int argn, char **args)
{
	if (argn < 2)
		return (0);
	int fd = open(args[1], O_RDWR);
	dup2(fd, STDOUT);
	printf("Hola caradecola\n");
}
