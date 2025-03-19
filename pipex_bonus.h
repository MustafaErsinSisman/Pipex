/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:48 by musisman          #+#    #+#             */
/*   Updated: 2025/03/19 11:41:31 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define ERR_RFILE "Read file error\n"
# define ERR_WFILE "Write file error\n"
# define ERR_ARG "Argument error\n"
# define ERR_PIPE "Pipe error\n"
# define ERR_PATH "Path error\n"
# define ERR_CMD "Command error\n"
# define ERR_PRC "Process error\n"
# define ERR_ENV "Environment variables error\n"

void	do_execve(char **env, char *av);
void	error(char *hat);
void	pipex_process(int ac, char **av, char **env, int *fds);

#endif