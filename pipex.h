/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:44:39 by musisman          #+#    #+#             */
/*   Updated: 2025/03/08 16:44:39 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
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

#endif