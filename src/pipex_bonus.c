/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.c                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:37 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/18 16:43:58 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

#define FIRST_CMD 2
//Syntax: name(0) infile(1) cmd(2)...
#define INFILE_POS 1
//Syntax: name(0) infile(1)...
#define MIN_ARGN 5
//Syntax: name infile cmd cmd1 outfile
#define HRDOC_POS 1
//Syntax: name "here_doc"...
#define DELIMITER_POS 2
//Syntax: name "here_doc" DELIMITER...
#define HRDOC_MIN_ARGN 6
//Syntax: name "here_doc" DELIMITER cmd cmd1 outfile
#define ANYPID -1
//If waitpid receives -1 instead of a real PID, it will wait for any PID

int	main(int argn, char **argv, char **env)
{
	int	fd_in;
	int	arg_count;

	if (argn > 2 && !ft_strncmp(argv[HRDOC_POS], "here_doc", 8))
	{
		if (argn < HRDOC_MIN_ARGN)
			print_error("Error. Not enough arguments.\n");
		fd_in = here_doc_behaviour(argv[DELIMITER_POS]);
		arg_count = 3;
	}
	else if (argn >= MIN_ARGN)
	{
		fd_in = start_behaviour(argv[INFILE_POS], argv[FIRST_CMD], env);
		arg_count = 2;
	}
	else
		print_error("Error. Not enough arguments.\n");
	while (argv[arg_count + 2] && arg_count++)
		fd_in = middle_behaviour(fd_in, argv[arg_count], env);
	end_behaviour(fd_in, argv[arg_count + 1], argv[arg_count], env);
	while (arg_count-- >= 2)
		waitpid(ANYPID, NULL, 0);
	return (0);
}
