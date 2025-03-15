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
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

#endif