/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:37 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/27 17:59:53 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

#define INFILE_POS 1
#define FIRST_CMD 2
#define LAST_CMD 3
#define OUTFILE_POS 4
#define MIN_ARGN 5
//Syntax: name(0) infile(1) cmd(2) cmd1(3) outfile(4)...

int	main(int argn, char **argv, char **env)
{
	int	fd_in;

	if (argn != MIN_ARGN)
		print_error("Error. Wrong number of arguments.");
	fd_in = start_behaviour(argv[INFILE_POS], argv[FIRST_CMD], env);
	end_behaviour(fd_in, argv[OUTFILE_POS], argv[LAST_CMD], env);
	waitpid(ANYPID, NULL, 0);
	waitpid(ANYPID, NULL, 0);
	return (0);
}
