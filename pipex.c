/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:44:30 by musisman          #+#    #+#             */
/*   Updated: 2025/03/08 16:44:30 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(char **av, char **env, int *fds)
{
	int	fd_infile;

	fd_infile = open(av[1], O_RDONLY, 0777);
	if (fd_infile == -1)
		error(ERR_RFILE);
	dup2(fds[1], 1);
	dup2(fd_infile, 0);
	close(fds[0]);
	exec(env, av[2]);
}

static void	parent(char **av, char **env, int *fds)
{
	int	fd_outfile;

	fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_outfile == -1)
		error(ERR_WFILE);
	dup2(fds[0], 0);
	dup2(fd_outfile, 1);
	close(fds[1]);
	exec(env, av[3]);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fds[2];

	if (env == NULL)
		error(ERR_ENV);
	if (ac == 5)
	{
		if (pipe(fds) == -1)
			error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			error(ERR_PRC);
		if (pid == 0)
			child(av, env, fds);
		parent(av, env, fds);
	}
	else
		error(ERR_ARG);
	return (0);
}
