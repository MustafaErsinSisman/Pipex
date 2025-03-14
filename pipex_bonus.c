/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:31 by musisman          #+#    #+#             */
/*   Updated: 2025/03/14 13:05:54 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
{
	*fd_infile = open(av[1], O_RDONLY, 0777);
	if (*fd_infile == -1 && ft_strncmp(av[1], "here_doc", 8))
		error(ERR_RFILE);
	*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*fd_outfile == -1)
		error(ERR_WFILE);
}

void	wait_child(pid_t pid)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			exit(exit_status);
	}
}

static void	child(char *av, char **env)
{
	pid_t pid;
	int fds[2];

	if (pipe(fds) == -1)
		error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		exec(env, av);
	}
	else
	{
		wait_child(pid);
		close(fds[1]);
		dup2(fds[0], 0);
	}
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
		read_strin(limiter, fds);
	else
	{
		wait_child(pid);
		close(fds[1]);
		dup2(fds[0], 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		input_fd;
	int		output_fd;
	int i;
	
	if (ac < 5)
		error(ERR_ARG);
	file_control(&input_fd, &output_fd, ac, av);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			error(ERR_ARG);
		i = 3;
		here_doc(av[2]);
	}
	else
	{
		i = 2;
		dup2(input_fd, 0);
	}
	while (i < ac - 2)
		child(av[i++], env);
	dup2(output_fd, 1);
	exec(env, av[ac - 2]);
	return (0);
}
