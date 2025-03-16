/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:48 by musisman          #+#    #+#             */
/*   Updated: 2025/03/16 15:50:15 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define ERR_RFILE "Read file error"
# define ERR_WFILE "Write file error"
# define ERR_ARG "Argument error"
# define ERR_PIPE "Pipe error"
# define ERR_PATH "Path error"
# define ERR_CMD "Command error"
# define ERR_PRC "Process error"
# define ERR_ENV "Environment variables error"

void	do_execve(char **env, char *av);
void	error(char *hat);
void process_tree(int ac, char **av, char **env, int *fds);

#endif