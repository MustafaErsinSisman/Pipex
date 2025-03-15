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

# define ERR_RFILE "Okunacak dosya hatasi"
# define ERR_WFILE "Yazilacak dosya hatasi"
# define ERR_ARG "Arguman hatasi"
# define ERR_PIPE "Pipe Hatasi"
# define ERR_PATH "Path hatasi"
# define ERR_CMD "Komut hatasi"
# define ERR_PRC "Process hatasi"
# define ERR_ENV "Environment hatasi"

void	exec(char **env, char *av);
void	error(char *hat);

#endif