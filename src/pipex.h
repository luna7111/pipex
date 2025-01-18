/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.h                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:46 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/18 17:01:06 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

int		start_behaviour(char *infile, char *command, char **env);
int		here_doc_behaviour(char *delimiter);
int		middle_behaviour(int fd_in, char *command, char **env);
void	end_behaviour(int fd_in, char *outfile, char *command, char **env);

void	print_error(char *error);
char	*command_path(char *name, char **env);

#endif
