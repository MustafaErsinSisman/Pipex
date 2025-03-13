/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:31 by musisman          #+#    #+#             */
/*   Updated: 2025/03/13 15:23:41 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
{
	*fd_infile = open(av[1], O_RDONLY, 0777);
	if (*fd_infile == -1)
		error(ERR_RFILE);
	*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*fd_outfile == -1)
		error(ERR_WFILE);
}

static void	child(char *av, char **env, int input_fd, int *fds)
{
	dup2(input_fd, 0);
	dup2(fds[1], 1);
	close(fds[0]);
	exec(env, av);
}

static void	do_cmd(int ac, char **av, char **env, int input_fd)
{
	pid_t	pid;
	int		i;
	int		fds[2];

	i = 2;
	while (i < ac - 2)
	{
		if (pipe(fds) == -1)
			error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			error(ERR_PRC);
		if (pid == 0)
			child(av[i], env, input_fd, fds);
		close(fds[1]);
		input_fd = fds[0];
		i++;
	}
}

static void	write_outfile(char *av, char **env, int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
	{
		dup2(input_fd, 0);
		dup2(output_fd, 1);
		exec(env, av);
	}
	close(output_fd);
	close(input_fd);
	wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	int		input_fd;
	int		output_fd;

	if (ac < 5)
		error(ERR_ARG);
	file_control(&input_fd, &output_fd, ac, av);
	do_cmd(ac, av, env, input_fd);
	write_outfile(av[ac - 1], env, input_fd, output_fd);
	while (wait(NULL) > 0)
		;
	return (0);
}


// #include "pipex_bonus.h"

// static	void	file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
// {
// 	*fd_infile = open(av[1], O_RDONLY, 0777);
// 	if (*fd_infile == -1)
// 		error(ERR_RFILE);
// 	*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	if (*fd_outfile == -1)
// 		error(ERR_WFILE);
// }

// static void	child(char *av, char **env, int input_fd, int *fds)
// {
// 	dup2(input_fd, 0);
// 	dup2(fds[1], 1);
// 	close(fds[0]);
// 	exec(env, av);
// }

// static void	write_outfile(char *av, char **env, int input_fd, int output_fd)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		error(ERR_PRC);
// 	if (pid == 0)
// 	{
// 		dup2(input_fd, 0);
// 		dup2(output_fd, 1);
// 		exec(env, av);
// 	}
// 	close(output_fd);
// 	close(input_fd);
// 	wait(NULL);
// }

// int	main(int ac, char **av, char **env)
// {
// 	pid_t	pid;
// 	int		i;
// 	int		fds[2];
// 	int		input_fd;
// 	int		output_fd;

// 	if (ac < 5)
// 		error(ERR_ARG);
// 	file_control(&input_fd, &output_fd, ac, av);
// 	i = 2;
// 	while (i < ac - 2)
// 	{
// 		if (pipe(fds) == -1)
// 			error(ERR_PIPE);
// 		pid = fork();
// 		if (pid == -1)
// 			error(ERR_PRC);
// 		if (pid == 0)
// 			child(av[i], env, input_fd, fds);
// 		close(fds[1]);
// 		input_fd = fds[0];
// 		i++;
// 	}
// 	write_outfile(av[i], env, input_fd, output_fd);
// 	while (wait(NULL) > 0);
// } 
