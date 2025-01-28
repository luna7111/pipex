/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pipex.h                                        .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/01/10 16:31:46 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/01/28 14:18:42 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define ANYPID -1
//If waitpid receives -1 instead of a real PID, it will wait for any PID

int		start_behaviour(char *infile, char *command, char **env);
int		here_doc_behaviour(char *delimiter);
int		middle_behaviour(int fd_in, char *command, char **env);
void	end_behaviour(int fd_in, char *outfile, char *command, char **env);

void	perror_exit(char *error);
void	print_error(char *error);
char	*command_path(char **cmd_args, char **env);

#endif
