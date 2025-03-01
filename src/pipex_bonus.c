/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex_bonus.c                                  .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:37 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/29 18:58:03 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

#define INFILE_POS 1
#define FIRST_CMD 2
#define MIN_ARGN 5
//Syntax: name infile cmd cmd1 outfile
#define HRDOC_POS 1
#define DELIMITER_POS 2
#define HRDOC_MIN_ARGN 6
//Syntax: name "here_doc" DELIMITER cmd cmd1 outfile

int	main(int argn, char **argv, char **env)
{
	int	fd_in;
	int	arg_count;

	arg_count = 2;
	if (argn > 2 && !ft_strncmp(argv[HRDOC_POS], "here_doc", 8))
	{
		if (argn < HRDOC_MIN_ARGN)
			print_error("Error. Not enough arguments.\n");
		fd_in = here_doc_behaviour(argv[DELIMITER_POS]);
	}
	else if (argn >= MIN_ARGN)
		fd_in = start_behaviour(argv[INFILE_POS], argv[FIRST_CMD], env);
	else
		print_error("Error. Not enough arguments.\n");
	while (arg_count++ && argv[arg_count + 2])
		fd_in = middle_behaviour(fd_in, argv[arg_count], env);
	if (argn > 2 && !ft_strncmp(argv[HRDOC_POS], "here_doc", 8))
		append_behaviour(fd_in, argv[arg_count + 1], argv[arg_count], env);
	else
		end_behaviour(fd_in, argv[arg_count + 1], argv[arg_count], env);
	while (arg_count-- >= 2)
		waitpid(ANYPID, NULL, 0);
	return (0);
}
